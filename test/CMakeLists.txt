# Download and unpack test and mock frameworks at configure
configure_file(CMakeLists.txt.in test-mock-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/test/test-mock-download )
if(result)
  message(FATAL_ERROR "CMake step for test/mock failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build . 
  RESULT_VARIABLE result 
WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/test/test-mock-download ) 
if(result) 
  message(FATAL_ERROR "Build step for test/mock failed: ${result}") 
endif() 

include_directories(${CMAKE_BINARY_DIR}/catch/single_include)
include_directories(${CMAKE_BINARY_DIR}/fakeit/single_header/catch)

if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANGXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0") # debug, no optimisation
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage") # enabling coverage
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -W4")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src/)

file(GLOB_RECURSE TEST_SOURCES "*.*pp")

foreach(f ${TEST_SOURCES})
    file(RELATIVE_PATH SRCGR ${CMAKE_CURRENT_SOURCE_DIR} ${f})
    string(REGEX REPLACE "(.*)(/[^/]*)$" "\\1" SRCGR ${SRCGR})
	get_filename_component(FNAME ${f} NAME)
	if (NOT ${SRCGR} STREQUAL ${FNAME})
		source_group("${SRCGR}" FILES ${f})
	endif()
endforeach()

add_executable(gluino_test ${TEST_SOURCES})
target_link_libraries(gluino_test gluino)
