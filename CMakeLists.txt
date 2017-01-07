cmake_minimum_required(VERSION 2.8.2)
set(CMAKE_MACOSX_RPATH 1)

project(gluino)
add_subdirectory(src)
add_subdirectory(test)

enable_testing()
add_test(GluinoTest test/gluino_test)
