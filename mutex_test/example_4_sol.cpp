#include <iostream>
#include <mutex>
#include <thread>

std::mutex mutex1, mutex2;

void ThreadA() {
  // Solves deadlock problem
  mutex1.lock();
  std::cout << "Thread A" << std::endl;
  mutex2.lock();
  mutex2.unlock();
  mutex1.unlock();
}

void ThreadB() {
  // Solves deadlock problem
  mutex1.lock();
  std::cout << "Thread B" << std::endl;
  mutex2.lock();
  mutex1.unlock();
  mutex2.unlock();
}

void ExecuteThreads() {
  std::thread t1(ThreadA);
  std::thread t2(ThreadB);

  t1.join();
  t2.join();

  std::cout << "Finished" << std::endl;
}

int main() {
  ExecuteThreads();

  return 0;
}
/*
One way to avoid such a deadlock would be to number all resources and require
that processes request resources only in strictly increasing (or decreasing)
order. Please try to manually rearrange the locks and unlocks in a way that the
deadlock does not occur and the following text is printed to the console:
*/
