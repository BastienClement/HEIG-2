cmake_minimum_required(VERSION 3.5)
project(ClasseString)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    cstring.cpp
    cstring.h
    main.cpp)

add_executable(ClasseString ${SOURCE_FILES})