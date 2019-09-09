cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(myvector)
ADD_DEFINITIONS(-std=c++14)

include_directories (/usr/local/include)
link_directories (/usr/local/lib)

add_library(mv SHARED  myvector.h)
set_target_properties(mv PROPERTIES LINKER_LANGUAGE CXX)

add_executable (main main.cpp)
target_link_libraries (mv)
