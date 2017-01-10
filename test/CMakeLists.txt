# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/test/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/test/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANGXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -fno-exceptions -std=c++11 -Wall")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0") # debug, no optimisation
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage") # enabling coverage
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -W4")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src/)

file(GLOB_RECURSE TEST_SOURCES "*.cpp")

foreach(f ${TEST_SOURCES})
    file(RELATIVE_PATH SRCGR ${CMAKE_CURRENT_SOURCE_DIR} ${f})
    string(REGEX REPLACE "(.*)(/[^/]*)$" "\\1" SRCGR ${SRCGR})
    source_group("${SRCGR}" FILES ${f})
endforeach()

add_executable(gluino_test ${TEST_SOURCES})
target_link_libraries(gluino_test gluino gtest_main gmock_main)
