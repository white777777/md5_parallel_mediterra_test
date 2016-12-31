#include "Worker.h"
#include <iostream>
Worker::Worker(ISupervisor* supervisor) :_supervisor(supervisor)
{
}

void Worker::Calc()
{
  while (!_isCmdToStop)
  {
    ITaskPtr task = _supervisor->GetTask();
    if (task.get() == nullptr)
      break;
    task->Calc();
    if (task->IsSolutionFound())
    {
      _resultTask = std::move(task);
      break;
    }
  }
  _isFinished = true;
  _supervisor->SignalFinishedCalc();
}

void Worker::Stop()
{
  _isCmdToStop = true;
}

bool Worker::IsFinished()
{
  return _isFinished;
}

ITaskPtr Worker::GetTask()
{
  return std::move(_resultTask);
}
