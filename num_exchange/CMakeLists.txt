cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(num_exchange)
ADD_DEFINITIONS(-std=c++14)

include_directories (/usr/local/include)
link_directories (/usr/local/lib)

add_executable (num_exchange num_exchange.cpp)
target_link_libraries (num_exchange)
