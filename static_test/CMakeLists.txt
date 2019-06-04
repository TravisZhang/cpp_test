cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(static)
ADD_DEFINITIONS(-std=c++17)

include_directories (/usr/local/include)
link_directories (/usr/local/lib)

add_executable (static static.cpp)
target_link_libraries (static)
