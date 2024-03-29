/**
 * @file Number.h
 * @title Calculadora de expresiones en notación polaca inversa
 * @brief Declaración de la clase Number
 * @version 1.0
 * @date 6/03/2023
 * @author: Fabrizzio Perilli Martín
 */

#pragma once
#include <cstddef>
#include <string>
#include <iostream>
#include <vector>

template <size_t Base>
class BigInt;

class Number
{
public:
  ~Number();
  virtual Number *Add(const Number *) const = 0;
  virtual Number *Subtract(const Number *) const = 0;
  virtual Number *Multiply(const Number *) const = 0;
  virtual Number *Divide(const Number *) const = 0;
  virtual Number *Module(const Number *) const = 0;
  virtual Number *Pow(const Number *) const = 0;
  virtual size_t GetBase() const = 0;

  virtual operator BigInt<2>() const = 0;
  virtual operator BigInt<8>() const = 0;
  virtual operator BigInt<10>() const = 0;
  virtual operator BigInt<16>() const = 0;
  virtual Number &operator=(const Number &) = 0;

  static Number *create(size_t, const std::string &);
  friend std::ostream &operator<<(std::ostream &, const Number &);
  friend std::istream &operator>>(std::istream &, Number &);

protected:
  virtual std::ostream &Write(std::ostream &) const = 0;
  virtual std::istream &Read(std::istream &) = 0;
};

#include "BigInt.h"
