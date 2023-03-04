#pragma once
#include "BigInt.h"

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




template <>
class BigInt<2>: public Number
{
public:
  BigInt(long = 0);
  BigInt(std::string);
  BigInt(const char *);
  BigInt(const BigInt<2> &);
  ~BigInt();

  BigInt<2> operator=(const BigInt<2> &);
  std::vector<bool> GetDigits() const;
  void SetDigits(std::vector<bool>);

  friend std::ostream &operator<< <2>(std::ostream &, const BigInt<2> &);
  friend std::istream &operator>><2>(std::istream &, BigInt<2> &);

  int sign() const;
  void sign(int);
  bool operator[](int) const;

  friend bool operator==<2>(const BigInt<2> &, const BigInt<2> &);
  bool operator!=(const BigInt<2> &) const;
  friend bool operator><2>(const BigInt<2> &, const BigInt<2> &);
  bool operator>=(const BigInt<2> &) const;
  friend bool operator< <2>(const BigInt<2> &, const BigInt<2> &);
  bool operator<=(const BigInt<2> &) const;

  BigInt<2> &operator++();
  BigInt<2> operator++(int);
  BigInt<2> &operator--();
  BigInt<2> operator--(int);

  BigInt<2> operator+(const BigInt<2> &) const;
  BigInt<2> operator-(const BigInt<2> &) const;
  BigInt<2> operator-() const;
  BigInt<2> operator*(const BigInt<2> &) const;
  BigInt<2> operator/(const BigInt<2> &) const;
  BigInt<2> operator%(const BigInt<2> &) const;
  friend BigInt<2> pow<2>(const BigInt<2> &, const BigInt<2> &);

  Number* Add(const Number*) const override;
  Number*Subtract(const Number*) const override;
  Number *Multiply(const Number *) const override;
  Number *Divide(const Number *) const override;
  Number *Module(const Number *) const override;
  Number *Pow(const Number *) const override;

  Number& operator=(const Number&) override;
  
  std::ostream& Write(std::ostream&) const override;
  std::istream& Read(std::istream&) override;



  BigInt<2> FillSign(int) const;

  template <size_t Base>
  operator BigInt<Base>();

private:
  std::vector<bool> digits_;

  int sign_; // 1 negative, 0 positive
};
