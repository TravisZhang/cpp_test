cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(butterworth)
ADD_DEFINITIONS(-std=c++11)

include_directories (/usr/local/include)
link_directories (/usr/local/lib)

add_executable (butterworth iir_filter_indirect.cpp)
target_link_libraries (butterworth)
