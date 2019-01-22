// Include
#include "torre.h"

struct tmpTorre { // Torre
    char id[50]; // Id da Torre
    double xCoord; // X do canto superior esquerdo
    double yCoord; // Y do canto superior esquerdo
    double radius; // Raio da Torre (8)
    char fillColor[50]; // Cor interior
    char strokeColor[50]; // Cor da borda
};

// Aloca e inicializa uma struct Torre
Torre *allocTorre() {
    Torre *tmpTor = (Torre *) calloc(1, sizeof(Torre));
    return tmpTor;
}

// Libera a memoria de uma unica Torre
void killTorre(Torre *tmpTor) {
    if (tmpTor != NULL) {
        free(tmpTor);
    }
}

// Deleta a torre
void deleteTorre(Torre *tmpTorre) {
    sprintf(tmpTorre->id, "%s", "deletado");
}

// Retorna o tamanho de uma Torre
size_t getTorreSize() {
    return sizeof(Torre);
}

// Set id
void setTorreId(Torre *tmpTor, char tmpId[50]) {
    sprintf(tmpTor->id, "%s", tmpId);
}

// Set X
void setTorreX(Torre *tmpTor, double tmpX) {
    tmpTor->xCoord = tmpX;
}

// Set Y
void setTorreY(Torre *tmpTor, double tmpY) {
    tmpTor->yCoord = tmpY;
}

// Set Radius
void setTorreRadius(Torre *tmpTor, double tmpRadius) {
    tmpTor->radius = tmpRadius;
}

// Set fillColor
void setTorreFillColor(Torre *tmpTor, char *tmpFillColor) {
    sprintf(tmpTor->fillColor, "%s", tmpFillColor);
}

// Set strokeColor
void setTorreStrokeColor(Torre *tmpTor, char *tmpStrokeColor) {
    sprintf(tmpTor->strokeColor, "%s", tmpStrokeColor);
}

// Get Id
char *getTorreId(Torre *tmpTor) {
    return tmpTor->id;
}

// Get X
double getTorreX(Torre *tmpTor) {
    return tmpTor->xCoord;
}

// Get Y
double getTorreY(Torre *tmpTor) {
    return tmpTor->yCoord;
}

// Get Radius
double getTorreRadius(Torre *tmpTor) {
    return tmpTor->radius;
}

// Get fillColor
char *getTorreFillColor(Torre *tmpTor) {
    return tmpTor->fillColor;
}

// Get strokeColor
char *getTorreStrokeColor(Torre *tmpTor) {
    return tmpTor->strokeColor;
}

// Imprime as informações do Retangulo
void printTorre(Torre *tmpTor) {
    printf("\nid = |%s|", tmpTor->id);
    printf("  x = |%.3lf|", tmpTor->xCoord);
    printf("  y = |%.3lf|", tmpTor->yCoord);
    printf("  radius = |%.3lf|", tmpTor->radius);
    printf("  fill color = |%s|\n", tmpTor->fillColor);
    printf("  stroke color = |%s|", tmpTor->strokeColor);
}
