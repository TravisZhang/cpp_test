cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(list_reverse)
ADD_DEFINITIONS(-std=c++11)

include_directories (/usr/local/include)
link_directories (/usr/local/lib)

add_executable (list_reverse list_reverse.cpp)
target_link_libraries (list_reverse)
