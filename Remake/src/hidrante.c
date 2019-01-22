// Include
#include "hidrante.h"

struct tmpHidrante { // Hidrante
    char id[50]; // Id do hidrante
    double xCoord; // X do centro
    double yCoord; // Y do centro
    double radius; // Raio do hidrante (8)
    char fillColor[50]; // Cor interior
    char strokeColor[50]; // Cor da borda
};

// Aloca e inicializa uma struct Hidrante
Hidrante *allocHidrante() {
    Hidrante *tmpHid = (Hidrante *) calloc(1, sizeof(Hidrante));
    return tmpHid;
}

// Libera a memoria de uma unica Hidrante
void killHidrante(Hidrante *tmpHid) {
    if (tmpHid != NULL) {
        free(tmpHid);
    }
}

// Deleta o hidrante
void deleteHidrante(Hidrante *tmpHid) {
    sprintf(tmpHid->id, "%s", "deletado");
}

// Retorna o tamanho de uma Hidrante
size_t getHidranteSize() {
    return sizeof(Hidrante);
}

// Set id
void setHidranteId(Hidrante *tmpHid, char tmpId[50]) {
    sprintf(tmpHid->id, "%s", tmpId);
}

// Set X
void setHidranteX(Hidrante *tmpHid, double tmpX) {
    tmpHid->xCoord = tmpX;
}

// Set Y
void setHidranteY(Hidrante *tmpHid, double tmpY) {
    tmpHid->yCoord = tmpY;
}

// Set radius
void setHidranteRadius(Hidrante *tmpHid, double tmpRadius) {
    tmpHid->radius = tmpRadius;
}

// Set fillColor
void setHidranteFillColor(Hidrante *tmpHid, char *tmpFillColor) {
    sprintf(tmpHid->fillColor, "%s", tmpFillColor);
}

// Set strokeColor
void setHidranteStrokeColor(Hidrante *tmpHid, char *tmpStrokeColor) {
    sprintf(tmpHid->strokeColor, "%s", tmpStrokeColor);
}

// Get Id
char *getHidranteId(Hidrante *tmpHid) {
    return tmpHid->id;
}

// Get X
double getHidranteX(Hidrante *tmpHid) {
    return tmpHid->xCoord;
}

// Get Y
double getHidranteY(Hidrante *tmpHid) {
    return tmpHid->yCoord;
}

// Get radius
double getHidranteRadius(Hidrante *tmpHid) {
    return tmpHid->radius;
}

// Get fillColor
char *getHidranteFillColor(Hidrante *tmpHid) {
    return tmpHid->fillColor;
}

// Get strokeColor
char *getHidranteStrokeColor(Hidrante *tmpHid) {
    return tmpHid->strokeColor;
}

// Imprime as informações do Hidrante
void printHidrante(Hidrante *tmpHid) {
    printf("\nid = |%s|", tmpHid->id);
    printf("  x = |%.3lf|", tmpHid->xCoord);
    printf("  y = |%.3lf|", tmpHid->yCoord);
    printf("  radius = |%.3lf|", tmpHid->radius);
    printf("  fill color = |%s|\n", tmpHid->fillColor);
    printf("  stroke color = |%s|", tmpHid->strokeColor);
}
