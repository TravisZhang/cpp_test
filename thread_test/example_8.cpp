#include <iostream>
#include <thread>

class Vehicle {
public:
  void operator()() {
    std::cout << "Vehicle object has been created \n" << std::endl;
  }
};

int main() {
  // create thread
  // std::thread t0(Vehicle()); // C++'s most vexing parse

  std::thread t1((Vehicle())); // Add an extra pair of parantheses

  std::thread t2 = std::thread(Vehicle()); // Use copy initialization

  std::thread t3{Vehicle()}; // Use uniform initialization with braces

  // do something in main()
  std::cout << "Finished work in main \n";

  // wait for thread to finish
  t1.join();
  t2.join();
  t3.join();

  return 0;
}

/*
In the previous code example, the line

Image

is seemingly ambiguous, since it could be interpreted either as

    a variable definition for variable t of class std::thread, initialized with
an anonymous instance of class Vehicle or a function declaration for a function
t that returns an object of type std::thread and has a single (unnamed)
parameter that is a pointer to function returning an object of type Vehicle

Most programmers would presumable expect the first case to be true, but the C++
standard requires it to be interpreted as the second - hence the compiler
warning.

There are three ways of forcing the compiler to consider the line as the first
case, which would create the thread object we want:

    Add an extra pair of parentheses
    Use copy initialization
    Use uniform initialization with braces

The following code shows all three variants:

Image

The output of this code sample shows that all three threads are executed and the
Vehicle object is properly initialized:

Image
*/
