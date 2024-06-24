cmake_minimum_required(VERSION 3.28)
project(ls2)

set(CMAKE_CXX_STANDARD 17)

add_executable(ls2 src/main.cpp
        src/ls2.cpp
        src/includes/ls2.h
        src/utils.cpp
        src/includes/utils.h
        src/fileinfo.cpp
        src/includes/fileinfo.h)
