
#include "cadena.h"
#include <algorithm>
#include <assert.h>

#define DEFAULT_ALPHABET_SYMBOL "0"

/**
 * @brief Construct a new Chain:: Chain object
 * Cadena vacía
 *
 */
Chain::Chain() {}

/**
 * @brief Construct a new Chain:: Chain object
 * Constructor con simbolo, todos menos cadena vacia
 * @param paramChain Primer simbolo de la cadena
 */
Chain::Chain(Symbol paramSymbol) {
    chain_.push_back(paramSymbol);
}


/**
 * @brief Construct a new Chain:: Chain object
 *
 * @param symbolVector Vector de simbolos
 */
Chain::Chain(std::vector<Symbol> symbolVector) {
  for (auto symbol : symbolVector) {
    chain_.push_back(symbol);
  }
}

/**
 * @brief Construct a new Chain:: Chain object
 * Constructor de copia de la clase
 * @param paramChain Cadena
 */
Chain::Chain(const Chain &paramChain) : chain_(paramChain.chain_) {}

/**
 * @brief Construct a new Chain:: Chain object
 * Constructor que, a partir de una cadena(std) va a añadiendo cada caracter
 * de la cadena como si fuera un simbolo
 * 
 * @param paramChain 
 */
Chain::Chain(std::string paramChain) {
  if ((paramChain.size() == 1) && (paramChain.at(0) == kEmptyChain))
    Chain();
  else {
    for (auto pos : paramChain) {
      Symbol aux(pos);
      AddSymbol(aux);
    }
  }
}
 /**
  * @brief Asigna un simbolo como simbolo de la cadena en la 'index' posicion
  * 
  * @param index Posicion de la cadena
  * @param paramSymbol Simbolo a establecer
  */
void Chain::assign(int index, Symbol paramSymbol) {
  chain_.at(index) = paramSymbol;
}

/**
 * @brief Metodo para devolver el ultimo simbolo de la cadena
 * 
 * @return Symbol 
 */
Symbol Chain::back() const { return chain_.back(); }

/**
 * @brief Getter del index lemento de la cadena
 *
 * @param index Indice de la cadenq
 * @return Symbol
 */
Symbol Chain::Position(int index) const {
  assert((index >= 0) && (index < (int)chain_.size()));
  return chain_.at(index);
}

/**
 * @brief Devuelve la longitud de la cadena
 *
 * @return int - Longitud cadena
 */
int Chain::Size() const { return chain_.size(); }

/**
 * @brief "Sobrecarga" de la función begin para que se pueda recorrer el vector
 * de simbolos en los for de tipo 'auto'
 * 
 * @return std::vector<Symbol>::const_iterator Iterador a la primera posicion
 * de la cadena
 */
std::vector<Symbol>::const_iterator Chain::begin() const {
  return chain_.begin();
}

/**
 * @brief "Sobrecarga" de la función begin para que se pueda recorrer el vector
 * de simbolos en los for de tipo 'auto'
 * 
 * @return std::vector<Symbol>::const_iterator Iterador a la ultima posicion
 * de la cadena
 */
std::vector<Symbol>::const_iterator Chain::end() const { return chain_.end(); }

/**
 * @brief Añadir simbolo a la cadena
 *
 * @param paramSymbol Symbol a añadir
 */
void Chain::AddSymbol(Symbol paramSymbol) { chain_.push_back(paramSymbol); }

/**
 * @brief Operacion concatenar
 *
 * @param original Primera cadena
 * @param adder Cadena a concatenar
 * @return Chain - Cadena resultante
 */
Chain Chain::Concatenate(const Chain &original, const Chain &adder) {
  Chain concatenated;
  Chain empty_chain;
  // Primera cadena no es cadena vacia
  if (!(original == empty_chain)) {
    for (auto symbol : original) {
      concatenated.AddSymbol(symbol);
    }
  }
  // Segunda cadena no es cadena vacia
  if (!(adder == empty_chain)) {
    for (auto symbol : adder) {
      concatenated.AddSymbol(symbol);
    }
  }
  return concatenated;
}

/**
 * @brief Metodo para saber si la cadena contiene un simbolo pasado por
 * parametro
 *
 * @param paramSymbol Simbolo a comprobar
 * @return true - El simbolo esta en la cadena.
 * @return False - El simbolo no esta en la cadena.
 */
bool Chain::inSymbol(Symbol paramSymbol) {
  for (auto symbol : chain_) {
    if (symbol == paramSymbol)
      return true;
  }
  return false;
}



/**
 * @brief Sobrecarga del operador '<' necesario para la clase std::set
 * Compara si una cadena es mayor a otra
 *
 * @param paramChain Cadena candidata a entrar en std::set
 * @return True - La cadena no se encuentra en el conjunto.
 * @return False - La cadena se encuentra en el conjunto.
 * @see std::set
 */
bool Chain::operator<(const Chain paramChain) const {
  // Cadenas distinto tamaño
  if (((int)chain_.size() != paramChain.Size()))
    return ((int)chain_.size() < paramChain.Size());

  // Caso comparar cadena vacia (ya tienen mismo tamaño)
  if (chain_.size() == 0)
    return ((int)chain_.size() < paramChain.Size());
  // terminate called after throwing an instance of 'std::out_of_range'
  // what():  vector::_M_range_check: __n (which is 0) >= this->size() (which is
  // 0)

  // Cadenas mismo tamaño y distinto de 0
  for (size_t i = 0; i < (chain_.size() - 1); i++) {
    if (!(chain_.at(i) == paramChain.Position(i))) {
      return (chain_.at(i) < paramChain.Position(i));
    }
  }
  return (chain_.back() < paramChain.Position(paramChain.Size() - 1));
}

/**
 * @brief Sobrecarga operador '<<' para escritura del objeto
 *
 * @param os
 * @param paramChain
 * @return std::ostream&
 */
std::ostream &operator<<(std::ostream &os, const Chain &paramChain) {
  if (paramChain.Size() == 0)
    return os << kEmptyChain;
  for (auto symbol : paramChain.chain_)
    os << symbol;
  return os;
}

void Chain::operator=(const Chain paramChain) {
  chain_.clear();
  for (auto symbol : paramChain)
    chain_.push_back(symbol);
}

/**
 * @brief Sobrecarga operador '==' para comparación del objeto
 *
 * @param param_chain
 * @return true
 * @return false
 */
bool Chain::operator==(const Chain &paramChain) const {
  if (((int)chain_.size()) != paramChain.Size()) {
    return false;
  } else {
    for (size_t i = 0; i < chain_.size(); i++) {
      if (!(chain_.at(i) == paramChain.Position(i)))
        return false;
    }
  }
  return true;
}

