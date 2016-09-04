cmake_minimum_required(VERSION 3.3)
project(Ex1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pthread -Wvla -std=c++11")

set(SOURCE_FILES Point.cpp PointSet.cpp PointSetBinaryOperations.cpp)
add_executable(Ex1 ${SOURCE_FILES})

project(Ex2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pthread -Wvla -std=c++11")

set(SOURCE_FILES Point.cpp Point.cpp Point.h PointSet.cpp PointSet.h
        ConvexHull.cpp)
add_executable(Ex2 ${SOURCE_FILES})