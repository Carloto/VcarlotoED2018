
#include "carro.h"

struct tmpCarro { // Carro
    char placa[25]; // Id da Carro
    double xCoord; // X do canto superior esquerdo
    double yCoord; // Y do canto superior esquerdo
    double width; // Largura da Carro
    double height; // Altura da Carro
};

// Aloca e inicializa uma struct Carro
Carro *allocCarro() {
    Carro *tmpQuad = (Carro *) calloc(1, sizeof(Carro));
    return tmpQuad;
}

// Libera a memoria de uma unica Carro
void killCarro(Carro *tmpQuad) {
    if (tmpQuad != NULL) {
        free(tmpQuad);
    }
}

// Deleta a Carro
void deleteCarro(Carro *tmpQuad) {
    sprintf(tmpQuad->placa, "%s", "deletado");
}

// Retorna o tamanho de uma Carro
size_t getCarroSize(){
    return sizeof(Carro);
}

// Set cep
void setCarroPlaca(Carro *tmpQuad, char tmpCep[25]) {
    sprintf(tmpQuad->placa, "%s", tmpCep);
}

// Set X
void setCarroX(Carro *tmpQuad, double tmpX) {
    tmpQuad->xCoord = tmpX;
}

// Set Y
void setCarroY(Carro *tmpQuad, double tmpY) {
    tmpQuad->yCoord = tmpY;
}

// Set width
void setCarroWidth(Carro *tmpQuad, double tmpWidth) {
    tmpQuad->width = tmpWidth;
}

// Set height
void setCarroHeight(Carro *tmpQuad, double tmpHeight) {
    tmpQuad->height = tmpHeight;
}

// Get cep
char *getCarroplaca(Carro *tmpQuad) {
    return tmpQuad->placa;
}

// Get X
double getCarroX(Carro *tmpQuad) {
    return tmpQuad->xCoord;
}

// Get Y
double getCarroY(Carro *tmpQuad) {
    return tmpQuad->yCoord;
}

// Get width
double getCarroWidth(Carro *tmpQuad) {
    return tmpQuad->width;
}

// Get height
double getCarroHeight(Carro *tmpQuad) {
    return tmpQuad->height;
}

/*// Imprime as informações do Retangulo
void printCarro(Carro *tmpQuad) {
    printf("\ncep = |%s|", tmpQuad->cep);
    printf("  x = |%.3lf|", tmpQuad->xCoord);
    printf("  y = |%.3lf|", tmpQuad->yCoord);
    printf("  width = |%.3lf|", tmpQuad->width);
    printf("  height = |%.3lf|", tmpQuad->height);
    printf("  fill color = |%s|\n", tmpQuad->fillColor);
    printf("  stroke color = |%s|", tmpQuad->strokeColor);
}
*/
