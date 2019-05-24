cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(max_subarray)
ADD_DEFINITIONS(-std=c++11)

include_directories (/usr/local/include)
link_directories (/usr/local/lib)

add_executable (max_subarray max_subarray.cpp)
target_link_libraries (max_subarray)
