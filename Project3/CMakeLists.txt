cmake_minimum_required(VERSION 3.17)
project(Project3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Project3
        City.h
        DataGenerator.cpp
        DataGenerator.h
        FordFulkerson.cpp
        FordFulkerson.h
        Graph.cpp
        Graph.h
        main.cpp
        NetworkFlow.cpp
        Randomizer.cpp
        Randomizer.h
        Reader.cpp
        Reader.h)
