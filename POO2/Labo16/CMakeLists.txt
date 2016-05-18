cmake_minimum_required(VERSION 3.5)
project(Labo16)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Container.cpp Boat.cpp Bank.cpp Controller.cpp ActionException.cpp person/Child.cpp person/Child.h person/Cop.cpp person/Cop.h person/Parent.cpp person/Parent.h person/Thief.cpp person/Thief.h person/Person.cpp person/Person.h person/FamilyMember.cpp person/FamilyMember.h person/PersonVisitor.cpp person/PersonVisitor.h)
add_executable(Labo16 ${SOURCE_FILES})
