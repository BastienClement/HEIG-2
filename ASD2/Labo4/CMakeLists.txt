cmake_minimum_required(VERSION 3.3)
project(Labo4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp DirectoryCity.cpp DirectoryInt.cpp DirectoryLong.cpp DirectorySha256.cpp DirectoryStl.cpp
        DirectoryWithoutAVS.cpp Util.cpp libs/city.cc libs/sha256.cpp)
add_executable(Labo4 ${SOURCE_FILES})
