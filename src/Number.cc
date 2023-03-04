#include "../include/Number.h"


Number::~Number() {}

Number* Number::create(size_t base, const std::string& number)
{
  Number* n = nullptr;
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

std::ostream& operator<<(std::ostream& os, const Number& n)
{
  return n.Write(os);
}

std::istream& operator>>(std::istream& is, Number& n)
{
  return n.Read(is);
}