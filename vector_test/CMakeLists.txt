cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(v_test)
ADD_DEFINITIONS(-std=c++11)

include_directories (/usr/local/include)
link_directories (/usr/local/lib)

add_executable (v_test v_test.cpp)
target_link_libraries (v_test)
