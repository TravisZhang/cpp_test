#include <algorithm>
#include <future>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

std::mutex mtx;
double result;

void printResult(int denom) {
  std::cout << "for denom = " << denom << ", the result is " << result
            << std::endl;
}

void divideByNumber(double num, double denom) {
  mtx.lock();
  try {
    // divide num by denom but throw an exception if division by zero is
    // attempted
    if (denom != 0) {
      result = num / denom;
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
      printResult(denom);
    } else {
      throw std::invalid_argument("Exception from thread: Division by zero!");
    }
  } catch (const std::invalid_argument &e) {
    // notify the user about the exception and return
    std::cout << e.what() << std::endl;
    return;
  }
  mtx.unlock();
}

int main() {
  // create a number of threads which execute the function "divideByNumber" with
  // varying parameters
  std::vector<std::future<void>> futures;
  for (double i = -5; i <= +5; ++i) {
    futures.emplace_back(
        std::async(std::launch::async, divideByNumber, 50.0, i));
  }

  // wait for the results
  std::for_each(futures.begin(), futures.end(),
                [](std::future<void> &ftr) { ftr.wait(); });

  return 0;
}

/*
In this example, a number of tasks is started up in main() with the method
divideByNumber as the thread function. Each task is given a different
denominator and within divideByNumber a check is performed to avoid a division
by zero. If denom should be zero, an exception is thrown. In the catch-block,
the exception is caught, printed to the console and then the function returns
immediately. The output of the program changes with each execution and might
look like this:

Image

As can easily be seen, the console output is totally mixed up and some results
appear multiple times. There are several issues with this program, so let us
look at them in turn:

    First, the thread function writes its result to a global variable which is
passed to it by reference. This will cause a data race as illustrated in the
last section. The sleep_for function exposes the data race clearly. Second, the
result is printed to the console by several threads at the same time, causing
the chaotic output.

*/
