
#include "simbolo.h"
#include <algorithm>
#include <iostream>
#include <vector>

#pragma once

class Chain {
public:
  // Constructores y destructores
  Chain();
  Chain(Symbol);
  Chain(std::vector<Symbol>);
  Chain(const Chain &); // Constructor de copia
  Chain(std::string);

  // Getters y setters
  void assign(int, Symbol);
  Symbol back(void) const;
  Symbol Position(int) const;
  int Size(void) const;

  // Iteradores
  std::vector<Symbol>::const_iterator begin() const;
  std::vector<Symbol>::const_iterator end() const;

  
  void AddSymbol(Symbol);
  static Chain Concatenate(const Chain &, const Chain &);
  bool inSymbol(Symbol);


  // Sobrecarga operadores
  bool operator<(const Chain) const;
  friend std::ostream &operator<<(std::ostream &, const Chain &);
  void operator=(const Chain);
  bool operator==(const Chain &) const;

private:
  std::vector<Symbol> chain_;
};
