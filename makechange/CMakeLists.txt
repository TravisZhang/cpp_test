cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(makechange)
ADD_DEFINITIONS(-std=c++11)

include_directories (/usr/local/include)
link_directories (/usr/local/lib)

add_executable (makechange makechange.cpp)
target_link_libraries (makechange)
