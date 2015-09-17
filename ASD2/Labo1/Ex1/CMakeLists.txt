cmake_minimum_required(VERSION 3.3)
project(Ex1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    bitmap_image.hpp
    ex1.cpp
    GraphFromImage.cpp
    GraphFromImage.h
    ParcoursEnProfondeur.h)

add_executable(Ex1 ${SOURCE_FILES})