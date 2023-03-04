/**
 * @file BigInt.h
 * @brief Plantilla de clase para la representación de números grandes
 * @version 1.0
 * @date 14/02/2023
 * @author Fabrizzio Perilli Martín
 */
#pragma once
#include <iostream>
#include <vector>
#include <regex>
#include <math.h>
#include "Number.h"

template <size_t Base>
class BigInt;

template <size_t Base>
std::ostream &operator<<(std::ostream &, const BigInt<Base> &);

template <size_t Base>
std::istream &operator>>(std::istream &, BigInt<Base> &);

template <size_t Base>
BigInt<Base> operator+(const BigInt<Base> &, const BigInt<Base> &);

template <size_t Base>
bool operator==(const BigInt<Base> &, const BigInt<Base> &);

template <size_t Base>
bool operator>(const BigInt<Base> &, const BigInt<Base> &);

template <size_t Base>
bool operator<(const BigInt<Base> &, const BigInt<Base> &);

template <size_t Base>
BigInt<Base> operator/(const BigInt<Base> &, const BigInt<Base> &);

template <size_t Base>
BigInt<Base> pow(const BigInt<Base> &, const BigInt<Base> &);

template <size_t Base = 10>
class BigInt: public Number {
public:
  BigInt(long = 0);
  BigInt(std::string);
  BigInt(const char *);
  BigInt(const BigInt<Base> &);
  ~BigInt();

  BigInt<Base> operator=(const BigInt<Base> &);
  std::vector<char> GetDigits();

  friend std::ostream &operator<< <Base>(std::ostream &, const BigInt<Base> &);
  friend std::istream &operator>><Base>(std::istream &, BigInt<Base> &);

  int sign() const;
  void sign(int);

  char operator[](int) const;

  friend bool operator==<Base>(const BigInt<Base> &, const BigInt<Base> &);
  bool operator!=(const BigInt<Base> &) const;
  friend bool operator><Base>(const BigInt<Base> &, const BigInt<Base> &);
  bool operator>=(const BigInt<Base> &) const;
  friend bool operator< <Base>(const BigInt<Base> &, const BigInt<Base> &);
  bool operator<=(const BigInt<Base> &) const;

  BigInt<Base> &operator++();
  BigInt<Base> operator++(int);
  BigInt<Base> &operator--();
  BigInt<Base> operator--(int);

  friend BigInt<Base> operator+<Base>(const BigInt<Base> &, const BigInt<Base> &);
  BigInt<Base> operator-(const BigInt<Base> &) const;
  BigInt<Base> operator-() const;
  BigInt<Base> operator*(const BigInt<Base> &) const;
  friend BigInt<Base> operator/<Base>(const BigInt<Base> &, const BigInt<Base> &);
  BigInt<Base> operator%(const BigInt<Base> &) const;
  friend BigInt<Base> pow<Base>(const BigInt<Base> &, const BigInt<Base> &);

  operator BigInt<2>();
  
  Number *Add(const Number *) const override;
  // Number *Subtract(const Number *) const override;
  // Number *Multiply(const Number *) const override;
  // Number *Divide(const Number *) const override;
  // Number *Module(const Number *) const override;
  // Number *Pow(const Number *) const override;


  Number& operator=(const Number&) override;
  std::ostream& Write(std::ostream&) const override;
  std::istream& Read(std::istream&) override;

private:
  bool CheckBase();
  bool CheckDigits(char);
  std::vector<char> digits_;
  int sign_; // 1 positive , -1 negative
};

////////////////////////////////////////////////////////
template <size_t Base>
BigInt<Base>::BigInt(long n)
{
  if (CheckBase())
    if (n < 0)
    {
      sign_ = -1;
      n = -n;
    }
    else
      sign_ = 1;
  else
  {
    std::cout << "Error: Base no válida" << std::endl;
    exit(EXIT_FAILURE);
  }

  while (n > 0)
  {
    digits_.push_back(n % 10 + '0');
    n /= 10;
  }
}

template <size_t Base>
BigInt<Base>::BigInt(std::string n)
{

  if (CheckBase())
    if (n[0] == '-')
    {
      sign_ = -1;
      n = n.erase(0, 1);
    }
    else if (n[0] == '+')
    {
      sign_ = 1;
      n = n.erase(0, 1);
    }
    else if (regex_match(std::string(1, n[0]), std::regex("[0-9A-F]")))
      sign_ = 1;
    else
    {
      std::cout << "Error: Valor del operando no válido" << std::endl;
      exit(EXIT_FAILURE);
    }
  else
  {
    std::cout << "Error: Base no válida" << std::endl;
    exit(EXIT_FAILURE);
  }

  for (int i = n.size() - 1; i >= 0; i--)
    if (CheckDigits(n[i]))
      digits_.push_back(n[i]);
    else
    {
      std::cout << "Error: Valor del operando en base diferente a la especificada" << std::endl;
      exit(EXIT_FAILURE);
    }
}

template <size_t Base>
BigInt<Base>::BigInt(const char *n) : BigInt(std::string(n)) {}

template <size_t Base>
BigInt<Base>::BigInt(const BigInt<Base> &n)
{
  sign_ = n.sign_;
  digits_ = n.digits_;
}

template <size_t Base>
BigInt<Base>::~BigInt() {}

template <size_t Base>
std::vector<char> BigInt<Base>::GetDigits()
{
  return digits_;
}

template <size_t Base>
BigInt<Base> BigInt<Base>::operator=(const BigInt<Base> &n1)
{
  sign_ = n1.sign_;
  digits_ = n1.digits_;
  return *this;
}

template <size_t Base>
std::ostream &operator<<(std::ostream &os, const BigInt<Base> &n)
{
  if (n.sign_ == -1)
    os << "-";
  for (int i = n.digits_.size() - 1; i >= 0; i--)
    os << n.digits_[i];
  return os;
}

template <size_t Base>
std::istream &operator>>(std::istream &is, BigInt<Base> &n)
{
  std::string s;
  is >> s;
  n = BigInt<Base>(s);
  return is;
}

template <size_t Base>
int BigInt<Base>::sign() const
{
  return sign_;
}

template <size_t Base>
void BigInt<Base>::sign(int s)
{
  sign_ = s;
}

template <size_t Base>
char BigInt<Base>::operator[](int i) const
{
  int size = digits_.size();
  if (i < 0 || i >= size)
    throw std::out_of_range("Fuera de rango");

  return digits_[i];
}

template <size_t Base>
bool operator==(const BigInt<Base> &n1, const BigInt<Base> &n2)
{
  if (n1.sign_ != n2.sign_)
    return false;
  if (n1.digits_.size() != n2.digits_.size())
    return false;
  for (size_t i = 0; i < n1.digits_.size(); i++)
    if (n1[i] != n2[i])
      return false;
  return true;
}

template <size_t Base>
bool BigInt<Base>::operator!=(const BigInt<Base> &n1) const
{
  return !(n1 == *this);
}

template <size_t Base>
bool operator>(const BigInt<Base> &n1, const BigInt<Base> &n2)
{
  if (n1.sign_ == -1 && n2.sign_ == 1)
    return false;
  if (n1.sign_ == 1 && n2.sign_ == -1)
    return true;
  if (n1.sign_ == 1 && n2.sign_ == 1)
  {
    if (n1.digits_.size() > n2.digits_.size())
      return true;
    else if (n1.digits_.size() < n2.digits_.size())
      return false;
    else
    {
      for (int i = n1.digits_.size() - 1; i >= 0; i--)
      {
        if (n1[i] > n2[i])
          return true;
        else if (n1[i] < n2[i])
          return false;
      }
    }
  }
  return false;
}

template <size_t Base>
bool BigInt<Base>::operator>=(const BigInt<Base> &n1) const
{
  return (*this > n1 || n1 == *this);
}

template <size_t Base>
bool operator<(const BigInt<Base> &n1, const BigInt<Base> &n2)
{
  return !(n1 >= n2);
}

template <size_t Base>
bool BigInt<Base>::operator<=(const BigInt<Base> &n1) const
{
  return (*this < n1 || n1 == *this);
}

template <size_t Base>
BigInt<Base> &BigInt<Base>::operator++()
{
  BigInt<Base> one(1);
  *this = *this + one;
  return *this;
}

template <size_t Base>
BigInt<Base> BigInt<Base>::operator++(int)
{
  BigInt<Base> result(*this);
  ++(*this);
  return result;
}

template <size_t Base>
BigInt<Base> &BigInt<Base>::operator--()
{
  BigInt<Base> one(1);
  *this = *this - one;
  return *this;
}

template <size_t Base>
BigInt<Base> BigInt<Base>::operator--(int)
{
  BigInt<Base> result(*this);
  --(*this);
  return result;
}

template <size_t Base>
BigInt<Base> operator+(const BigInt<Base> &n1, const BigInt<Base> &n2)
{
  BigInt<Base> result;

  size_t carry = 0;
  size_t i = 0;
  size_t j = 0;

  if (n1.sign() == -1 && n2.sign() == -1)
  {
    result.sign_ = -1;
    while (i < n1.digits_.size() || j < n2.digits_.size())
    {
      int num1 = i < n1.digits_.size() ? (isdigit(n1[i]) ? n1[i] - '0' : n1[i] - 'A' + 10) : 0;
      int num2 = j < n2.digits_.size() ? (isdigit(n2[j]) ? n2[j] - '0' : n2[j] - 'A' + 10) : 0;
      ++i;
      ++j;

      int sum = num1 + num2 + carry;
      carry = sum / Base;
      sum = sum % Base;

      if (sum >= 0 && sum <= 9)
        result.digits_.push_back(sum + '0');
      else if (sum >= 10 && sum <= 15)
        result.digits_.push_back(sum - 10 + 'A');
    }

    if (carry > 0)
      result.digits_.push_back(carry + '0');
  }
  else if (n1.sign() == 1 && n2.sign() == 1)
  {
    result.sign_ = 1;
    while (i < n1.digits_.size() || j < n2.digits_.size())
    {
      int num1 = i < n1.digits_.size() ? (isdigit(n1[i]) ? n1[i] - '0' : n1[i] - 'A' + 10) : 0;
      int num2 = j < n2.digits_.size() ? (isdigit(n2[j]) ? n2[j] - '0' : n2[j] - 'A' + 10) : 0;
      ++i;
      ++j;

      int sum = num1 + num2 + carry;
      carry = sum / Base;
      sum = sum % Base;

      if (sum >= 0 && sum <= 9)
        result.digits_.push_back(sum + '0');
      else if (sum >= 10 && sum <= 15)
        result.digits_.push_back(sum - 10 + 'A');
    }

    if (carry > 0)
      result.digits_.push_back(carry + '0');
  }
  else if (n1.sign() == -1 && n2.sign() == 1)
  {
    BigInt<Base> n1_copy(n1);
    n1_copy.sign_ = 1;
    result = n2 - n1_copy;
  }
  else if (n1.sign() == 1 && n2.sign() == -1)
  {
    BigInt<Base> n2_copy(n2);
    n2_copy.sign_ = 1;
    result = n1 - n2_copy;
  }

  return result;
}

template <size_t Base>
BigInt<Base> BigInt<Base>::operator-(const BigInt<Base> &other) const
{
  BigInt<Base> result;

  size_t carry = 0;
  size_t i = 0;
  size_t j = 0;

  if (other == *this)
    return BigInt<Base>("0");

  if (sign() == -1 && other.sign() == -1)
  {
    BigInt<Base> n1_copy(*this);
    n1_copy.sign_ = 1;
    BigInt<Base> n2_copy(other);
    n2_copy.sign_ = 1;
    result = n2_copy - n1_copy;
  }
  else if (sign() == 1 && other.sign() == 1)
  {
    BigInt<Base> n1_copy(*this);
    BigInt<Base> n2_copy(other);
    if (n1_copy < n2_copy)
    {
      result = n2_copy - n1_copy;
      result.sign_ = -1;
    }
    else
    {
      result.sign_ = 1;
      while (i < n1_copy.digits_.size() || j < n2_copy.digits_.size())
      {
        int num1, num2;
        if (i < n1_copy.digits_.size())
        {
          if (n1_copy[i] >= '0' && n1_copy[i] <= '9')
            num1 = n1_copy[i] - '0';
          else if (n1_copy[i] >= 'A' && n1_copy[i] <= 'F')
            num1 = n1_copy[i] - 'A' + 10;
          i++;
        }
        else
          num1 = 0;

        if (j < n2_copy.digits_.size())
        {
          if (n2_copy[j] >= '0' && n2_copy[j] <= '9')
            num2 = n2_copy[j] - '0';
          else if (n2_copy[j] >= 'A' && n2_copy[j] <= 'F')
            num2 = n2_copy[j] - 'A' + 10;
          j++;
        }
        else
          num2 = 0;

        int sum = num1 - num2 - carry;
        if (sum < 0)
        {
          sum += Base;
          carry = 1;
        }
        else
          carry = 0;

        if (sum >= 0 && sum <= 9)
          result.digits_.push_back(sum + '0');
        else if (sum >= 10 && sum <= 15)
          result.digits_.push_back(sum - 10 + 'A');
      }
    }
  }
  else if (sign() == -1 && other.sign() == 1)
  {
    BigInt<Base> n1_copy(*this);
    n1_copy.sign_ = 1;
    result = n1_copy + other;
    result.sign_ = -1;
  }
  else if (sign() == 1 && other.sign() == -1)
  {
    BigInt<Base> n2_copy(other);
    n2_copy.sign_ = 1;
    result = *this + n2_copy;
  }

  if (result.digits_[result.digits_.size() - 1] == '0')
    result.digits_.pop_back();

  return result;
}

template <size_t Base>
BigInt<Base> BigInt<Base>::operator-() const
{
  BigInt<Base> result(*this);
  result.sign_ = -result.sign_;
  return result;
}

template <size_t Base>
BigInt<Base> BigInt<Base>::operator*(const BigInt<Base> &rhs) const
{
  BigInt<Base> result;
  result.sign_ = sign_ * rhs.sign_;

  BigInt<Base> n1 = *this;
  BigInt<Base> n2 = rhs;

  if (n1.sign() == -1)
    n1 = -n1;
  if (n2.sign() == -1)
    n2 = -n2;

  BigInt<Base> sum;

  for (size_t i = 0; i < n2.digits_.size(); i++)
  {
    BigInt<Base> temp;
    int carry = 0;
    for (size_t j = 0; j < n1.digits_.size(); j++)
    {
      int num1 = n1[j] >= '0' && n1[j] <= '9' ? n1[j] - '0' : n1[j] - 'A' + 10;
      int num2 = n2[i] >= '0' && n2[i] <= '9' ? n2[i] - '0' : n2[i] - 'A' + 10;
      int prod = num1 * num2 + carry;
      carry = prod / Base;
      prod = prod % Base;
      temp.digits_.push_back(prod >= 10 ? prod - 10 + 'A' : prod + '0');
    }
    if (carry > 0)
      temp.digits_.push_back(carry >= 10 ? carry - 10 + 'A' : carry + '0');
    for (size_t j = 0; j < i; j++)
      temp.digits_.insert(temp.digits_.begin(), '0');
    sum = sum + temp;
  }

  if (result.sign() == -1)
    result = -sum;
  else
    result = sum;

  return result;
}

template <size_t Base>
BigInt<Base> operator/(const BigInt<Base> &lhs, const BigInt<Base> &rhs)
{
  BigInt<Base> result;
  BigInt<Base> n1 = lhs;
  BigInt<Base> n2 = rhs;

  if (n1.sign() == -1)
    n1 = -n1;
  if (n2.sign() == -1)
    n2 = -n2;

  if (n1 < n2)
  {
    result.digits_.push_back('0');
    return result;
  }

  BigInt<Base> temp;
  for (int i = (int)n1.digits_.size() - 1; i >= 0; i--)
  {
    temp.digits_.insert(temp.digits_.begin(), n1[i]);
    int count = 0;
    while (temp >= n2)
    {
      temp = temp - n2;
      count++;
    }
    std::string str_count = std::to_string(count);
    result.digits_.insert(result.digits_.begin(), str_count[0]);
  }

  if (lhs.sign() == -1 && rhs.sign() == -1)
    result.sign_ = 1;
  else if (lhs.sign() == -1 || rhs.sign() == -1)
    result.sign_ = -1;

  if (result.digits_[result.digits_.size() - 1] == '0')
    result.digits_.pop_back();

  if (result.digits_.empty())
    result.digits_.push_back('0');

  return result;
}

template <size_t Base>
BigInt<Base> BigInt<Base>::operator%(const BigInt<Base> &rhs) const
{
  BigInt<Base> n1 = *this;
  BigInt<Base> n2 = rhs;
  BigInt<Base> result;

  if (n1.sign() == -1)
    n1 = -n1;
  if (n2.sign() == -1)
    n2 = -n2;

  if (n2 == BigInt<Base>("0"))
  {
    std::cerr << "Error: no se puede dividir entre cero." << std::endl;
    return BigInt<Base>();
  }

  if (n1 < n2)
    return n1;

  if (n1 == n2)
    return BigInt<Base>("0");

  if (n2 == BigInt<Base>(1L))
    return BigInt<Base>("0");

  BigInt<Base> temp;

  for (int i = (int)n1.digits_.size() - 1; i >= 0; i--)
  {
    temp.digits_.insert(temp.digits_.begin(), n1[i]);
    int count = 0;
    while (temp >= n2)
    {
      temp = temp - n2;
      count++;
    }
    n1.digits_.at(i) = count;
  }

  // Elimina los ceros no significativos al principio del vector de residuos.
  while (n1.digits_.size() > 1 && n1.digits_.back() == 0)
    n1.digits_.pop_back();

  if (sign() == -1)
    temp = -temp;

  result = temp;
  result.sign(temp.sign());

  return result;
}

template <size_t Base>
BigInt<Base> pow(const BigInt<Base> &a, const BigInt<Base> &b)
{
  if (b < BigInt<Base>(0L))
  {
    std::cerr << "Error: el exponente no puede ser negativo." << std::endl;
    return BigInt<Base>();
  }
  BigInt<Base> res(1L);
  for (BigInt<Base> i(0L); i < b; i = i + BigInt<Base>(1L))
    res = res * a;

  return res;
}

// template <size_t Base>
// BigInt<Base>::operator BigInt<2>()
// {
//   BigInt<2> result_bin;
//   BigInt<Base> number_aux = *this;
//   BigInt<Base> zero("0");
//   BigInt<Base> two("2");
//   int aux_sign;
//   std::vector<bool> result;
//   if (number_aux == zero)
//   {
//     result.push_back(false);
//     result_bin.SetDigits(result);
//     return result_bin;
//   }
//   if (number_aux.sign() == -1)
//   {
//     number_aux = -number_aux;
//     aux_sign = -1;
//   }

//   while (number_aux != zero)
//   {
//     result.push_back(number_aux % two == zero ? false : true);
//     number_aux = number_aux / two;
//   }

//   result.push_back(false);

//   if (aux_sign == -1)
//   {
//     result_bin.SetDigits(result);
//     result_bin = -result_bin;
//     return result_bin;
//   }
//   result_bin.SetDigits(result);
//   result_bin.sign(0);

//   return result_bin;
// }

template <size_t Base>
Number* BigInt<Base>::Add(const Number* n) const
{
  const BigInt<Base>* n1 = dynamic_cast<const BigInt<Base>*>(n);
  if (n1 == nullptr)
    return nullptr;
  return new BigInt<Base>(*this + *n1);
}

// template <size_t Base>
// Number* BigInt<Base>::Subtract(const Number* n) const
// {
//   const BigInt<Base>* n1 = dynamic_cast<const BigInt<Base>*>(n);
//   if (n1 == nullptr)
//     return nullptr;
//   return new BigInt<Base>(*this - *n1);
// }

// template <size_t Base>
// Number* BigInt<Base>::Multiply(const Number* n) const
// {
//   const BigInt<Base>* n1 = dynamic_cast<const BigInt<Base>*>(n);
//   if (n1 == nullptr)
//     return nullptr;
//   return new BigInt<Base>(*this * *n1);
// }

// template <size_t Base>
// Number* BigInt<Base>::Divide(const Number* n) const
// {
//   const BigInt<Base>* n1 = dynamic_cast<const BigInt<Base>*>(n);
//   if (n1 == nullptr)
//     return nullptr;
//   return new BigInt<Base>(*this / *n1);
// }

// template <size_t Base>
// Number* BigInt<Base>::Module(const Number* n) const
// {
//   const BigInt<Base>* n1 = dynamic_cast<const BigInt<Base>*>(n);
//   if (n1 == nullptr)
//     return nullptr;
//   return new BigInt<Base>(*this % *n1);
// }

// template <size_t Base>
// Number* BigInt<Base>::Pow(const Number* n) const
// {
//   const BigInt<Base>* n1 = dynamic_cast<const BigInt<Base>*>(n);
//   if (n1 == nullptr)
//     return nullptr;
//   return new BigInt<Base>(pow(*this, *n1));
// }


template <size_t Base>
Number& BigInt<Base>::operator=(const Number& n)
{
  const BigInt<Base>* n1 = dynamic_cast<const BigInt<Base>*>(&n);
  if (n1 == nullptr)
    return *this;
  *this = *n1;
  return *this;
}

template <size_t Base>
std::ostream& BigInt<Base>::Write(std::ostream &os) const {
  return os << *this;
}

template <size_t Base>
std::istream& BigInt<Base>::Read(std::istream &is) {
  return is >> *this;
}



template <size_t Base>
bool BigInt<Base>::CheckBase()
{
  if (Base == 2 || Base == 8 || Base == 10 || Base == 16)
    return true;
  else
    std::cout << "Error: Base no válida" << std::endl;
  return false;
}

template <size_t Base>
bool BigInt<Base>::CheckDigits(char c)
{
  switch (Base)
  {
  case 2:
    if (c == '0' || c == '1')
      return true;
    break;
  case 8:
    if (c >= '0' && c <= '7')
      return true;
    break;
  case 10:
    if (c >= '0' && c <= '9')
      return true;
    break;
  case 16:
    if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F'))
      return true;
    break;
  default:
    break;
  }
  return false;
}
