// Define
#ifndef TRAB3_STRUCTLIB_H
#define TRAB3_STRUCTLIB_H

// Include
#include <stdio.h>

// Neste header estarão definidas as structs necessarias para o programa

// Struct para guardar a entrada de argumentos
typedef struct tmp_fileArguments {
    char *input_e;
    char *input_f;
    char *output_o;
    char *geoInputName;
    char *geoName;
    FILE *GeoInputFile;
} fileArguments;

// Lista ligada generica
typedef struct tmp_genericList {
    void *data;
    struct tmp_genericList *next;
} genericList;

// Figuras basicas

typedef struct tmpCircle { // Circulo

    int numberId; // Id da figura
    float xCenter; // X do centro
    float yCenter; // Y do centro
    char *fillColor; // Cor interior
    char *strokeColor; // Cor da borda

} Circle;

typedef struct tmpRectangle { // Retangulo

    int numberId; // Id da figura
    float xCoord; // X do canto superior esquerdo
    float yCoord; // Y do canto superior esquerdo
    float width; // Largura do ratangulo
    float height; // Altura do retangulo
    char *fillColor; // Cor interior
    char *strokeColor; // Cor da borda

} Rectangle;

#endif //TRAB3_STRUCTLIB_H
