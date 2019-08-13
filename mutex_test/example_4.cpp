#include <iostream>
#include <mutex>
#include <thread>

std::mutex mutex1, mutex2;

void ThreadA() {
  // Creates deadlock problem
  mutex2.lock();
  std::cout << "Thread A" << std::endl;
  mutex1.lock();
  mutex2.unlock();
  mutex1.unlock();
}

void ThreadB() {
  // Creates deadlock problem
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
ThreadA and ThreadB both require access to the console. Unfortunately, they
request this resource which is protected by two mutexes in different order. If
the two threads work interlocked so that first ThreadA locks mutex 1, then
ThreadB locks mutex 2, the program is in a deadlock: Each thread tries to lock
the other mutex and needs to wait for its release, which never comes. The
following figure illustrates the problem graphically.
*/
