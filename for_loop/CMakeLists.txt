cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(for_loop)
ADD_DEFINITIONS(-std=c++11)

include_directories (/usr/local/include)
link_directories (/usr/local/lib)

add_executable (for_loop for_loop.cpp)
target_link_libraries (for_loop)
