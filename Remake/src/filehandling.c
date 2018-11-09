// Modulo para lidar com a entrada e saida de arquivos

// Include
#include "filehandling.h"

// Struct para guardar a entrada de argumentos
struct tmp_fileArguments {
    char *input_e; // Argumento do comando -e
    char *input_f; // Argumento do comando -f
    char *output_o; // Argumento do comando -o
    char *inputGeoFileName; // Nome completo do arquivo .geo
    char *inputGeoName; // Nome isolado do arquivo .geo
    char *outputSvgStandard; // Arquivo de saida .svg principal
};

// Inicializar fileArguments
fileArguments *createFileArguments() {
    fileArguments *create_struct = (fileArguments *) calloc(1, sizeof(fileArguments));
    create_struct->input_e = NULL;
    create_struct->input_f = NULL;
    create_struct->output_o = NULL;
    create_struct->inputGeoFileName = NULL;
    create_struct->inputGeoName = NULL;
    create_struct->outputSvgStandard = NULL;
    return create_struct;
}

// Destruir fileArguments
void killFileArguments(fileArguments **kill_struct) {
    freeString(&(*kill_struct)->input_e);
    freeString(&(*kill_struct)->input_f);
    freeString(&(*kill_struct)->output_o);
    freeString(&(*kill_struct)->inputGeoFileName);
    freeString(&(*kill_struct)->inputGeoName);
    freeString(&(*kill_struct)->outputSvgStandard);
    free(*kill_struct);
}

// Imprimir fileArguments
void printInputArguments(fileArguments *print_struct) {
    printThis(print_struct->input_e);
    printThis(print_struct->input_f);
    printThis(print_struct->output_o);
    printThis(print_struct->inputGeoFileName);
    printThis(print_struct->inputGeoName);
    printThis(print_struct->outputSvgStandard);
}

// Obtem os argumentos de argv e montar os nomes dos arquivos
void setFileArguments(fileArguments **set_struct, int argc, char **argv) {
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

    // Isolar nome do arquivo
    cutFileName(&(*set_struct)->inputGeoName, (*set_struct)->input_f);

    // Concatenar nome do arquivo de saida .svg
    strcatFileName(&(*set_struct)->outputSvgStandard, (*set_struct)->output_o, &(*set_struct)->inputGeoName, "svg\0");

    // Verificar se -f possui "." e concatenar nome do arquivo geo
    if ((*set_struct)->input_e != NULL) {
        if ((*set_struct)->input_f[0] == '.') {
            removeFirstChar(&(*set_struct)->input_f);
        }
        strcatFileName((&(*set_struct)->inputGeoFileName), (*set_struct)->input_e, &(*set_struct)->inputGeoName, "geo\0");
    } else {
        copyString(&(*set_struct)->inputGeoFileName, (*set_struct)->input_f);
    }

}

// Lê uma linha do arquivo de entrada
void readLine(char **line, FILE **input) {
    freeString(line);
    *line = (char *) calloc(M_BUFFER, sizeof(char));
    fgets(*line, M_BUFFER, *input);
    *line = strtok(*line, "\r\n");
}

// Abre um arquivo
FILE *openFile(fileArguments *tmpStruct, char accessType[3], int fileName) {
    // Arquivo a ser aberto
    FILE *fileToOpen = NULL;
    // Detectar arquivo resquisitado
    switch (fileName) {
        case 0: // Arquivo de entrada .geo
            fileToOpen = fopen(tmpStruct->inputGeoFileName, accessType);
            break;

        default:
            break;
    }
    // Retorno
    return fileToOpen;
}
