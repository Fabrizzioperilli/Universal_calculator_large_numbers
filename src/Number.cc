/**
 * @file Number.cc
 * @title Calculadora de expresiones en notación polaca inversa
 * @brief Implementación de la clase Number
 * @version 1.0
 * @date 6/03/2023
 * @author: Fabrizzio Perilli Martín
 */

#include "../include/Number.h"

Number::~Number() {}

/**
 * @brief Crea un objeto Number a partir de una cadena de caracteres
 *
 * @param base
 * @param number
 * @return Number*
 */
Number *Number::create(size_t base, const std::string &number)
{
  Number *n = nullptr;
  switch (base)
  {
  case 2:
    n = new BigInt<2>(number);
    break;
  case 8:
    n = new BigInt<8>(number);
    break;
  case 10:
    n = new BigInt<10>(number);
    break;
  case 16:
    n = new BigInt<16>(number);
    break;
  default:
    throw BigIntBaseNotImplemented(base, __FILE__, __LINE__);
    break;
  }
  return n;
}

/**
 * @brief Sobrecarga del operador de salida
 *
 * @param os
 * @param n
 * @return std::ostream&
 */
std::ostream &operator<<(std::ostream &os, const Number &n)
{
  return n.Write(os);
}

/**
 * @brief Sobrecarga del operador de entrada
 *
 * @param is
 * @param n
 * @return std::istream&
 */
std::istream &operator>>(std::istream &is, Number &n)
{
  return n.Read(is);
}