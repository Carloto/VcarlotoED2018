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
    if (openFile(FileNames->geo_input_name, "r", &InputGeo) == -1) { // Verificar se foi aberto corretamente
        killInputArguments(FileNames);
        return -1;
    }

    char *linha = NULL;

    while (!feof(InputGeo)) { // Loop de leitura
        /*if (feof(InputGeo)){
            break;
        }*/
        readLine(&linha, &InputGeo);
        print_this(linha);
    }

    fclose(InputGeo); // Fecha o arquivo .geo

    // Free structs
    killInputArguments(FileNames);

    // Free Strings
    free_string(&linha);

    // End main
    return 0;

}
