
#include <iostream>
#include <string>
#pragma once

static char const kEmptyChain = '&';

class Symbol {
public:
  // Constructores y destructores
  Symbol(const std::string);
  Symbol(char);
  ~Symbol();

  // Getters
  const char position(int);
  int Size() const;

  // Operaciones
  bool CheckSimbols(Symbol);

  // Iteradores
  std::string::const_iterator begin() const;
  std::string::const_iterator end() const;

  // Sobrecarga de operadores
  void operator=(const Symbol);
  bool operator==(const Symbol) const;
  bool operator==(const Symbol);
  bool operator==(const std::string);
  bool operator<(const Symbol) const;
  operator std::string(void) const;
  friend std::ostream &operator<<(std::ostream &, const Symbol &);

private:
  std::string symbol_;
};
