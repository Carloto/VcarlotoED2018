// Include
#include "rectangle.h"

struct tmpRectangle { // Retangulo
    int *numberId; // Id da figura
    double *xCoord; // X do canto superior esquerdo
    double *yCoord; // Y do canto superior esquerdo
    double *width; // Largura do ratangulo
    double *height; // Altura do retangulo
    char *fillColor; // Cor interior
    char *strokeColor; // Cor da borda
};

// Aloca e inicializa uma struct Rectangle
Rectangle *allocRectangle() {
    Rectangle *tmpRect = (Rectangle *) calloc(1, sizeof(Rectangle));
    tmpRect->numberId = (int *) calloc(1, sizeof(int));
    tmpRect->xCoord = (double *) calloc(1, sizeof(double));
    tmpRect->yCoord = (double *) calloc(1, sizeof(double));
    tmpRect->width = (double *) calloc(1, sizeof(double));
    tmpRect->height = (double *) calloc(1, sizeof(double));
    tmpRect->fillColor = NULL;
    tmpRect->strokeColor = NULL;
    return tmpRect;
}

// Libera a memoria de um unico retangulo
void killRectangle(Rectangle *tmpRect) {
    if (tmpRect != NULL) {
        freeInt(&(tmpRect->numberId));
        freeDouble(&(tmpRect->xCoord));
        freeDouble(&(tmpRect->yCoord));
        freeDouble(&(tmpRect->width));
        freeDouble(&(tmpRect->height));
        freeString(&(tmpRect->fillColor));
        freeString(&(tmpRect->strokeColor));
    }
}

// Set number id
void setRectangleId(Rectangle *tmpRect, int tmpNumberId) {
    *(tmpRect->numberId) = tmpNumberId;
}

// Set X
void setRectangleX(Rectangle *tmpRect, double tmpX) {
    *(tmpRect->xCoord) = tmpX;
}

// Set Y
void setRectangleY(Rectangle *tmpRect, double tmpY) {
    *(tmpRect->yCoord) = tmpY;
}

// Set width
void setRectangleWidth(Rectangle *tmpRect, double tmpWidth) {
    *(tmpRect->width) = tmpWidth;
}

// Set height
void setRectangleHeight(Rectangle *tmpRect, double tmpHeight) {
    *(tmpRect->height) = tmpHeight;
}

// Set fillColor
void setRectangleFillColor(Rectangle *tmpRect, char *tmpFillColor) {
    copyString(&(tmpRect->fillColor), tmpFillColor);
}

// Set strokeColor
void setRectangleStrokeColor(Rectangle *tmpRect, char *tmpStrokeColor) {
    copyString(&(tmpRect->strokeColor), tmpStrokeColor);
}

// Get number id
int *getRectangleId(Rectangle *tmpRect) {
    return tmpRect->numberId;
}

// Get X
double *getRectangleX(Rectangle *tmpRect) {
    return tmpRect->xCoord;
}

// Get Y
double *getRectangleY(Rectangle *tmpRect) {
    return tmpRect->yCoord;
}

// Get width
double *getRectangleWidth(Rectangle *tmpRect) {
    return tmpRect->width;
}

// Get height
double *getRectangleHeight(Rectangle *tmpRect) {
    return tmpRect->height;
}

// Get fillColor
char *getRectangleFillColor(Rectangle *tmpRect) {
    return tmpRect->fillColor;
}

// Get strokeColor
char *getRectangleStrokeColor(Rectangle *tmpRect) {
    return tmpRect->strokeColor;
}

// Imprime as informações do Retangulo
void printRectangle(Rectangle *tmpRect) {
    printf("\nid = |%d|", *(tmpRect->numberId));
    printf("  x = |%.3lf|", *(tmpRect->xCoord));
    printf("  y = |%.3lf|", *(tmpRect->yCoord));
    printf("  width = |%.3lf|", *(tmpRect->width));
    printf("  height = |%.3lf|", *(tmpRect->height));
    printf("  fill color = |%s|\n", tmpRect->fillColor);
    printf("  stroke color = |%s|", tmpRect->strokeColor);
}
