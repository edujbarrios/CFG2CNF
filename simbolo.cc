
#include "simbolo.h"
#include <assert.h>

/**
 * @brief Construct a new Symbol:: Symbol object
 * @param paramString
 */
Symbol::Symbol(const std::string paramString) {
  for (auto pos : paramString) {
    symbol_.push_back(pos);
    assert(CheckSimbols(*this));
  }
  // Comprobar no es simbolo reservado cadena vacia
}

Symbol::Symbol(char paramString) {
  symbol_.push_back(paramString);
  assert(CheckSimbols(*this));
}

/**
 * @brief Destroy the Symbol:: Symbol object
 */
Symbol::~Symbol() {}

/**
 * @brief Devuelve el caracter que ocupa index posicion
 * @param index Posicion a la que se quiere acceder
 * @return Caracter
 */
const char Symbol::position(int index) {
  assert((index >= 0) && (index < (int)symbol_.size()));
  return symbol_[index];
}

/**
 * @brief Devuelve el numero de caracteres del simbolo
 * @return Numero de caracteres ASCII del simbolo
 */
int Symbol::Size() const { return symbol_.size(); }

/**
 * @brief Comprueba que no contiene el caracter reservado para la cadena vacía
 *
 * @param paramSymbol Simbolo
 * @return true si la cadena es correcta y false en caso contrario
 */
bool Symbol::CheckSimbols(Symbol paramSymbol) {
  for (auto pos : paramSymbol) {
    if (pos == kEmptyChain)
      return false;
  }
  return true;
}

std::string::const_iterator Symbol::begin() const { return symbol_.begin(); }

std::string::const_iterator Symbol::end() const { return symbol_.end(); }

void Symbol::operator=(const Symbol paramSymbol) {
  symbol_.clear();
  symbol_ = paramSymbol;
}

/**
 * @brief
 * @param paramSymbol
 * @return
 */
bool Symbol::operator==(const Symbol paramSymbol) const {
  if ((symbol_.compare(paramSymbol.symbol_)) == 0) return true;
  else return false;
}

/**
 * @brief
 * @param paramSymbol
 * @return
 */
bool Symbol::operator==(const Symbol paramSymbol) {
  if ((symbol_.compare(paramSymbol.symbol_)) == 0) return true;
  else return false;
}

/**
 * @brief
 * @param paramSymbol
 * @return
 */
bool Symbol::operator==(const std::string paramString) {
  if (symbol_.size() != paramString.size())
    return false;
  for (size_t i = 0; i < symbol_.size(); i++) {
    if (symbol_.at(i) != paramString.at(i))
      return false;
  }
  return true;
}

/**
 * @brief Sobrecarga operador '<' para trabajar con la clase std::set
 * @param param_symbol Simbolo candidato a entrar en el conjunto
 * @return True si el elemento no esta en el conjunto. False en caso contrario.
 */
bool Symbol::operator<(const Symbol param_symbol) const {
  if (symbol_.size() != param_symbol.symbol_.size())
    return (symbol_.size() < param_symbol.symbol_.size());
  for (size_t i = 0; i < symbol_.size() - 1; i++) {
    if (symbol_.at(i) != param_symbol.symbol_.at(i))
      return (symbol_.at(i) < param_symbol.symbol_.at(i));
  }
  return (symbol_.back() < param_symbol.symbol_.back());
}

Symbol::operator std::string(void) const { return symbol_; }

/**
 * @brief Sobrecarga operador '<<' para escritura del objeto
 * @param os std::ostream
 * @param param_symbol Simbolo a escribir
 * @return std::ostream&
 */
std::ostream &operator<<(std::ostream &os, const Symbol &param_symbol) {
  os << param_symbol.symbol_;
  return os;
}