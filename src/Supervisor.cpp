#include "Supervisor.h"
#include <iostream>
#include <algorithm>
#include <string>
#include "Worker.h"

Supervisor::Supervisor(const Task&& task) : _mainTask(task)
{

}

ITaskPtr Supervisor::GetTask()
{
  std::lock_guard<std::mutex> lock(_mutexQueue);
  const size_t defaultSplitSize = 1000;
  if (_mainTask.IsEmpty())
    return nullptr;
  return _mainTask.Split(defaultSplitSize);
}

void Supervisor::Run()
{
  std::unique_lock<std::mutex> lkFinishedCalc(_mutexWorkerFinishedCalc);

  unsigned nWorkers = std::thread::hardware_concurrency();
  std::list<std::thread> threads;

  _nFinishedWorkers = 0;
  for (size_t i = 0; i < nWorkers; ++i)
  {
    _workers.emplace_back(this);
    threads.emplace_back(&Worker::Calc, &_workers.back());
  }
  do
  {
    _cv.wait(lkFinishedCalc);

    for (Worker & worker : _workers)
    {
      if (!worker.IsFinished())
        continue;
      if (_resultTask.get() != nullptr)
        continue;
      ITaskPtr task = worker.GetTask();
      if (task.get() != nullptr && task->IsSolutionFound())
      {
        finishAllWorkers();
        _resultTask = std::move(task);
      }
    }
  } while (_nFinishedWorkers != nWorkers);
  for (std::thread & thread:threads)
    thread.join();
}

void Supervisor::finishAllWorkers()
{
  for (Worker & worker: _workers)
    worker.Stop();
}

void Supervisor::SignalFinishedCalc()
{
  std::lock_guard<std::mutex> lk(_mutexWorkerFinishedCalc);
  ++_nFinishedWorkers;
  _cv.notify_one();
}
