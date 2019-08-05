#include <iostream>
#include <thread>

class Vehicle
{
public:
    Vehicle(int id) : _id(id) {}
    void operator()()
    {
        std::cout << "Vehicle #" << _id << " has been created" << std::endl;
    }

private:
    int _id;
};

int main()
{
    // create thread
    std::thread t = std::thread(Vehicle(1)); // Use copy initialization

    // do something in main()
    std::cout << "Finished work in main \n";

    // wait for thread to finish
    t.join();

    return 0;
}

/*
Whichever option we use, the idea is the same: the function object is copied into internal storage accessible to the new thread, and the new thread invokes the operator (). The Vehicle class can of course have data members and other member functions too, and this is one way of passing data to the thread function: pass it in as a constructor argument and store it as a data member:

Image

In the above code example, the class Vehicle has a constructor that takes an integer and it will store it internally in a variable _id. In the overloaded function call operator, the vehicle id is printed to the console. In main(), we are creating the Vehicle object using copy initialization. The output of the program is given below:

Image

As can easily be seen, the integer ID has been successfully passed into the thread function.
*/
