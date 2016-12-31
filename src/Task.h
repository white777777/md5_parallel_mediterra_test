#include <vector>
#include "BigInt.h"
#include "interfaces.h"

class Task: public ITask
{
public:
  Task(size_t lenMin, size_t lenMax, const std::string& charsStr, const std::string& hash);
  
  void Calc() override;

  bool IsEmpty() const override
  {
    return !(_beg < _end);
  }
  
  std::unique_ptr<ITask> Split(unsigned int nOps) override;
  
  bool IsSolutionFound() const override;
  
  std::string GetSolution() const override;
  
private:
  void reset();
  
  std::string getPhrase() const;
  
  bool parseChars(const std::string& str);
  
private:
  std::vector<char> _chars;
  std::string _hash;
  BigInt _beg, _end, _currentIndex;
  bool _isSolutionFound = false;
  std::string _result;
};
