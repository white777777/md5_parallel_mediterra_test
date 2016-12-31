#include <vector>

class BigInt
{
public:
  typedef unsigned int TBase;
  BigInt();

  BigInt(TBase base, size_t len);

  static BigInt BigIntFromInt(TBase base, unsigned int val);

  void Reset(size_t len);

  void SetToMax();

  void Add(BigInt over);

  void Add(unsigned int val);

  void Minus(BigInt over);

  friend bool operator<(const BigInt & lhs, const BigInt & rhs)
  {
    if (lhs.data.size() < rhs.data.size())
      return true;
    if (lhs.data.size() > rhs.data.size())
      return false;
    for (size_t i = lhs.data.size(); i > 0; --i)
    {
      const int j = i - 1;
      if (lhs.data[j] < rhs.data[j])
        return true;
      if (lhs.data[j] > rhs.data[j])
        return false;
    }
    return false; //equal
  }

  TBase base;
  std::vector<TBase> data;
};
