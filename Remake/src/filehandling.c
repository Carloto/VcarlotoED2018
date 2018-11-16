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
    char *outputSvgStandardFileName; // Arquivo de saida .svg principal
    char *outputTxtFileName; // Arquivo de saida .txt
};

// Inicializar fileArguments
fileArguments *createFileArguments() {
    fileArguments *create_struct = (fileArguments *) calloc(1, sizeof(fileArguments));
    create_struct->input_e = NULL;
    create_struct->input_f = NULL;
    create_struct->output_o = NULL;
    create_struct->inputGeoFileName = NULL;
    create_struct->inputGeoName = NULL;
    create_struct->outputSvgStandardFileName = NULL;
    create_struct->outputTxtFileName = NULL;
    return create_struct;
}

// Destruir fileArguments
void killFileArguments(fileArguments **kill_struct) {
    freeString(&(*kill_struct)->input_e);
    freeString(&(*kill_struct)->input_f);
    freeString(&(*kill_struct)->output_o);
    freeString(&(*kill_struct)->inputGeoFileName);
    freeString(&(*kill_struct)->inputGeoName);
    freeString(&(*kill_struct)->outputSvgStandardFileName);
    freeString(&(*kill_struct)->outputTxtFileName);
    free(*kill_struct);
}

// Imprimir fileArguments
void printInputArguments(fileArguments *print_struct) {
    printThis(print_struct->input_e);
    printThis(print_struct->input_f);
    printThis(print_struct->output_o);
    printThis(print_struct->inputGeoFileName);
    printThis(print_struct->inputGeoName);
    printThis(print_struct->outputSvgStandardFileName);
    printThis(print_struct->outputTxtFileName);
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
    strcatFileName(&(*set_struct)->outputSvgStandardFileName, (*set_struct)->output_o, &(*set_struct)->inputGeoName,
                   "svg\0");

    // Concatenar nome do arquivo de saida .txt
    strcatFileName(&(*set_struct)->outputTxtFileName, (*set_struct)->output_o, &(*set_struct)->inputGeoName,
                   "txt\0");

    // Verificar se -f possui "." e concatenar nome do arquivo geo
    if ((*set_struct)->input_e != NULL) {
        if ((*set_struct)->input_f[0] == '.') {
            removeFirstChar(&(*set_struct)->input_f);
        }
        strcatFileName((&(*set_struct)->inputGeoFileName), (*set_struct)->input_e, &(*set_struct)->inputGeoName,
                       "geo\0");
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
FILE *openFile(char *fileName, char accessType[3]) {
    FILE *fileToOpen = NULL; // Arquivo a ser aberto
    fileToOpen = fopen(fileName, accessType); // Abrir arquivo
    return fileToOpen; // Retorno
}

// Retorna o nome de do arquivo base
char *getInputGeoName(fileArguments *tmpStructs) {
    return tmpStructs->inputGeoName;
}

// Retorna o nome de do arquivo de entrada .geo
char *getInputGeoFileName(fileArguments *tmpStructs) {
    return tmpStructs->inputGeoFileName;
}

// Retorna o nome do arquivo de saida .svg padrão
char *getOutputSvgStandardFileName(fileArguments *tmpStructs) {
    return tmpStructs->outputSvgStandardFileName;
}

// Retorna o nome do arquivo de saida .txt padrão
char *getOutputTxtFileName(fileArguments *tmpStructs) {
    return tmpStructs->outputTxtFileName;
}

// Imprime tags svg
void printTagSvg(FILE **outputFile, int type) {
    switch (type) {
        case 0: // Tag de início
            fprintf(*outputFile, "<svg>\n");
            break;
        case 1: // Tag de fim
            fprintf(*outputFile, "</svg>");
            break;
        default:
            break;
    }
}
