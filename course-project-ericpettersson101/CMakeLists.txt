cmake_minimum_required (VERSION 2.8.11)

# set default build to debug
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Release or Debug" FORCE)
endif(NOT CMAKE_BUILD_TYPE)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall" CACHE INTERNAL "")

# get folder name as project name
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})

# defince cmake variables for file locations
file(GLOB USER_FILES_1
"hash.cpp"
"hash.hpp"
"PriorityQueue.cpp"
"PriorityQueue.hpp"
"test.txt"
"./build/test.txt"
)

# create an executables in the app folder
add_executable( run_app "driver.cpp" ${USER_FILES_1} )
