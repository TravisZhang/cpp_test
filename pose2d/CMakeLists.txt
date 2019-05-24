cmake_minimum_required(VERSION 3.0)

project(pose2d)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

include_directories (/usr/local/include)
link_directories (/usr/local/lib)

include_directories(${pose2d_SOURCE_DIR}/include)

#add_library(${PROJECT_NAME} SHARED   include/pose2d.h)

#set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

add_executable (pose2d src/pose2d.cpp)
target_link_libraries (${PROJECT_NAME})
