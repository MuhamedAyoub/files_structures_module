cmake_minimum_required(VERSION 3.23)
project(file_structures)

set(CMAKE_CXX_STANDARD 14)

include_directories(sequential_structures/TOF/C/main)

add_executable(file_structures
        sequential_structures/TDs/TD3/exo1.c
        sequential_structures/TOF/C/main/model.h
        sequential_structures/TOF/C/main/tof_functions.c
        sequential_structures/dichotomic_search.C)
