cmake_minimum_required(VERSION 3.27)
project(task C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(task
        src/main.c
        src/menuApplication.c
        src/linkedList.c
        include/main.h
        include/menuApplication.h
        include/linkedList.h)
