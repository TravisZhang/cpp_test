#include <iostream>
#include <thread>

class Vehicle {
public:
  void operator()() {
    std::cout << "Vehicle object has been created \n" << std::endl;
  }
};

int main() {
  Vehicle v;

  // create thread
  std::thread t(v); // C++'s most vexing parse

  // do something in main()
  std::cout << "Finished work in main \n";

  // wait for thread to finish
  t.join();

  return 0;
}

/*
The std::thread constructor can also be called with instances of classes that
implement the function-call operator. In the following, we will thus define a
class that has an overloaded ()-operator. In preparation for the final project
of this course, which will be a traffic simulation with vehicles moving through
intersections in a street grid, we will define a (very) early version of the
Vehicle class in this example:

Image

When executing this code, the clang++ compiler generates a warning, which is
followed by an error:

Image

A similar error is shown when compiling with g++, so you will see an error when
you compile example_1.cpp!

The extra parentheses suggested by the compiler avoid what is known as C++'s
"most vexing parse", which is a specific form of syntactic ambiguity resolution
in the C++ programming language.

The expression was coined by Scott Meyers in 2001, who talks about it in details
in his book "Effective STL". The "most vexing parse" comes from a rule in C++
that says that anything that could be considered as a function declaration, the
compiler should parse it as a function declaration - even if it could be
interpreted as something else.
*/