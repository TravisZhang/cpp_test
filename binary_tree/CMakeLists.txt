cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(binary_tree)
ADD_DEFINITIONS(-std=c++11)

include_directories (/usr/local/include)
link_directories (/usr/local/lib)

add_executable (binary_tree binary_tree.cpp)
target_link_libraries (binary_tree)
