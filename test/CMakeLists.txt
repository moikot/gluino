set(CMAKE_BUILD_TYPE Debug)

#-fno-exceptions
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -std=c++11 -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0") # debug, no optimisation
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage") # enabling coverage

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src/)

file(GLOB_RECURSE SOURCES "../src/*.cpp")

set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
add_library(gluino SHARED ${SOURCES})

file(GLOB_RECURSE TEST_SOURCES "*.cpp")
include_directories("test")
add_executable(gluino_test ${TEST_SOURCES})
target_link_libraries(gluino_test gluino)
add_test(GluinoTest gluino_test)
