// Include
#include "semaforo.h"

struct tmpSemaforo { // Semaforo
    char id[50]; // Id da Semaforo
    double xCoord; // X do canto superior esquerdo
    double yCoord; // Y do canto superior esquerdo
    double width; // Largura da Semaforo (15)
    double height; // Altura da Semaforo (35)
    char fillColor[50]; // Cor interior
    char strokeColor[50]; // Cor da borda
};

// Aloca e inicializa uma struct Semaforo
Semaforo *allocSemaforo() {
    Semaforo *tmpSemaf = (Semaforo *) calloc(1, sizeof(Semaforo));
    return tmpSemaf;
}

// Libera a memoria de uma unica Semaforo
void killSemaforo(Semaforo *tmpSemaf) {
    if (tmpSemaf != NULL) {
        free(tmpSemaf);
    }
}

// Deleta o semaforo
void deleteSemaforo(Semaforo *tmpSemaf) {
    sprintf(tmpSemaf->id, "%s", "deletado");
}

// Retorna o tamanho de uma Semaforo
size_t getSemaforoSize(){
    return sizeof(Semaforo);
}

// Set id
void setSemaforoId(Semaforo *tmpSemaf, char tmpId[50]) {
    sprintf(tmpSemaf->id, "%s", tmpId);
}

// Set X
void setSemaforoX(Semaforo *tmpSemaf, double tmpX) {
    tmpSemaf->xCoord = tmpX;
}

// Set Y
void setSemaforoY(Semaforo *tmpSemaf, double tmpY) {
    tmpSemaf->yCoord = tmpY;
}

// Set width
void setSemaforoWidth(Semaforo *tmpSemaf, double tmpWidth) {
    tmpSemaf->width = tmpWidth;
}

// Set height
void setSemaforoHeight(Semaforo *tmpSemaf, double tmpHeight) {
    tmpSemaf->height = tmpHeight;
}

// Set fillColor
void setSemaforoFillColor(Semaforo *tmpSemaf, char *tmpFillColor) {
    sprintf(tmpSemaf->fillColor, "%s", tmpFillColor);
}

// Set strokeColor
void setSemaforoStrokeColor(Semaforo *tmpSemaf, char *tmpStrokeColor) {
    sprintf(tmpSemaf->strokeColor, "%s", tmpStrokeColor);
}

// Get id
char *getSemaforoId(Semaforo *tmpSemaf) {
    return tmpSemaf->id;
}

// Get X
double getSemaforoX(Semaforo *tmpSemaf) {
    return tmpSemaf->xCoord;
}

// Get Y
double getSemaforoY(Semaforo *tmpSemaf) {
    return tmpSemaf->yCoord;
}

// Get width
double getSemaforoWidth(Semaforo *tmpSemaf) {
    return tmpSemaf->width;
}

// Get height
double getSemaforoHeight(Semaforo *tmpSemaf) {
    return tmpSemaf->height;
}

// Get fillColor
char *getSemaforoFillColor(Semaforo *tmpSemaf) {
    return tmpSemaf->fillColor;
}

// Get strokeColor
char *getSemaforoStrokeColor(Semaforo *tmpSemaf) {
    return tmpSemaf->strokeColor;
}

// Imprime as informações do Retangulo
void printSemaforo(Semaforo *tmpSemaf) {
    printf("\nid = |%s|", tmpSemaf->id);
    printf("  x = |%.3lf|", tmpSemaf->xCoord);
    printf("  y = |%.3lf|", tmpSemaf->yCoord);
    printf("  width = |%.3lf|", tmpSemaf->width);
    printf("  height = |%.3lf|", tmpSemaf->height);
    printf("  fill color = |%s|\n", tmpSemaf->fillColor);
    printf("  stroke color = |%s|", tmpSemaf->strokeColor);
}
