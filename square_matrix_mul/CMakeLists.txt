cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(square_matrix_mul)
ADD_DEFINITIONS(-std=c++11)

include_directories (/usr/local/include)
link_directories (/usr/local/lib)

add_executable (square_matrix_mul square_matrix_mul.cpp)
target_link_libraries (square_matrix_mul)
