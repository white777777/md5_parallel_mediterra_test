//Brute-force attack against a known hash
#include <vector>
#include <iostream>
#include "Supervisor.h"
#include "md5.h"

void test(unsigned int beg, unsigned int end, const std::string& chars, const std::string & word)
{
  MD5 md5;
  std::cout << "test:" << word.c_str() << std::endl;
  std::string hash = md5.digestString(word.c_str());
  Supervisor supervisor(Task(beg, end, chars, hash));
  supervisor.Run();
  try
  {
    ITaskPtr task = supervisor.GetResultTask();
    if (task.get() == nullptr || !task->IsSolutionFound())
      throw std::logic_error("solution not found");
    if (task->GetSolution() != word)
      throw std::logic_error("wrong result");
    std::cout << "test passed" << std::endl;
  }
  catch (const std::exception& e)
  {
    std::cout << "test failed. " << e.what() << std::endl;
  }
}

void test()
{
  test(1, 1, "65-90:97-122", "A");
  test(1, 1, "65-90:97-122", "Z");
  test(1, 1, "65-90:97-122", "a");
  test(1, 1, "65-90:97-122", "z");

  test(1, 2, "65-90:97-122", "A");
  test(1, 2, "65-90:97-122", "Z");
  test(1, 2, "65-90:97-122", "a");
  test(1, 2, "65-90:97-122", "z");

  test(1, 2, "65-90:97-122", "AA");
  test(1, 2, "65-90:97-122", "zz");

  test(3, 4, "65-90:97-122", "AAA");
  test(3, 3, "65-90:97-122", "aaa");
  test(3, 3, "65-90:97-122", "zzz");
  test(3, 8, "112-116:117-122", "zzzzzz");
}

int main(int argc, char** argv)
{
  //test();
  if(argc != 5)
  {
    std::cout<<"Usage NMin NMax Chars HEXHash"<<std::endl;
    return 0;
  }
  const unsigned int beg = atoi(argv[1]);
  const unsigned int end = atoi(argv[2]);

  Supervisor supervisor(Task(beg, end, argv[3], argv[4]));
  supervisor.Run();
  ITaskPtr task = supervisor.GetResultTask();
  if (task.get() == nullptr || !task->IsSolutionFound())
    std::cout << "Solution not found" << std::endl;
  else::
    std::cout << "Solution is:" << task->GetSolution() << std::endl;
  return 0;
}