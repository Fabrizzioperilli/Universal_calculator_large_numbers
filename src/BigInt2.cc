/**
 * @file BigInt2.cc
 * @title Calculadora de expresiones en notación polaca inversa
 * @brief Implementación de la clase BigInt<2>
 * @version 1.0
 * @date 6/03/2023
 * @author: Fabrizzio Perilli Martín
 */

#include "../include/BigInt.h"
#include "../include/BigIntException.h"

BigInt<2>::BigInt(long n)
{
  if (n < 0)
  {
    sign_ = 1;
    n = -n;
  }
  else
    sign_ = 0;

  while (n > 0)
  {
    digits_.push_back(n % 2);
    n /= 2;
  }
}

BigInt<2>::BigInt(std::string s)
{
  if (s[0] == '1')
    sign_ = 1;
  else if (s[0] == '0')
    sign_ = 0;
  else
    throw BigIntBadDigit(s[0], __FILE__, __LINE__);

  for (int i = s.length() - 1; i >= 0; i--)
  {
    if (s[i] == '0')
      digits_.push_back(false);
    else if (s[i] == '1')
      digits_.push_back(true);
    else
      throw BigIntBadDigit(s[i], __FILE__, __LINE__);
  }
}

BigInt<2>::BigInt(const char *s) : BigInt<2>(std::string(s)) {}

BigInt<2>::BigInt(const BigInt<2> &other)
{
  digits_ = other.digits_;
  sign_ = other.sign_;
}

BigInt<2>::~BigInt() {}

std::vector<bool> BigInt<2>::GetDigits() const
{
  return digits_;
}

void BigInt<2>::SetDigits(std::vector<bool> digits)
{
  digits_ = digits;
}

BigInt<2> BigInt<2>::operator=(const BigInt<2> &other)
{
  digits_ = other.digits_;
  sign_ = other.sign_;
  return *this;
}

// Operador de cambio de signo, complemento a 2.
BigInt<2> BigInt<2>::operator-() const
{
  // Complemento a 2, invertir bits y sumar 1.
  BigInt<2> result;

  for (int i = 0; i < digits_.size(); i++)
  {
    if (digits_[i])
      result.digits_.push_back(false);
    else
      result.digits_.push_back(true);
  }

  result++;

  if (sign_ == 0)
    result.sign(0);
  else
    result.sign(1);

  return result;
}

bool operator==(const BigInt<2> &a, const BigInt<2> &b)
{
  BigInt<2> aux1;
  BigInt<2> aux2;

  if (a.sign() != b.sign())
    return false;
  else if (a.GetDigits().size() < b.GetDigits().size())
  {
    aux1 = a.FillSign(b.GetDigits().size() - a.GetDigits().size());
    aux2 = b;
  }
  else if (a.GetDigits().size() > b.GetDigits().size())
  {
    aux1 = a;
    aux2 = b.FillSign(a.GetDigits().size() - b.GetDigits().size());
  }
  else
  {
    aux1 = a;
    aux2 = b;
  }

  for (int i = 0; i < aux1.GetDigits().size(); i++)
    if (aux1[i] != aux2[i])
      return false;

  return true;
}

bool BigInt<2>::operator!=(const BigInt<2> &other) const
{
  return !(*this == other);
}

bool operator>(const BigInt<2> &a, const BigInt<2> &b)
{
  BigInt<2> aux1;
  BigInt<2> aux2;

  if (a.sign() != b.sign())
    return a.sign() < b.sign();
  else if (a.GetDigits().size() < b.GetDigits().size())
  {
    aux1 = a.FillSign(b.GetDigits().size() - a.GetDigits().size());
    aux2 = b;
  }
  else if (a.GetDigits().size() > b.GetDigits().size())
  {
    aux1 = a;
    aux2 = b.FillSign(a.GetDigits().size() - b.GetDigits().size());
  }
  else
  {
    aux1 = a;
    aux2 = b;
  }

  for (int i = aux1.GetDigits().size() - 1; i >= 0; i--)
  {
    if (aux1[i] != aux2[i])
      return aux1[i] > aux2[i];
  }

  return false;
}

bool BigInt<2>::operator>=(const BigInt<2> &other) const
{
  return *this > other || *this == other;
}

bool operator<(const BigInt<2> &a, const BigInt<2> &b)
{
  return !(a >= b);
}

bool BigInt<2>::operator<=(const BigInt<2> &other) const
{
  return *this < other || *this == other;
}

BigInt<2> &BigInt<2>::operator++()
{
  BigInt<2> one("01");
  *this = *this + one;
  return *this;
}

BigInt<2> BigInt<2>::operator++(int)
{
  BigInt<2> result(*this);
  ++(*this);
  return result;
}

BigInt<2> &BigInt<2>::operator--()
{
  BigInt<2> one("01");
  *this = *this - one;
  return *this;
}

BigInt<2> BigInt<2>::operator--(int)
{
  BigInt<2> result(*this);
  --(*this);
  return result;
}

BigInt<2> BigInt<2>::operator+(const BigInt<2> &a) const
{
  BigInt<2> first = *this;
  BigInt<2> other = a;

  std::vector<bool> number_x = first.digits_;
  std::vector<bool> number_y = other.digits_;
  bool carry = false;
  bool sum;

  if (number_x.size() > number_y.size())
    number_y = other.FillSign(number_x.size() - number_y.size()).digits_;
  else if (number_x.size() < number_y.size())
    number_x = first.FillSign(number_y.size() - number_x.size()).digits_;

  std::vector<bool> aux;
  for (size_t i = 0; i < number_x.size(); i++)
  {
    sum = number_x[i] ^ number_y[i] ^ carry;
    carry = (number_x[i] & number_y[i]) | (number_x[i] & carry) | (number_y[i] & carry);
    aux.push_back(sum);
  }

  if (carry)
    aux.push_back(carry);

  BigInt<2> result;
  result.digits_ = aux;

  if (result.digits_[result.digits_.size() - 1])
    result.sign_ = 1;
  else
    result.sign_ = 0;

  return result;
}

BigInt<2> BigInt<2>::operator-(const BigInt<2> &a) const
{
  return *this + (-a);
}

BigInt<2> BigInt<2>::operator*(const BigInt<2> &b) const
{

  std::vector<bool> result(digits_.size() + b.digits_.size(), 0);
  BigInt<2> aux;

  for (int i = 0; i < digits_.size(); i++)
    for (int j = 0; j < b.digits_.size(); j++)
      if (digits_[i] && b.digits_[j])
        result[i + j] = !result[i + j];

  int carry = 0;
  for (int i = 0; i < result.size(); i++)
  {
    int sum = result[i] + carry;
    result[i] = sum % 2;
    carry = sum / 2;
  }

  while (result.size() > 1 && result.back() == 0)
    result.pop_back();

  aux.SetDigits(result);

  if (aux.digits_[aux.digits_.size() - 1])
    aux.sign_ = 1;
  else
    aux.sign_ = 0;

  return aux;
}

BigInt<2> BigInt<2>::operator/(const BigInt<2> &b) const
{
  BigInt<2> result;
  BigInt<2> dividend = *this;
  BigInt<2> divisor = b;

  if (divisor == BigInt<2>("0"))
    throw BigIntDivisionByZero(__FILE__, __LINE__);

  if (dividend == BigInt<2>("0"))
    return BigInt<2>("0");

  if (divisor == BigInt<2>("1"))
    return dividend;

  if (divisor == dividend)
    return BigInt<2>("1");

  if (divisor.GetDigits().size() > dividend.GetDigits().size())
    dividend = dividend.FillSign(divisor.GetDigits().size() - dividend.GetDigits().size());
  else if (divisor.GetDigits().size() < dividend.GetDigits().size())
    divisor = divisor.FillSign(dividend.GetDigits().size() - divisor.GetDigits().size());

  BigInt<2> temp;
  for (int i = dividend.digits_.size() - 1; i >= 0; i--)
  {
    temp.digits_.insert(temp.digits_.begin(), 0);
    int count = 0;
    if (temp >= divisor)
    {
      temp = temp - divisor;
      count++;
    }
    result.digits_.insert(result.digits_.begin(), count);

    temp.digits_[0] = dividend.digits_[i];
  }

  if (result.digits_[result.digits_.size() - 1])
    result.sign_ = 1;
  else
    result.sign_ = 0;

  return result;
}

BigInt<2> BigInt<2>::operator%(const BigInt<2> &b) const
{

  BigInt<2> result;
  BigInt<2> dividend = *this;
  BigInt<2> divisor = b;

  if (divisor.GetDigits().size() > dividend.GetDigits().size())
    dividend = dividend.FillSign(divisor.GetDigits().size() - dividend.GetDigits().size());
  else if (divisor.GetDigits().size() < dividend.GetDigits().size())
    divisor = divisor.FillSign(dividend.GetDigits().size() - divisor.GetDigits().size());

  if (divisor == BigInt<2>("0"))
    throw BigIntDivisionByZero(__FILE__, __LINE__);

  if (dividend == BigInt<2>("0"))
    return BigInt<2>("0");

  if (divisor == BigInt<2>("1"))
    return BigInt<2>("0");

  if (divisor == dividend)
    return BigInt<2>("0");

  if (dividend < divisor)
    return dividend;

  BigInt<2> temp;
  while (dividend >= divisor)
  {
    temp.digits_.insert(temp.digits_.begin(), 0);
    int count = 0;
    if (temp >= divisor)
    {
      temp = temp - divisor;
      count++;
    }
    result.digits_.insert(result.digits_.begin(), count);

    temp.digits_[0] = dividend.digits_[0];
    dividend.digits_.erase(dividend.digits_.begin());
  }

  if (result.digits_[result.digits_.size() - 1])
    result.sign_ = 1;
  else
    result.sign_ = 0;

  return temp;
}

BigInt<2> pow(const BigInt<2> &a, const BigInt<2> &b)
{
  BigInt<2> result = a;

  if (b == BigInt<2>("0"))
    return BigInt<2>("1");

  if (b == BigInt<2>("1"))
    return a;

  if (b < BigInt<2>("0"))
    throw std::invalid_argument("Exponent cannot be negative");

  for (int i = 0; i < b.GetDigits().size(); i++)
    if (b.GetDigits()[i])
      result = result * a;

  return result;
}

std::ostream &operator<<(std::ostream &os, const BigInt<2> &n)
{
  for (int i = n.GetDigits().size() - 1; i >= 0; i--)
    os << (n.GetDigits()[i] ? '1' : '0');
  return os;
}

std::istream &operator>>(std::istream &is, BigInt<2> &n)
{
  std::string s;
  is >> s;
  n = BigInt<2>(s);
  return is;
}

int BigInt<2>::sign() const
{
  return sign_;
}

void BigInt<2>::sign(int s)
{
  sign_ = s;
}

bool BigInt<2>::operator[](int i) const
{
  return digits_[i];
}

template <size_t Base>
BigInt<Base> BigInt<2>::ToBase() const
{

  BigInt<2> aux_this(*this);
  BigInt<Base> result;
  int aux_sign;

  if (aux_this.sign() == 1)
  {
    aux_this = -aux_this;
    aux_sign = 1;
  }

  for (int i = 0; i < aux_this.GetDigits().size(); i++)
    if (aux_this.GetDigits()[i])
      result = result + BigInt<Base>(std::pow(2, i));

  if (aux_sign == 1)
    result.sign(-1);
  else
    result.sign(1);

  return result;
}

BigInt<2>::operator BigInt<8>() const
{
  BigInt<2> aux_this(*this);
  return aux_this.ToBase<8>();
}

BigInt<2>::operator BigInt<10>() const
{
  BigInt<2> aux_this(*this);
  return aux_this.ToBase<10>();
}

BigInt<2>::operator BigInt<16>() const
{
  BigInt<2> aux_this(*this);
  return aux_this.ToBase<16>();
}

BigInt<2>::operator BigInt<2>() const
{
  return *this;
}

Number *BigInt<2>::Add(const Number *n) const
{
  size_t base = GetBase();
  size_t base2 = n->GetBase();

  if (base != base2)
  {
    BigInt<2> b1 = this->operator BigInt<2>();
    BigInt<2> b2 = n->operator BigInt<2>();
    return new BigInt<2>(b1 + b2);
  }
  BigInt<2> aux = *(BigInt<2> *)n;
  return new BigInt<2>(*this + aux);
}

Number *BigInt<2>::Subtract(const Number *n) const
{
  size_t base = GetBase();
  size_t base2 = n->GetBase();

  if (base != base2)
  {
    BigInt<2> b1 = this->operator BigInt<2>();
    BigInt<2> b2 = n->operator BigInt<2>();
    return new BigInt<2>(b1 - b2);
  }
  BigInt<2> aux = *(BigInt<2> *)n;
  return new BigInt<2>(*this - aux);
}

Number *BigInt<2>::Multiply(const Number *n) const
{
  size_t base = GetBase();
  size_t base2 = n->GetBase();

  if (base != base2)
  {
    BigInt<2> b1 = this->operator BigInt<2>();
    BigInt<2> b2 = n->operator BigInt<2>();
    return new BigInt<2>(b1 * b2);
  }
  BigInt<2> aux = *(BigInt<2> *)n;
  return new BigInt<2>(*this * aux);
}

Number *BigInt<2>::Divide(const Number *n) const
{
  size_t base = GetBase();
  size_t base2 = n->GetBase();

  if (base != base2)
  {
    BigInt<2> b1 = this->operator BigInt<2>();
    BigInt<2> b2 = n->operator BigInt<2>();
    return new BigInt<2>(b1 / b2);
  }
  BigInt<2> aux = *(BigInt<2> *)n;
  return new BigInt<2>(*this / aux);
}

Number *BigInt<2>::Module(const Number *n) const
{
  size_t base = GetBase();
  size_t base2 = n->GetBase();

  if (base != base2)
  {
    BigInt<2> b1 = this->operator BigInt<2>();
    BigInt<2> b2 = n->operator BigInt<2>();
    return new BigInt<2>(b1 % b2);
  }
  BigInt<2> aux = *(BigInt<2> *)n;
  return new BigInt<2>(*this % aux);
}

Number *BigInt<2>::Pow(const Number *n) const
{
  size_t base = GetBase();
  size_t base2 = n->GetBase();

  if (base != base2)
  {
    BigInt<2> b1 = this->operator BigInt<2>();
    BigInt<2> b2 = n->operator BigInt<2>();
    return new BigInt<2>(pow(b1, b2));
  }
  BigInt<2> aux = *(BigInt<2> *)n;
  return new BigInt<2>(pow(*this, aux));
}

size_t BigInt<2>::GetBase() const
{
  return 2;
}

Number &BigInt<2>::operator=(const Number &n)
{
  BigInt<2> aux = *(BigInt<2> *)&n;
  *this = aux;
  return *this;
}

std::ostream &BigInt<2>::Write(std::ostream &os) const
{
  return os << *this;
}

std::istream &BigInt<2>::Read(std::istream &is)
{
  return is >> *this;
}

BigInt<2> BigInt<2>::FillSign(int size) const
{
  BigInt<2> result(*this);

  if (result.sign() == 1)
    for (int i = 0; i < size; i++)
      result.digits_.push_back(1);
  else
    for (int i = 0; i < size; i++)
      result.digits_.push_back(0);

  return result;
}