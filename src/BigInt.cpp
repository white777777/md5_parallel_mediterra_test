#include "BigInt.h"



BigInt::BigInt(TBase base, size_t len) : base(base)
{
  Reset(len);
}

BigInt::BigInt() : base(0)
{

}

BigInt BigInt::BigIntFromInt(TBase base, unsigned int val)
{
  BigInt bigInt(base, 0);
  unsigned int tmp = val;
  do
  {
    int ost = tmp%base;
    tmp = tmp / base;
    bigInt.data.push_back(ost);
  } while (tmp != 0);
  return bigInt;
}

void BigInt::Reset(size_t len)
{
  data.resize(len, 0);
}

void BigInt::SetToMax()
{
  data.assign(data.size(), base - 1);
}

void BigInt::Add(unsigned int val)
{
  Add(BigInt::BigIntFromInt(this->base, val));
}

void BigInt::Add(BigInt over)
{
  if (base != over.base)
    throw std::logic_error("unimplmented. base != over.base");
  if (over.data.size() > this->data.size())
    std::swap(*this, over);
  over.data.resize(data.size(), 0);
  TBase up = 0;
  for (size_t i = 0; i < over.data.size(); ++i)
  {
    TBase sum = data[i] + over.data[i] + up;
    data[i] = sum%base;
    up = sum / base;
  }
  if (up != 0)
  {
    data.push_back(0);
  }
}

void BigInt::Minus(BigInt over)
{
  if (*this < over)
    throw std::invalid_argument("this < over");
  TBase up = 0;
  over.data.resize(data.size(), 0);
  for (size_t i = 0; i < over.data.size(); ++i)
  {
    int sum = data[i] - over.data[i] + up;
    data[i] = (sum + base)%base;
    up = sum / base;
  }
}

