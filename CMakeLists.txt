cmake_minimum_required(VERSION 3.26)
project(projeto_aed1_lp1 C)

set(CMAKE_C_STANDARD 11)

add_executable(projeto_aed1_lp1 main.c
        functions/functions_1.c
        functions/functions_1.h
        test_functions/test_functions_1.c
        test_functions/test_functions_1.h
        functions/functions_2.c
        functions/functions_2.h
)
