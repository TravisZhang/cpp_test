#include <iostream>
#include <thread>

class Vehicle
{
public:
    Vehicle() : _id(0) {}
    void addID(int id) { _id = id; }
    void setName(std::string name) { _name = name; }
    void printID()
    {
        std::cout << "Vehicle ID=" << _id << std::endl;
    }
    // TODO: Modify the Vehicle class as indicated in the instructions on the left.
    void printName()
    {
        std::cout << "Vehicle name=" << _name << std::endl;
    }
private:
    int _id;
    std::string _name;
};

int main()
{
    std::string name("MyThread");
    // create thread
    std::shared_ptr<Vehicle> v(new Vehicle);
    std::thread t = std::thread(&Vehicle::addID, v, 1); // call member function on object v
    std::thread t1 = std::thread(&Vehicle::setName, v, name); // call member function on object v
    
    // TODO: Modify the main to start setName as a thread.
    // Also, add code to main to print the name of the vehicle.
    
    // wait for thread to finish
    t.join();
    t1.join();
    
    // print Vehicle id
    v->printID();
    v->printName();
    
    return 0;
}

/*
Change the code from the previous example in a way that a new member _name variable of type std::string is added to the Vehicle class. Then, define a function setName which takes a string as an argument and assigns this to _name. The function setName needs to be started as a thread from main. Also, add a function printName to the Vehicle class which is used at the end of main to print the name to the console.
*/
