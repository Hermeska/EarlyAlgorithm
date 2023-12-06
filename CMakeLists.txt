cmake_minimum_required(VERSION 3.22)
project(MiptEarly)

set(CMAKE_CXX_STANDARD 17)

add_executable(MiptEarly EarlyParser.h
        test.cpp main.cpp)
