// Include
#include "rectangle.h"

struct tmpRectangle { // Retangulo
    int *type; // 0 = figura normal, 1 = pontilhado
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
    tmpRect->type = (int *) calloc(1, sizeof(int));
    tmpRect->numberId = (int *) calloc(1, sizeof(int));
    tmpRect->xCoord = (double *) calloc(1, sizeof(double));
    tmpRect->yCoord = (double *) calloc(1, sizeof(double));
    tmpRect->width = (double *) calloc(1, sizeof(double));
    tmpRect->height = (double *) calloc(1, sizeof(double));
    tmpRect->fillColor = NULL;
    tmpRect->strokeColor = NULL;
    setRectangleType(tmpRect, 0);
    return tmpRect;
}

// Libera a memoria de um unico retangulo
void killRectangle(Rectangle *tmpRect) {
    if (tmpRect != NULL) {
        freeInt(&(tmpRect->type));
        freeInt(&(tmpRect->numberId));
        freeDouble(&(tmpRect->xCoord));
        freeDouble(&(tmpRect->yCoord));
        freeDouble(&(tmpRect->width));
        freeDouble(&(tmpRect->height));
        freeString(&(tmpRect->fillColor));
        freeString(&(tmpRect->strokeColor));
    }
}

// Set type
void setRectangleType(Rectangle *tmpRect, int tmpType) {
    *(tmpRect->type) = tmpType;
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

// Imprime as informações do circulo
void printRectangle(Rectangle *tmpRect) {
    printf("\ntype = |%d|", *(tmpRect->type));
    printf(" id = |%d|", *(tmpRect->numberId));
    printf("  x = |%.3lf|", *(tmpRect->xCoord));
    printf("  y = |%.3lf|", *(tmpRect->yCoord));
    printf("  width = |%.3lf|", *(tmpRect->width));
    printf("  height = |%.3lf|", *(tmpRect->height));
    printf("  fill color = |%s|\n", tmpRect->fillColor);
    printf("  stroke color = |%s|", tmpRect->strokeColor);
}
