cmake_minimum_required(VERSION 2.8.2)
set(CMAKE_MACOSX_RPATH 1)
project(gluino)

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
  set(CMAKE_COMPILER_IS_CLANGXX true)
endif()

add_subdirectory(src)
add_subdirectory(test)

enable_testing()
add_test(GluinoTest test/gluino_test)
