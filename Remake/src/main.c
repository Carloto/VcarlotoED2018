// Modulo main do trabalho

// Include
#include <stdio.h>
#include <stdlib.h>
#include "filehandling.h"
#include "structlib.h"
#include "miscfunctions.h"
#include "filehandling.h"

// Main
int main(int argc, char *argv[]) {

    // Verificar se entrada de argumentos é nula
    if (argc <= 1) {
        printf("\nNenhum argumento foi encontrado na linha de comando!\n");
        return -1;
    }

    // Obtem os argumentos da linha de comando
    fileArguments *FileNames = createInputArguments();
    setInputArguments(&FileNames, argc, argv);
    printInputArguments(FileNames);

    // Leitura de .geo
    FILE *InputGeo = NULL;
    if (openFile(FileNames->geoInput, "r", &InputGeo) == -1) { // Verificar se foi aberto corretamente
        killInputArguments(FileNames);
        return -1;
    }

    char *linha = NULL;
    char *tmpLinha = NULL;
    int controle = 1; // Controle permite a execução da leitura, e # muda seu valor para 0
    unsigned long int hashResult = 0;

    while (!feof(InputGeo) && controle == 1) { // Loop de leitura
        /*if (feof(InputGeo)){
            break;
        }*/
        readLine(&linha, &InputGeo); // Le uma linha do arquivo de entrada
        // print_this(linha); // Impime a linha lida
        copyString(&tmpLinha, linha);
        hashResult = hash((unsigned char *) strtok(tmpLinha, " "));
        printf("\nResultado do hashing : %lu", hashResult);
        switch (hashResult) { // Switch dos comandos lidos
            case CMD_NX:
                print_this(linha);
                break;

            case CMD_A:
                print_this(linha);
                break;

            case CMD_D:
                print_this(linha);
                break;

            case CMD_I:
                print_this(linha);
                break;

            case CMD_O:
                print_this(linha);
                break;
            case CMD_FIM:
                print_this(linha);
                controle = 0; // Sinaliza o fim da leitura
                printf("\nControle = %d", controle);
                break;

            case FIG_C:
                print_this(linha);
                break;

            case FIG_R:
                print_this(linha);
                break;

            default:
                break;
        }
    }

    fclose(InputGeo); // Fecha o arquivo .geo

    // Free structs
    killInputArguments(FileNames);

    // Free Strings
    free_string(&linha);
    free_string(&tmpLinha);

    // End main
    return 0;

}
