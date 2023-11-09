
#include "cadena.h"
#include "production.h"
#include "simbolo.h"

#include <iostream>
#include <set>


class Grammar {

public:
  // Constructores y destructores
  Grammar();
  Grammar(std::string);
  Grammar(Grammar &); // Copia
  ~Grammar();

  // Operaciones
  void addNonTerminalSymbol(Symbol);
  void addProductionRule(Production);
  void addTerminalSymbol(Symbol);
  bool checkGrammar();
  void convertToCNF();
  Grammar getCNFGrammar();
  bool isRegular();
  void setStartSymbol(std::string);
  void writeFile(std::string);


  // Sobrecarga de operadores
  void operator=(const Grammar &);
  friend std::ostream &operator<<(std::ostream &, Grammar &);

private:
  int getNProductions(Symbol);

private:
  // Alphabet alphabet_;
  std::set<Symbol> terminalSymbol_;
  std::set<Symbol> nonTerminalSymbol_;
  std::string startSymbolId_;
  std::set<Production> productionRules_;
};
