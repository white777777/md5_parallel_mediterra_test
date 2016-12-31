#include "Task.h"
#include "md5.h"
#include <sstream>
#include <cmath>

Task::Task(size_t lenMin, size_t lenMax, const std::string& charsStr, const std::string& hash)
{
  if (!parseChars(charsStr))
    throw std::invalid_argument("Wrong charsStr format");
  _beg = BigInt(_chars.size(), lenMin);
  _end = BigInt(_chars.size(), lenMax);
  _end.SetToMax();
  _end.Add(1);
  _hash = hash;
  reset();
}

void Task::Calc()
{
  MD5 md5;
  while (_currentIndex < _end)
  {
    std::string str = getPhrase();
    if (strcmp(md5.digestString(str.c_str()), _hash.c_str()) == 0)
    {
      _isSolutionFound = true;
      _result = str;
      break;
    }
    _currentIndex.Add(1);
  }
}

std::unique_ptr<ITask> Task::Split(unsigned int nOps)
{
  std::unique_ptr<Task> smallTask = std::make_unique<Task>(*this);

  BigInt delim = _beg;
  delim.Add(nOps);
  delim = delim < _end ? delim : _end;
  smallTask->_end = delim;
  smallTask->reset();

  _beg = delim;
  reset();

  return std::move(smallTask);
}

bool Task::IsSolutionFound() const
{
  return _isSolutionFound;
}

std::string Task::GetSolution() const
{
  return _result;
}

void Task::reset()
{
  _isSolutionFound = false;
  _result = "";
  _currentIndex = _beg;
}

std::string Task::getPhrase() const
{
  std::string str;
  const size_t size = _currentIndex.data.size();
  str.resize(size);
  for (size_t i = 0; i < size; ++i)
    str[size-i-1] = _chars[_currentIndex.data[i]];
  return str;
}

bool Task::parseChars(const std::string& str)
{
  _chars.clear();
  std::stringstream ss;
  ss << str;
  try
  {
    while (!ss.eof())
    {
      char ch;
      unsigned int beg, end;
      ss >> beg;
      ss >> ch;
      if (ch != '-')
        return false;
      ss >> end;
      for (unsigned int i = beg; i <= end; ++i)
        _chars.push_back(i);
      if (!ss.eof())
      {
        ss >> ch;
        if (ch != ':')
          return false;
      }
    }
  }
  catch (...)
  {
    return false;
  }
  if (_chars.empty())
    return false;
  return true;
}
