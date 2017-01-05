cmake_minimum_required(VERSION 2.8)
enable_testing()
project(gluino)
add_subdirectory(test)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -fno-exceptions -std=c++11 -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0") # debug, no optimisation
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage") # enabling coverage

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/)

file(GLOB_RECURSE SOURCES "src/*.cpp")

set(CMAKE_MACOSX_RPATH 1)
add_library(gluino SHARED ${SOURCES})
