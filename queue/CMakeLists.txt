cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(queue)
ADD_DEFINITIONS(-std=c++14)

include_directories (/usr/local/include)
link_directories (/usr/local/lib)

add_executable (queue queue.cpp)
target_link_libraries (queue)
