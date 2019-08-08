#include <chrono>
#include <cmath>
#include <future>
#include <iostream>
#include <thread>
#include <vector>

void workerFunction(int n) {
  // print system id of worker thread
  std::cout << "Worker thread id = " << std::this_thread::get_id() << std::endl;

  // perform work
  for (int i = 0; i < n; ++i) {
    sqrt(12345.6789);
  }
}

int main() {
  // print system id of worker thread
  std::cout << "Main thread id = " << std::this_thread::get_id() << std::endl;

  // start time measurement
  std::chrono::high_resolution_clock::time_point t1 =
      std::chrono::high_resolution_clock::now();

  // launch various tasks
  std::vector<std::future<void>> futures;
  int nLoops = 10, nThreads = 5;
  for (int i = 0; i < nThreads; ++i) {
    futures.emplace_back(std::async(std::launch::any, workerFunction, nLoops));
  }

  // wait for tasks to complete
  for (const std::future<void> &ftr : futures)
    ftr.wait();

  // stop time measurement and print execution time
  std::chrono::high_resolution_clock::time_point t2 =
      std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
  std::cout << "Execution finished after " << duration << " microseconds"
            << std::endl;

  return 0;
}

/*
In this section, we want to explore the influence of the number of threads on
the performance of a program with respect to its overall runtime. The example
below has a thread function called "workerThread" which contains a loop with an
adjustable number of cycles in which a mathematical operation is performed.

Image

In main(), a for-loop starts a configurable number of tasks that can either be
executed synchronously or asynchronously. As an experiment, we will now use a
number of different parameter settings to execute the program and evaluate the
time it takes to finish the computations. The idea is to gauge the effect of the
number of threads on the overall runtime:

    int nLoops = 1e7 , nThreads = 4 , std::launch::async

    Image

    With this set of parameters, the high workload is computed in parallel, with
an overall runtime of ~45 milliseconds.

    int nLoops = 1e7 , nThreads = 5 , std::launch::deferred

    Image

    The difference to the first set of parameters is the synchronous execution
of the tasks - all computations are performed sequentially - with an overall
runtime of ~126 milliseconds. While impressive with regard to the achieved
speed-up, the relative runtime advantage of setting 1 to this settings is at a
factor of ~2.8 on a 4-core machine.

    int nLoops = 10 , nThreads = 5 , std::launch::async

    Image

    In this parameter setting, the tasks are run in parallel again but with a
significantly lower number of computations: The thread function now computes
only 10 square roots where with settings 1 and 2 a total of 10.000.000 square
roots were computed. The overall runtime of this example therefore is
significantly lower with only ~3 milliseconds.

    int nLoops = 10 , nThreads = 5 , std::launch::deferred

    Image

    In this last example, the same 10 square roots are computed sequentially.
Surprising, the overall runtime is at only 0.01 milliseconds - an astounding
difference to the asynchronous execution and a stark reminder that starting and
managing threads takes a significant amount of time. It is therefore not a
general advantage if computations are performed in parallel: It must be
carefully weighed with regard to the computational effort whether
parallelization makes sense.

*/
