cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(cam)
ADD_DEFINITIONS(-std=c++14)

include_directories (/usr/local/include)
link_directories (/usr/local/lib)

add_executable (cam cam.cpp)
#target_link_libraries (cat)
