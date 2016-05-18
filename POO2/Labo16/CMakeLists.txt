cmake_minimum_required(VERSION 3.5)
project(Labo16)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        main.cpp
        Container.cpp
        Boat.cpp
        Bank.cpp
        Controller.cpp
        ActionException.cpp
        person/Child.cpp
        person/Cop.cpp
        person/Parent.cpp
        person/Thief.cpp
        person/Person.cpp
        person/FamilyMember.cpp
        person/PersonVisitor.cpp)

add_executable(Labo16 ${SOURCE_FILES})
