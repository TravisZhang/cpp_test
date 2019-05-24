cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(magic_matrix)
ADD_DEFINITIONS(-std=c++11)

include_directories (/usr/local/include)
link_directories (/usr/local/lib)

add_executable (magic_matrix magic_matrix.cpp)
target_link_libraries (magic_matrix)
