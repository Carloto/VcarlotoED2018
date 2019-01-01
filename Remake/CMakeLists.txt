cmake_minimum_required(VERSION 3.12)
project(remake)

add_executable(siguel src/main.c src/filehandling.c src/miscfunctions.c src/miscfunctions.h src/basicshapes.c src/basicshapes.h src/genericlist.c src/genericlist.h src/circle.c src/circle.h src/rectangle.c src/rectangle.h src/quadra.c src/quadra.h)
target_compile_options(siguel PUBLIC -fstack-protector-all -std=c99 -pedantic -g -Wall)
target_link_libraries(siguel m)