cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(inverse_matrix)
ADD_DEFINITIONS(-std=c++11)

find_package(Eigen3 REQUIRED)

include_directories (/usr/local/include)
link_directories (/usr/local/lib)

add_executable (inverse_matrix inverse_matrix.cpp)
target_link_libraries (inverse_matrix)

target_include_directories(inverse_matrix
PUBLIC
    ${EIGEN3_INCLUDE_DIRS}
)
