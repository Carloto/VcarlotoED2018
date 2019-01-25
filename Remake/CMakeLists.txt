cmake_minimum_required(VERSION 3.12)
project(remake)

add_executable(siguel src/main.c src/filehandling.c src/miscfunctions.c src/miscfunctions.h src/basicshapes.c src/basicshapes.h src/genericlist.c src/genericlist.h src/circle.c src/circle.h src/rectangle.c src/rectangle.h src/quadra.c src/quadra.h src/cidade.c src/cidade.h src/btree.c src/btree.h src/color.c src/color.h src/hidrante.c src/hidrante.h src/torre.c src/torre.h src/semaforo.c src/semaforo.h src/query.c src/query.h src/closestpair.c src/closestpair.h src/estabelecimento.c src/estabelecimento.h src/tipoestab.c src/tipoestab.h src/pessoa.c src/pessoa.h src/moradia.c src/moradia.h src/auxfig.c src/auxfig.h src/grafo.c src/grafo.h src/linkedist.c src/linkedist.h src/ponto.c src/ponto.h src/carro.c src/carro.h)
target_compile_options(siguel PUBLIC -fstack-protector-all -std=c99 -pedantic -g -Wall)
target_link_libraries(siguel m)


find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

target_link_libraries(siguel ${GTK3_LIBRARIES})