cmake_minimum_required(VERSION 3.12)
project(trab3)

add_executable(siguel src/main.c src/filehandling.c src/miscfunctions.c src/miscfunctions.h src/basicshapes.c src/basicshapes.h src/genericlist.c src/genericlist.h)
target_compile_options(siguel PUBLIC -fstack-protector-all -std=c99 -pedantic -g -Wall)
target_link_libraries(siguel m)