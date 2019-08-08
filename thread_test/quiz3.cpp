#include <future>
#include <iostream>
#include <thread>

class Vehicle {
public:
  // default constructor
  Vehicle() : _id(0), _name(new std::string("Default Name")) {
    std::cout << "Vehicle #" << _id << " Default constructor called"
              << std::endl;
  }

  // initializing constructor
  Vehicle(int id, std::string name) : _id(id), _name(new std::string(name)) {
    std::cout << "Vehicle #" << _id << " Initializing constructor called"
              << std::endl;
  }

  // copy constructor
  Vehicle(Vehicle const &src) {
    // QUIZ: Student code STARTS here
    _id = src._id;
    if (src._name != nullptr) {
      _name = new std::string;
      *_name = *src._name;
    }
    // QUIZ: Student code ENDS here
    std::cout << "Vehicle #" << _id << " copy constructor called" << std::endl;
  };

  // setter and getter
  void setID(int id) { _id = id; }
  int getID() { return _id; }
  void setName(std::string name) { *_name = name; }
  std::string getName() { return *_name; }

private:
  int _id;
  std::string *_name;
};

int main() {
  // create instances of class Vehicle
  Vehicle v0;                 // default constructor
  Vehicle v1(1, "Vehicle 1"); // initializing constructor

  // launch a thread that modifies the Vehicle name
  std::future<void> ftr = std::async(
      [](Vehicle v) {
        std::this_thread::sleep_for(
            std::chrono::milliseconds(500)); // simulate work
        v.setName("Vehicle 2");
      },
      v0);

  v0.setName("Vehicle 3");

  ftr.wait();
  std::cout << v0.getName() << std::endl;

  return 0;
}

/*
The problem with passing a proprietary class is that the standard copy
constructor makes a 1:1 copy of all data members, including pointers to objects.
This behavior is also referred to as "shallow copy". In the above example we
would have liked (and maybe expected) a "deep copy" of the object though, i.e. a
copy of the data to which the pointer refers. A solution to this problem is to
create a proprietary copy constructor in the class Vehicle. The following piece
of code overwrites the default copy constructor and can be modified to make a
customized copy of the data members.

Image

Expanding on the code example from above, please implement the code required for
a deep copy so that the program always prints "Vehicle 3" to the console,
regardless of the delay within the thread function.
*/
