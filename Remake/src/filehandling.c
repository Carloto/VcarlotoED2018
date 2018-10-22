// Modulo para lidar com a entrada e saida de arquivos

// Include
#include "filehandling.h"

// Inicializar fileArguments
fileArguments *createInputArguments() {
    fileArguments *create_struct = (fileArguments *) calloc(1, sizeof(fileArguments));
    create_struct->input_e = NULL;
    create_struct->input_f = NULL;
    create_struct->output_o = NULL;
    create_struct->geoInputName = NULL;
    create_struct->geoName = NULL;
    create_struct->GeoInputFile = NULL;
    return create_struct;
}

// Destruir fileArguments
void killInputArguments(fileArguments **kill_struct) {
    freeString(&(*kill_struct)->input_e);
    freeString(&(*kill_struct)->input_f);
    freeString(&(*kill_struct)->output_o);
    freeString(&(*kill_struct)->geoInputName);
    freeString(&(*kill_struct)->geoName);
    free(*kill_struct);
}

// Imprimir fileArguments
void printInputArguments(fileArguments *print_struct) {
    printThis(print_struct->input_e);
    printThis(print_struct->input_f);
    printThis(print_struct->output_o);
    printThis(print_struct->geoInputName);
    printThis(print_struct->geoName);
}

// Obtem os argumentos de argv
void setInputArguments(fileArguments **set_struct, int argc, char *argv[]) {
    // Loop para encontrar argv
    for (int i = 0; i < argc; i++) {
        if (strcmp("-e", argv[i]) == 0) {
            i++;
            copyString(&(*set_struct)->input_e, argv[i]);
        }

        if (strcmp("-f", argv[i]) == 0) {
            i++;
            copyString(&(*set_struct)->input_f, argv[i]);
        }

        if (strcmp("-o", argv[i]) == 0) {
            i++;
            copyString(&(*set_struct)->output_o, argv[i]);
        }
    }

    // Verificar se -f possui "." e concatenar nome do arquivo geo
    if ((*set_struct)->input_e != NULL) {
        if ((*set_struct)->input_f[0] == '.') {
            removeFirstChar(&(*set_struct)->input_f);
        }
        strcatFileName((&(*set_struct)->geoInputName), (*set_struct)->input_e, &(*set_struct)->input_f);
    } else {
        copyString(&(*set_struct)->geoInputName, (*set_struct)->input_f);
    }

    // Isolar nome do arquivo
    cutFileName(&(*set_struct)->geoName, (*set_struct)->geoInputName);

}

// Lê uma linha do arquivo de entrada
void readLine(char **line, FILE **input) {
    freeString(line);
    *line = (char *) calloc(M_BUFFER, sizeof(char));
    fgets(*line, M_BUFFER, *input);
    *line = strtok(*line, "\r\n");
}

// Abre um arquivo
int openFile(char *fileName, char accessType[3], FILE **fileToOpen) {
    // Abrir arquivo
    *fileToOpen = fopen(fileName, accessType);

    // Falha
    if (*fileToOpen == NULL) {
        perror("Erro na abertura do arquivo");
        return -1;
    }

    // Sucesso
    return 1;
}
