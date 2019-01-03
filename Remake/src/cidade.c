// Include
#include "cidade.h"

struct tmpCidade { // Estruturas da cidade
    FILE *quadras; // Arquivo binario de quadras
};

// Aloca e inicializa uma struct Cidade
Cidade *allocCidade(fileArguments *source) {
    Cidade *tmpStruct = (Cidade *) calloc(1, sizeof(Cidade));
    char *openName = NULL; // Nome de abertura do arquivo
    char *name = (char *) calloc(50, sizeof(char)); // Nome da estrutura
    sprintf(name, "%s", "quadra"); // Quadra
    strcatFileName(&openName, getFullPathBd(source), &name, ".bin\0");
    tmpStruct->quadras = openFile(openName, "wb+");
    freeString(&openName);
    freeString(&name);
    return tmpStruct;
}

// Libera a memoria de toda a Cidade
void killCidade(Cidade **cityIndex) {
    fclose((*cityIndex)->quadras);
    free(*cityIndex);
}

// Adiciona uma nova estrutura no arquivo binario e na b-tree, a partir do arquivo lido
void newCityShapeFromFile(Cidade *cityIndex, char *inputLine, int typeOfData) {
    Quadra *tmpQuad = NULL;
    char *token = strtok(inputLine, " ");// Comando
    if (token == NULL) {
        return;
    }
    // Switch typeOfData
    switch (typeOfData) {
        case 1: // Quadra
            tmpQuad = allocQuadra();
            setQuadraCep(tmpQuad, strtok(NULL, " ")); // Cep
            setQuadraX(tmpQuad, newAtod(strtok(NULL, " "))); // X
            setQuadraY(tmpQuad, newAtod(strtok(NULL, " "))); // Y
            setQuadraWidth(tmpQuad, newAtod(strtok(NULL, " "))); // Width
            setQuadraHeight(tmpQuad, newAtod(strtok(NULL, " "))); // Height
            break;
        default:
            break;
    }
    printToBin(&(cityIndex->quadras), getQuadraSize(), tmpQuad);
    killQuadra(tmpQuad);
}

// Imprime as estruturas da cidade
void printCityShapes(Cidade *cityIndex) {
    Quadra *tmpQuad = allocQuadra();
    fseek(cityIndex->quadras, 0, SEEK_SET);
    printf("\n Quadras \n");
    while (!feof(cityIndex->quadras)) {
        readFromBin(&(cityIndex->quadras), getQuadraSize(), tmpQuad);
        if (!feof(cityIndex->quadras)) {
            printQuadra(tmpQuad);
        }
    }
    killQuadra(tmpQuad);
}
