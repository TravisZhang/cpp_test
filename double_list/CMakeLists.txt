cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(double_list)
ADD_DEFINITIONS(-std=c++14)

include_directories (/usr/local/include)
link_directories (/usr/local/lib)

add_executable (double_list double_list.cpp)
target_link_libraries (double_list)
