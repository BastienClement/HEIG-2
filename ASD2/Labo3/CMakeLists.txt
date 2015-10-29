cmake_minimum_required(VERSION 3.3)
project(Labo3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp RoadNetwork.cpp UnionFind.cpp Util.cpp)
add_executable(Labo3 ${SOURCE_FILES})
