// Include
#include "circle.h"

struct tmpCircle { // Circulo
    int *numberId; // Id da figura
    double *radius; // Raio do circulo
    double *xCenter; // X do centro
    double *yCenter; // Y do centro
    char *fillColor; // Cor interior
    char *strokeColor; // Cor da borda
};

// Aloca e inicializa uma struct Circle
Circle *allocCircle() {
    Circle *tmpCircle = (Circle *) calloc(1, sizeof(Circle));
    tmpCircle->numberId = (int *) calloc(1, sizeof(int));
    tmpCircle->radius = (double *) calloc(1, sizeof(double));
    tmpCircle->xCenter = (double *) calloc(1, sizeof(double));
    tmpCircle->yCenter = (double *) calloc(1, sizeof(double));
    tmpCircle->fillColor = NULL;
    tmpCircle->strokeColor = NULL;
    return tmpCircle;
}

// Libera a memoria de um unico circulo
void killCircle(Circle *tmpCircle) {
    if (tmpCircle != NULL) {
        freeInt(&(tmpCircle->numberId));
        freeDouble(&(tmpCircle->radius));
        freeDouble(&(tmpCircle->xCenter));
        freeDouble(&(tmpCircle->yCenter));
        freeString(&(tmpCircle->fillColor));
        freeString(&(tmpCircle->strokeColor));
    }
}

// Set number id
void setCircleId(Circle *tmpCircle, int tmpNumberId) {
    *(tmpCircle->numberId) = tmpNumberId;
}

// Set radius
void setCircleRadius(Circle *tmpCircle, double tmpRadius) {
    *(tmpCircle->radius) = tmpRadius;
}

// Set xCenter
void setCircleX(Circle *tmpCircle, double tmpXCenter) {
    *(tmpCircle->xCenter) = tmpXCenter;
}

// Set yCenter
void setCircleY(Circle *tmpCircle, double tmpYCenter) {
    *(tmpCircle->yCenter) = tmpYCenter;
}

// Set fillColor
void setCircleFillColor(Circle *tmpCircle, char *tmpFillColor) {
    copyString(&(tmpCircle->fillColor), tmpFillColor);
}

// Set strokeColor
void setCircleStrokeColor(Circle *tmpCircle, char *tmpStrokeColor) {
    copyString(&(tmpCircle->strokeColor), tmpStrokeColor);
}

// Get number id
int *getCircleId(Circle *tmpCircle) {
    return tmpCircle->numberId;
}

// Get radius
double *getCircleRadius(Circle *tmpCircle) {
    return tmpCircle->radius;
}

// Get xCenter
double *getCircleX(Circle *tmpCircle) {
    return tmpCircle->xCenter;
}

// Get yCenter
double *getCircleY(Circle *tmpCircle) {
    return tmpCircle->yCenter;
}

// Get fillColor
char *getCircleFillColor(Circle *tmpCircle) {
    return tmpCircle->fillColor;
}

// Get strokeColor
char *getCircleStrokeColor(Circle *tmpCircle) {
    return tmpCircle->strokeColor;
}

// Imprime as informações do circulo
void printCircle(Circle *tmpCircle) {
    printf("\nid = |%d|", *(tmpCircle->numberId));
    printf("  x = |%.3lf|", *(tmpCircle->xCenter));
    printf("  y = |%.3lf|", *(tmpCircle->yCenter));
    printf("  raio = |%.3lf|", *(tmpCircle->radius));
    printf("  fill color = |%s|\n", tmpCircle->fillColor);
    printf("  stroke color = |%s|", tmpCircle->strokeColor);
}
