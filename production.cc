
#include "production.h"

/**
 * @brief Constructor para un objeto Production.
 *
 * @param nonTerminalSymbol El símbolo no terminal.
 * @param paramChain La cadena de símbolos.
 */
Production::Production(Symbol nonTerminalSymbol, Chain paramChain)
    : nonTerminalSymbol_(nonTerminalSymbol), chain_(paramChain) {}

/**
 * @brief Constructor para un objeto Production con un solo símbolo.
 *
 * @param nonTerminalSymbol El símbolo no terminal.
 * @param symbol El símbolo único.
 */
Production::Production(Symbol nonTerminalSymbol, Symbol symbol)
    : nonTerminalSymbol_(nonTerminalSymbol) {
  chain_.AddSymbol(nonTerminalSymbol);
}

/**
 * @brief Destructor para el objeto Production.
 */
Production::~Production() {}

/**
 * @brief Getter para la cadena de símbolos producidos.
 * Objeto constante.
 *
 * @return Chain
 */
Chain Production::getChain() const { return chain_; }

/**
 * @brief Getter para la cadena de símbolos producidos.
 *
 * @return Chain
 */
Chain Production::getChain() { return chain_; }

/**
 * @brief Getter para el símbolo no terminal de la producción.
 * Objeto constante.
 *
 * @return Symbol
 */
Symbol Production::getNonFinalSymbol() const { return nonTerminalSymbol_; }

/**
 * @brief Getter para el símbolo no terminal de la producción.
 *
 * @return Symbol
 */
Symbol Production::getNonFinalSymbol() { return nonTerminalSymbol_; }

/**
 * @brief Obtiene el tipo de regularidad
 *
 * @param paramNonTerminal El conjunto de símbolos no terminales en la gramática.
 * @return int: -1 No regular |
 *              0 Regular izquierda y derecha |
 *              1 Regular izquierda |
 *              2 Regular derecha
 */
int Production::getType(std::set<Symbol> paramNonTerminal) {
  if (paramNonTerminal.count(chain_.Position(0)) != 0) {
    for (int symbolIndex = 1; symbolIndex < chain_.Size(); symbolIndex++) {
      if ((paramNonTerminal.count(chain_.Position(symbolIndex)) != 0))
        return -1; // No es una producción regular
    }
    return 1; // Producción regular izquierda
  }
  if (paramNonTerminal.count(chain_.back()) != 0) {
    for (int symbolIndex = 0; symbolIndex < chain_.Size() - 1; symbolIndex++) {
      if (paramNonTerminal.count(chain_.Position(symbolIndex)) != 0)
        return -1; // No es una producción regular
    }
    return 2; // Producción regular derecha
  }
  for (Symbol symbol : chain_) {
    if (paramNonTerminal.count(symbol) != 0)
      return -1; // No es una producción regular
  }
  return 0; // Es una producción regular en ambas direcciones
}

/**
 * @brief Sobrecarga del operador '<' para trabajar con std::set.
 *
 * @param paramProductionRule Objeto Production candidato para entrar en el std::set.
 * @return True - El objeto Production no está en el conjunto.
 * @return False - El objeto Production está en el conjunto.
 * @see std::set
 */
bool Production::operator<(const Production paramProductionRule) const {
  if (!(nonTerminalSymbol_ == paramProductionRule.getNonFinalSymbol()))
    return (nonTerminalSymbol_ < paramProductionRule.getNonFinalSymbol());
  return (chain_ < paramProductionRule.chain_);
}

/**
 * @brief Sobrecarga del operador de asignación.
 *
 * @param paramProduction Producción a la que se asignará el objeto Production.
 */
void Production::operator=(const Production paramProduction) {
  nonTerminalSymbol_ = paramProduction.nonTerminalSymbol_;
  chain_ = paramProduction.chain_;
}

/**
 * @brief Sobrecarga del operador de comparación de igualdad.
 *
 * @param paramProductionRule Producción con la que se comparará el objeto Production.
 */
bool Production::operator==(
    const Production paramProductionRule) const {
  if (!(nonTerminalSymbol_ == paramProductionRule.getNonFinalSymbol()))
    return false;
  if (!(chain_ == paramProductionRule.chain_))
    return false;
  return true;
}
