cmake_minimum_required(VERSION 3.20)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled main.cpp src/Stop.cpp src/Stop.h src/Interface/Menu.cpp src/Interface/Menu.h src/Interface/System.cpp src/Interface/System.h src/Controller.cpp src/Controller.h src/Interface/OptionsMenu.cpp src/Interface/OptionsMenu.h src/Line.cpp src/Line.h src/Interface/DirectionsMenu.cpp src/Interface/DirectionsMenu.h src/Graph.cpp src/Graph.h src/minHeap.h src/Edge.cpp src/Edge.h)
