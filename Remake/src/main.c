// Modulo main do trabalho

// Include
#include <stdio.h>
#include <stdlib.h>
#include "filehandling.h"
#include "miscfunctions.h"
#include "filehandling.h"
#include "basicshapes.h"

// Main
int main(int argc, char *argv[]) {

    // Verificar se entrada de argumentos é nula
    if (argc <= 1) {
        printf("\nNenhum argumento foi encontrado na linha de comando!\n");
        return -1;
    }

    // Obtem os argumentos da linha de comando
    fileArguments *FileNames = createFileArguments();
    setFileArguments(&FileNames, argc, argv);
    //printInputArguments(FileNames);

    // Structs de figuras basicas
    BasicShapes *AllBasicShapes = allocBasicShapes();

    // Leitura de .geo
    FILE *GeoInputFile = openFile(FileNames, "r", 0);
    if (GeoInputFile == NULL) { // Verificar se foi aberto corretamente
        printf("\nFalha na abertura do arquivo!");
        killFileArguments(&FileNames);
        return -1;
    }

    char *linha = NULL; // Linha lida
    char *tmpLinha = NULL; // Copia para strtok
    int controle = 1; // Controle permite a execução da leitura, e # muda seu valor para 0
    unsigned long int hashResult = 0; // Resultado do hash

    while (!feof(GeoInputFile) && controle == 1) { // Loop de leitura

        readLine(&linha, &GeoInputFile); // Le uma linha do arquivo de entrada
        // printThis(linha); // Impime a linha lida
        copyString(&tmpLinha, linha); // Copia a linha lida
        hashResult = hash((unsigned char *) strtok(tmpLinha, " ")); // Extrai o comando
        // printf("\nResultado do hashing : %lu", hashResult);

        switch (hashResult) { // Switch dos comandos lidos
            case CMD_NX:
                //printThis(linha);
                break;

            case CMD_A:
                //printThis(linha);
                break;

            case CMD_D:
                //printThis(linha);
                break;

            case CMD_I:
                //printThis(linha);
                break;

            case CMD_O:
                //printThis(linha);
                break;

            case CMD_FIM:
                //printThis(linha);
                controle = 0; // Sinaliza o fim da leitura
                //printf("\nControle = %d", controle);
                break;

            case FIG_C:
                newShapeFromFile(AllBasicShapes, linha, 1); // 1 para circulo
                break;

            case FIG_R:
                newShapeFromFile(AllBasicShapes, linha, 2); // 2 para retangulo
                break;

            default:
                break;
        }
    }

    printBasicShapes(AllBasicShapes);
    fclose(GeoInputFile); // Fecha o arquivo .geo

    // Free structs
    killFileArguments(&FileNames);
    killBasicShapes(&AllBasicShapes);

    // Free Strings
    freeString(&linha);
    freeString(&tmpLinha);

    // End main
    return 0;

}
