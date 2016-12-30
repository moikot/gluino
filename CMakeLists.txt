cmake_minimum_required (VERSION 2.6)
project(Gluino)

set (CMAKE_CXX_FLAGS "-fno-rtti -fno-exceptions -std=c++11 -Isrc -Wall")
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.hpp")

set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
add_library(gluino SHARED ${SOURCES})
