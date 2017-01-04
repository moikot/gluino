cmake_minimum_required (VERSION 2.8)
project(gluino)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(COVERALLS "Turn on coveralls support" OFF)
option(COVERALLS_UPLOAD "Upload the generated coveralls json" ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
	${PROJECT_SOURCE_DIR}/coveralls-cmake/cmake)

if (COVERALLS)
	include(Coveralls)
  coveralls_turn_on_coverage()
endif()

# Create the library -fno-exceptions
include_directories("src")

set(CMAKE_CXX_FLAGS "-fno-rtti -std=c++11 -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0") # debug, no optimisation
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage") # enabling coverage

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.hpp")

set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
add_library(gluino SHARED ${SOURCES})

# include_directories(${PROJECT_SOURCE_DIR})

# Setup the coveralls target and tell it to gather
# coverage data for all the lib sources.
if (COVERALLS)
	coveralls_setup("${SOURCES}" ${COVERALLS_UPLOAD}
        "${PROJECT_SOURCE_DIR}/coveralls-cmake/cmake")
endif()

# Add a test for the library.
enable_testing()

file(GLOB_RECURSE TEST_SOURCES "test/*.cpp")
include_directories("test")
add_executable(gluino_test ${TEST_SOURCES})
target_link_libraries(gluino_test gluino)
add_test(GluinoTest gluino_test)
