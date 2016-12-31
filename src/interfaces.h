#pragma once
#include <memory>
#include <string>

class ITask;
typedef std::unique_ptr<ITask> ITaskPtr;
class ITask
{
public:
  virtual void Calc() = 0;
  virtual ITaskPtr Split(unsigned int nOps) = 0;
  virtual bool IsSolutionFound() const = 0;
  virtual std::string GetSolution() const = 0;
  virtual bool IsEmpty() const = 0;
};

class ISupervisor
{
public:
  virtual ITaskPtr GetTask() = 0;
  virtual void SignalFinishedCalc() = 0;
};
