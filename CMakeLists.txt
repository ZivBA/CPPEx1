cmake_minimum_required(VERSION 3.3)
project(Ex1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Point.cpp Point.cpp Point.h PointSet.cpp PointSet.h
        TestPointSetFuncs.cpp)
add_executable(Ex1 ${SOURCE_FILES})