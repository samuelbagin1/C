cmake_minimum_required(VERSION 3.27)
project(C C)

set(CMAKE_C_STANDARD 11)

include_directories(z2_clion_project/include)

add_executable(C
        architekturapc/blok2.c
        "architekturapc/uloha 1.c"
        z2_clion_project/include/data.h
        z2_clion_project/include/functions.h
        z2_clion_project/src/data.c
        z2_clion_project/src/functions.c
        z2_clion_project/src/z2.c
        hokus.c
        intro.c
        "zadanie 1.c"
        z3.c)
