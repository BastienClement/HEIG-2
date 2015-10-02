cmake_minimum_required(VERSION 3.3)
project(Labo2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    DiGraph.cpp
    DiGraph.h
    DirectedCycle.h
    main.cpp
    ParcoursEnProfondeur.h
    SymbolGraph.h
    TopologicalSort.h
    Util.cpp
    Util.h)

add_executable(Labo2 ${SOURCE_FILES})