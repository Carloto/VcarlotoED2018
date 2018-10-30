// Define
#ifndef TRAB3_STRUCTLIB_H
#define TRAB3_STRUCTLIB_H

// Include
#include <stdio.h>

// Neste header estarão definidas as structs necessarias para o programa

// Lista ligada generica
typedef struct tmp_genericList {
    void *data;
    int type; // 0 = irrelevante, 1 = circulo, 2 = retangulo
    struct tmp_genericList *next;
} genericList;

// Figuras basicas

#endif //TRAB3_STRUCTLIB_H
