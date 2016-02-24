cmake_minimum_required(VERSION 3.3)
project(AVLTree)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        src/model/Noh.h
        src/model/Noh.cpp
        src/model/Tree.h
        src/model/Tree.cpp
        src/run/Runner.h
        src/run/Runner.cpp
        src/main.cpp
        src/model/Constants.h
        src/model/Constants.cpp)

add_executable(AVLTree ${SOURCE_FILES})