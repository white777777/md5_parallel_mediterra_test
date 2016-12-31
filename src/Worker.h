#pragma once
#include "interfaces.h"

class Worker
{
public:
  Worker(ISupervisor* supervisor);
  void Stop();
  bool IsFinished();
  ITaskPtr GetTask();
  void Calc();
private:
  ISupervisor* _supervisor;
  bool _isCmdToStop = false;
  ITaskPtr _resultTask;
  bool _isFinished = false;
};
