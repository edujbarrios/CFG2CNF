
#include "grammar.h"
#include "cadena.h"
#include <assert.h>
#include <fstream>
#include <string>

Grammar::Grammar() {}

Grammar::Grammar(std::string fileName) {
    std::ifstream archivo(fileName.c_str());
    std::string linea;

    // Símbolos terminales
    getline(archivo, linea);
    int nTerminalSymbol = stoi(linea);
    // Coger solo hasta el primer espacio
    for (int n = 0; n < nTerminalSymbol; n++) {
        getline(archivo, linea);
        Symbol auxSymbol(linea.front());
        terminalSymbol_.insert(auxSymbol);
    }

    // Símbolos no terminales
    getline(archivo, linea);
    int nNonTerminalSymbol = stoi(linea);
  
    for (int n = 0; n < nNonTerminalSymbol; n++) {
        getline(archivo, linea);
        Symbol auxSymbol(linea);
        nonTerminalSymbol_.insert(auxSymbol);
        
        // Condición de que el primer símbolo no terminal sea el estado de arranque
        // Si es el primer símbolo no terminal, lo establecemos como estado de arranque.
        if (n == 0) {
            startSymbolId_ = linea; 
        }
    }

    // Producciones
    getline(archivo, linea);
    int nProductions = stoi(linea);
    for (int n = 0; n < nProductions; n++) {
        getline(archivo, linea);

        size_t pos = linea.find(' '); // Buscar la posición del primer espacio
        if (pos == std::string::npos) {
            // Comprueba los formatos del archivo
            assert(false);
            return;
        }

        // El contenido antes del espacio es el símbolo no terminal en el lado izquierdo de la producción.
        std::string nonTerminal = linea.substr(0, pos);

        Chain auxChain;
        // Los caracteres restantes son los símbolos en el lado derecho de la producción.
        for (size_t j = pos + 1; j < linea.size(); j++) {
            Symbol auxSymbol(linea[j]);
            auxChain.AddSymbol(auxSymbol);
        }

        Production auxProductionRule(nonTerminal, auxChain);
        addProductionRule(auxProductionRule);
    }
}

Grammar::Grammar(Grammar &paramGrammar)
    : terminalSymbol_(paramGrammar.terminalSymbol_),
      nonTerminalSymbol_(paramGrammar.nonTerminalSymbol_),
      startSymbolId_(paramGrammar.startSymbolId_),
      productionRules_(paramGrammar.productionRules_) {}

/**
 * @brief Destruye el objeto Grammar
 *
 */
Grammar::~Grammar() {}

void Grammar::addNonTerminalSymbol(Symbol paramSymbol) {
    nonTerminalSymbol_.insert(paramSymbol);
}

/**
 * @brief Método que añade transiciones al Grammar. Se comprueba que ambos
 * estados pertenecen al conjunto de estados del Grammar y que el símbolo
 * pertenece al Alfabeto
 *
 * @param actualStateId Estado origen
 * @param paramSymbol Símbolo
 * @param nextStateId Estado destino
 */
void Grammar::addProductionRule(Production paramProduction) {
    productionRules_.insert(paramProduction);
}

void Grammar::addTerminalSymbol(Symbol paramSymbol) {
    terminalSymbol_.insert(paramSymbol);
}

bool Grammar::checkGrammar() {
    for (auto pr : productionRules_) {
        if (pr.getChain().Size() == 0)
            return false;
        if (pr.getChain().Size() == 1) {
            bool found = false;
            for (auto symbol : nonTerminalSymbol_) {
                if (pr.getChain().inSymbol(symbol)) {
                    found = true;
                    break;
                }
            }
            if (found)
                return false;
        }
    }
    return true;
}

void Grammar::convertToCNF() {
    /* Comprobar que la gramática no tiene producciones unitarias
     * Comprobar que la gramática no tiene producciones vacías menos el de
     * arranque
     */
    // Producciones vacías
    std::set<Production> toEraseSet;

    // Sustituir símbolos terminales
    for (auto pr : productionRules_) {
        // Longitud de producción > 1
        if (pr.getChain().Size() > 1) {
            for (int i = 0; i < pr.getChain().Size(); i++) {
                // Símbolo terminal
                if (terminalSymbol_.count(pr.getChain().Position(i)) != 0) {
                    toEraseSet.insert(pr);

                    // Crear el nombre de la nueva producción basado en el símbolo terminal
                    std::string auxString;
                    auxString.push_back('C');
                    for (auto symbol : pr.getChain().Position(i))
                        auxString.push_back(symbol);

                    Symbol Cs(auxString);
                    // Se inserta el símbolo designado al conjunto de símbolos no terminales
                    nonTerminalSymbol_.insert(Cs);
                    // Inserto la (nueva) producción de símbolo terminal al conjunto de producciones
                    Chain auxChain(pr.getChain().Position(i));

                    Production terminalSymbolProduction(Cs, auxChain);
                    productionRules_.insert(terminalSymbolProduction);

                    // Modificar la producción cambiando símbolo terminal por su producción
                    Chain prChain(pr.getChain());
                    prChain.assign(i, Cs);
                    Production correctedProd(pr.getNonFinalSymbol(), prChain);
                    productionRules_.insert(correctedProd);
                }
            }
        }
    }
    // Borrar las producciones obsoletas tras la primera pasada
    for (auto erase : toEraseSet)
        productionRules_.erase(erase);
    toEraseSet.clear(); // clean de set

// Reducir a 2 número estados no terminales
char initialCharacter = 'D'; // Inicializamos el primer carácter para las nuevas producciones

for (auto pr : productionRules_) {
    // Crear una copia de la producción actual con el mismo símbolo no terminal y cadena
    Production referenceProduction(pr.getNonFinalSymbol(), pr.getChain());
    
    int counter = referenceProduction.getChain().Size() - 2; // Contador para generar nombres únicos

    bool modified = false; // Variable que indica si se ha modificado la producción

    while (referenceProduction.getChain().Size() > 2) {
        modified = true;
        toEraseSet.insert(referenceProduction); // Marcar la producción original para eliminarla
        
        // Generar un nuevo símbolo no terminal con un nombre único (E1, E2, etc.)
        std::string sustNonTerminalSymbolId(1, initialCharacter);
        sustNonTerminalSymbolId.append(std::to_string(counter));
        counter--;
        Symbol newNonTerminalSymbol(sustNonTerminalSymbolId);
        nonTerminalSymbol_.insert(newNonTerminalSymbol);
        
        // Crear una nueva cadena de producción con los dos últimos símbolos de la cadena original
        Chain newProductionChain(referenceProduction.getChain().Position(
            referenceProduction.getChain().Size() - 2));
        newProductionChain.AddSymbol(referenceProduction.getChain().Position(
            referenceProduction.getChain().Size() - 1));
        Production newProduction(newNonTerminalSymbol, newProductionChain);
        productionRules_.insert(newProduction); // Agregar la nueva producción
        
        Chain substitutionChain;
        // Crear una cadena de sustitución sin los dos últimos símbolos de la cadena original
        for (int i = 0; i < referenceProduction.getChain().Size() - 2; i++)
            substitutionChain.AddSymbol(pr.getChain().Position(i));
        substitutionChain.AddSymbol(newNonTerminalSymbol);
        Production substitutionProduction(
            referenceProduction.getNonFinalSymbol(), substitutionChain);
        productionRules_.insert(substitutionProduction); // Agregar la producción de sustitución
        
        referenceProduction = substitutionProduction; // Actualizar la producción de referencia
    }
    
    if (modified)
        initialCharacter++; // Cambiar el carácter para la próxima generación (Ejemplo: D1, D2, E1, E2, etc.)
}

    // Borrar las producciones obsoletas tras la primera pasada
    for (auto erase : toEraseSet)
        productionRules_.erase(erase);
    toEraseSet.clear(); // Limpiar set
}

Grammar Grammar::getCNFGrammar() {
    Grammar auxGrammar(*this);
    auxGrammar.convertToCNF();
    return auxGrammar;
}

// Define si la gramatica es regular
bool Grammar::isRegular() {
    bool status = true;
    for (auto pr : productionRules_) {
        if (pr.getType(nonTerminalSymbol_) == -1)
            status = false;
    }
    return status;
}

void Grammar::setStartSymbol(std::string paramString) {
    startSymbolId_ = paramString;
}

void Grammar::writeFile(std::string outputFile) {
    std::ofstream file(outputFile);
    std::string line;
    file << terminalSymbol_.size() << "\n";
    for (auto symbol : terminalSymbol_)
        file << symbol << "\n";
    file << nonTerminalSymbol_.size() << "\n";
    for (auto symbol : nonTerminalSymbol_)
        file << symbol << "\n";
    file << productionRules_.size() << "\n";
    for (auto pr : productionRules_) {
        file << pr.getNonFinalSymbol() << " ";
        for (auto symbol : pr.getChain()) {
            // Espacio entre símbolos es decir CaCb en vez de Ca Cb
            file << symbol << "";
        }
        file << "\n";
    }
    file.close();
}

void Grammar::operator=(const Grammar &paramGrammar) {
    terminalSymbol_ = paramGrammar.terminalSymbol_;
    nonTerminalSymbol_ = paramGrammar.nonTerminalSymbol_;
    startSymbolId_ = paramGrammar.startSymbolId_;
    productionRules_ = paramGrammar.productionRules_;
}

/**
 * @brief Sobrecarga del operador de escritura
 *
 * @param os
 * @param paramGrammar
 * @return std::ostream&
 */
std::ostream &operator<<(std::ostream &os, Grammar &paramGrammar) {
    for (auto symbol : paramGrammar.nonTerminalSymbol_) {
        int productionsNumber = paramGrammar.getNProductions(symbol);
        if (productionsNumber > 0) {
            int iterator = 0;
            for (auto production : paramGrammar.productionRules_) {
                if (production.getNonFinalSymbol() == symbol) {
                    if ((productionsNumber - 1) > iterator)
                        iterator++;
                }
            }
        }
    }
    return os;
}

int Grammar::getNProductions(Symbol paramSymbol) {
    assert(nonTerminalSymbol_.count(paramSymbol) != 0);
    int count = 0;
    for (auto production : productionRules_) {
        if (paramSymbol == production.getNonFinalSymbol())
            count++;
    }
    return count;
}
