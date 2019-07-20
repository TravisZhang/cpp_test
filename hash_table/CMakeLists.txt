cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(hash_table)
ADD_DEFINITIONS(-std=c++11)

include_directories (/usr/local/include)
link_directories (/usr/local/lib)

add_executable (hash_table hash_table.cpp)
target_link_libraries (hash_table)
