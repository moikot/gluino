set(CMAKE_BUILD_TYPE Debug)

if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANGXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -fno-exceptions -std=c++11 -Wall")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0") # debug, no optimisation
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage") # enabling coverage
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -W4")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE SOURCES "*.*pp")

foreach(f ${SOURCES})
    file(RELATIVE_PATH SRCGR ${CMAKE_CURRENT_SOURCE_DIR} ${f})
    string(REGEX REPLACE "(.*)(/[^/]*)$" "\\1" SRCGR ${SRCGR})
    source_group("${SRCGR}" FILES ${f})
endforeach()

if (CMAKE_COMPILER_IS_GNUCXX)
  add_library(gluino SHARED ${SOURCES})
else()
  add_library(gluino STATIC ${SOURCES})
endif()
