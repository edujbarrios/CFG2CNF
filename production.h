
#include "cadena.h"
#include "simbolo.h"

#include <iostream>
#include <set>
#include <vector>

class Production {

public:
  // Constructores y destructor
  Production(Symbol, Chain);
  Production(Symbol, Symbol);
  ~Production();

  // Getters y setters
  Chain getChain() const;
  Chain getChain();
  Symbol getNonFinalSymbol() const;
  Symbol getNonFinalSymbol();
  int getType(std::set<Symbol>);

  // Sobrecarga de operadores
  bool operator<(const Production) const;
  void operator=(const Production);
  bool operator==(const Production) const;
  friend std::ostream &operator<<(std::ostream &, Production &);
  friend std::ostream &operator<<(std::ostream &, const Production &);
  
private:
  Symbol nonTerminalSymbol_;
  Chain chain_;
};