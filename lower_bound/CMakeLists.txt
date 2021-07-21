cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(lower_bound)
ADD_DEFINITIONS(-std=c++11)

include_directories (/usr/local/include)
link_directories (/usr/local/lib)

add_executable (lower_bound lower_bound.cpp)
target_link_libraries (lower_bound)
