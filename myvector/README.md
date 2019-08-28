# myvector project

This is a project that simulates most of the functionalities of the std::vector library. 
The `myvector.h` contains a class called `Myvector` that is the main class to fulfill the functionality.
The `main.cpp` contains testing codes for member functions of class `Myvector`.

## To setup and compile in Udacity Ubuntu workspace:

1. Create a folder called `build`, and cd into it.
```
mkdir build && cd build
```
2. Run the following command to compile the code
```
cmake .. && make
```
3. Run the following command to test the code
```
./main
```

## The following rubric points are satisfied:

1. All the required rubric points.

2. The project demonstrates an understanding of C++ functions and control structures.

3. The project uses Object Oriented Programming techniques. (l10)

4. Classes use appropriate access specifiers for class members. (l12, l269)

5. Class constructors utilize member initialization lists. (l18)

6. Classes abstract implementation details from their interfaces.

7. Classes encapsulate behavior. (l244 -> l250)

8. Templates generalize functions in the project. (l9)

9. The project makes use of references in function declarations. (l45, l80, l124, l137, l167, l203, l252, l253, l263)

10. The project uses destructors appropriately. (l226)

11. The project follows the Rule of 5. (l80, l123, l167, l203, l226)

12. The project uses move semantics to move data, instead of copying it, where possible. (l124, l203)

