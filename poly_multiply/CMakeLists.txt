cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(poly_mul)
ADD_DEFINITIONS(-std=c++14)

include_directories (/usr/local/include)
link_directories (/usr/local/lib)

add_executable (poly_mul poly_mul.cpp)
target_link_libraries (poly_mul)
