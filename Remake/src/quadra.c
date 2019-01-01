// Include
#include "quadra.h"

struct tmpQuadra { // Quadra
    char cep[50]; // Id da quadra
    double xCoord; // X do canto superior esquerdo
};

// Adiciona uma nova quadra
void newQuadra(char *inputLine, FILE **binFile) {
    Quadra *novaQuadra = (Quadra *) calloc(1, sizeof(Quadra));
    char *token = strtok(inputLine, " "); // Comando
    if (token == NULL) {
        return;
    }
    token = strtok(NULL, " ");
    strcpy(novaQuadra->cep, token);
    token = strtok(NULL, " ");
    (novaQuadra->xCoord) = newAtod(token);
    printf("\ncep = %s x = %lf\n", novaQuadra->cep, (novaQuadra->xCoord));
    fwrite(novaQuadra, sizeof(Quadra), 1, *binFile);
    free(novaQuadra);
}

// Print quadras
void printBinQuadra(FILE **binFile) {
    Quadra *novaQuadra = (Quadra *) calloc(1, sizeof(Quadra));
    fseek(*binFile, 0, SEEK_SET);
    printf("\n Quadras Lidas : \n");
    while (fread(novaQuadra, sizeof(Quadra), 1, *binFile) > 0) {
        printf("\n//////////////////////////////////////////////////////////////////\n "
               "Cep = %s  X = %lf", novaQuadra->cep, (novaQuadra->xCoord));
    }
    free(novaQuadra);
}
