// Include
#include "quadra.h"

struct tmpQuadra { // Quadra
    char cep[50]; // Id da quadra
    double xCoord; // X do canto superior esquerdo
    double yCoord; // Y do canto superior esquerdo
    double width; // Largura da quadra
    double height; // Altura da quadra
    char fillColor[50]; // Cor interior
    char strokeColor[50]; // Cor da borda
};

// Aloca e inicializa uma struct Quadra
Quadra *allocQuadra() {
    Quadra *tmpQuad = (Quadra *) calloc(1, sizeof(Quadra));
    return tmpQuad;
}

// Libera a memoria de uma unica quadra
void killQuadra(Quadra *tmpQuad) {
    if (tmpQuad != NULL) {
        free(tmpQuad);
    }
}

// Deleta a quadra
void deleteQuadra(Quadra *tmpQuad) {
    sprintf(tmpQuad->cep, "%s", "deletado");
}

// Retorna o tamanho de uma quadra
size_t getQuadraSize(){
    return sizeof(Quadra);
}

// Set cep
void setQuadraCep(Quadra *tmpQuad, char tmpCep[50]) {
    sprintf(tmpQuad->cep, "%s", tmpCep);
}

// Set X
void setQuadraX(Quadra *tmpQuad, double tmpX) {
    tmpQuad->xCoord = tmpX;
}

// Set Y
void setQuadraY(Quadra *tmpQuad, double tmpY) {
    tmpQuad->yCoord = tmpY;
}

// Set width
void setQuadraWidth(Quadra *tmpQuad, double tmpWidth) {
    tmpQuad->width = tmpWidth;
}

// Set height
void setQuadraHeight(Quadra *tmpQuad, double tmpHeight) {
    tmpQuad->height = tmpHeight;
}

// Set fillColor
void setQuadraFillColor(Quadra *tmpQuad, char *tmpFillColor) {
    sprintf(tmpQuad->fillColor, "%s", tmpFillColor);
}

// Set strokeColor
void setQuadraStrokeColor(Quadra *tmpQuad, char *tmpStrokeColor) {
    sprintf(tmpQuad->strokeColor, "%s", tmpStrokeColor);
}

// Get cep
char *getQuadraCep(Quadra *tmpQuad) {
    return tmpQuad->cep;
}

// Get X
double getQuadraX(Quadra *tmpQuad) {
    return tmpQuad->xCoord;
}

// Get Y
double getQuadraY(Quadra *tmpQuad) {
    return tmpQuad->yCoord;
}

// Get width
double getQuadraWidth(Quadra *tmpQuad) {
    return tmpQuad->width;
}

// Get height
double getQuadraHeight(Quadra *tmpQuad) {
    return tmpQuad->height;
}

// Get fillColor
char *getQuadraFillColor(Quadra *tmpQuad) {
    return tmpQuad->fillColor;
}

// Get strokeColor
char *getQuadraStrokeColor(Quadra *tmpQuad) {
    return tmpQuad->strokeColor;
}

// Imprime as informações do Retangulo
void printQuadra(Quadra *tmpQuad) {
    printf("\ncep = |%s|", tmpQuad->cep);
    printf("  x = |%.3lf|", tmpQuad->xCoord);
    printf("  y = |%.3lf|", tmpQuad->yCoord);
    printf("  width = |%.3lf|", tmpQuad->width);
    printf("  height = |%.3lf|", tmpQuad->height);
    printf("  fill color = |%s|\n", tmpQuad->fillColor);
    printf("  stroke color = |%s|", tmpQuad->strokeColor);
}
