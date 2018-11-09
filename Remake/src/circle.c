// Include
#include "circle.h"

struct tmpCircle { // Circulo
    int *type; // 0 = figura normal, 1 = pontilhado
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
    tmpCircle->type = (int *) calloc(1, sizeof(int));
    tmpCircle->numberId = (int *) calloc(1, sizeof(int));
    tmpCircle->radius = (double *) calloc(1, sizeof(double));
    tmpCircle->xCenter = (double *) calloc(1, sizeof(double));
    tmpCircle->yCenter = (double *) calloc(1, sizeof(double));
    tmpCircle->fillColor = NULL;
    tmpCircle->strokeColor = NULL;
    setCircleType(tmpCircle, 0);
    return tmpCircle;
}

// Libera a memoria de um unico circulo
void killCircle(Circle *tmpCircle) {
    if (tmpCircle != NULL) {
        freeInt(&(tmpCircle->type));
        freeInt(&(tmpCircle->numberId));
        freeDouble(&(tmpCircle->radius));
        freeDouble(&(tmpCircle->xCenter));
        freeDouble(&(tmpCircle->yCenter));
        freeString(&(tmpCircle->fillColor));
        freeString(&(tmpCircle->strokeColor));
    }
}

// Set type
void setCircleType(Circle *tmpCircle, int tmpType) {
    *(tmpCircle->type) = tmpType;
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

// Imprime as informações do circulo
void printCircle(Circle *tmpCircle) {
    printf("\ntype = |%d|", *(tmpCircle->type));
    printf(" id = |%d|", *(tmpCircle->numberId));
    printf("  raio = |%.3lf|", *(tmpCircle->radius));
    printf("  x = |%.3lf|", *(tmpCircle->xCenter));
    printf("  y = |%.3lf|", *(tmpCircle->yCenter));
    printf("  fill color = |%s|\n", tmpCircle->fillColor);
    printf("  stroke color = |%s|", tmpCircle->strokeColor);
}
