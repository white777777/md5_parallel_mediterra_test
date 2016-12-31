#include "Task.h"
#include <list>
#include "interfaces.h"
#include <mutex>
#include <thread>
#include <condition_variable>
#include <Worker.h>

class Supervisor: public ISupervisor
{
public:
  Supervisor(const Task&& task);
  
  ITaskPtr GetTask() override;
  
  ITaskPtr GetResultTask()
  {
    return std::move(_resultTask);
  }

  void Run();
    
  void finishAllWorkers();

  void SignalFinishedCalc() override;
  
private:
  Task _mainTask;
  std::list<Worker> _workers;
  ITaskPtr _resultTask;
  std::mutex _mutexQueue;

  std::condition_variable _cv;
  std::mutex _mutexWorkerFinishedCalc;
  size_t _nFinishedWorkers;
};
