cmake_minimum_required(VERSION 3.19)
project(CoursesAnalyzer)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/Parser)
include_directories(${CMAKE_SOURCE_DIR}/Course)
include_directories(${CMAKE_SOURCE_DIR}/CoursesAnalyzer)

add_executable(CoursesAnalyzer main.cpp)