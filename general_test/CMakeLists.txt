cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(general_test)
ADD_DEFINITIONS(-std=c++11)

include_directories (/usr/local/include)
link_directories (/usr/local/lib)

add_executable (general_test general_test.cpp)
target_link_libraries (general_test)
