#include <iostream>

int main() {
  int id = 0; // Define an integer variable

  // create lambda
  auto f = [](const int id) {
    std::cout << "ID = " << id << std::endl;
  }; // ID is passed as a parameter

  // execute function object and pass the parameter
  f(id);

  return 0;
}

/*
The following example illustrates how the function object is first created and
then used to pass the parameter id later in the code.
*/
