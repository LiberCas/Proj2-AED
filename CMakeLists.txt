cmake_minimum_required(VERSION 3.20)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(untitled main.cpp src/Interface/System.h src/Interface/System.cpp src/Controller.cpp src/Controller.h src/Graph.cpp src/Graph.h src/StopEdge.cpp src/StopEdge.h src/Line.cpp src/Line.h)
