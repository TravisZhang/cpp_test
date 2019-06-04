cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(yaml_test)
ADD_DEFINITIONS(-std=c++14)

include_directories (/usr/local/include)
link_directories (/usr/local/lib)

add_executable (yaml_test yaml_test.cpp)
target_link_libraries (yaml_test)
