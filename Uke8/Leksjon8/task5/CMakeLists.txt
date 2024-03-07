cmake_minimum_required(VERSION 3.27)
project(oppgave2 C)

set(CMAKE_C_STANDARD 11)

add_executable(oppgave2
        src/main.c
        src/snBubblesort.c
        src/printing.c
        include/printing.h
        include/snBubblesort.h
        src/main.c)
