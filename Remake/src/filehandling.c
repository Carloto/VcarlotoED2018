// Modulo para lidar com a entrada e saida de arquivos

// Include
#include "filehandling.h"

// Struct para guardar a entrada de argumentos
struct tmp_fileArguments {
    char *input_e; // Argumento do comando -e
    char *input_f; // Argumento do comando -f
    char *input_q; // Argumento do comando -q
    char *input_ec; // Argumento do comando -ec
    char *input_pm; // Argumento do comando -pm
    char *output_o; // Argumento do comando -o
    char *path_bd; // Argumento do comando -bd
    char *inputGeoFileName; // Nome completo do arquivo .geo
    char *inputQryFileName; // Nome completo do arquivo .qry
    char *inputEcFileName; // Nome completo do arquivo .ec
    char *inputPmFileName; // Nome completo do arquivo .pm
    char *inputGeoName; // Nome isolado do arquivo .geo
    char *outputQrySvgName; // Nome isolado do arquivo .geo
    char *outputSvgStandardFileName; // Arquivo de saida .svg principal
    char *outputTxtFileName; // Arquivo de saida .txt
    char *full_path_bd; // Path completo do banco de dados
};

// Inicializar fileArguments
fileArguments *createFileArguments() {
    fileArguments *create_struct = (fileArguments *) calloc(1, sizeof(fileArguments));
    create_struct->input_e = NULL;
    create_struct->input_f = NULL;
    create_struct->input_q = NULL;
    create_struct->input_ec = NULL;
    create_struct->input_pm = NULL;
    create_struct->output_o = NULL;
    create_struct->path_bd = NULL;
    create_struct->inputGeoFileName = NULL;
    create_struct->inputQryFileName = NULL;
    create_struct->inputEcFileName = NULL;
    create_struct->inputPmFileName = NULL;
    create_struct->inputGeoName = NULL;
    create_struct->outputQrySvgName = NULL;
    create_struct->outputSvgStandardFileName = NULL;
    create_struct->outputTxtFileName = NULL;
    create_struct->full_path_bd = NULL;
    return create_struct;
}

// Destruir fileArguments
void killFileArguments(fileArguments **kill_struct) {
    freeString(&(*kill_struct)->input_e);
    freeString(&(*kill_struct)->input_f);
    freeString(&(*kill_struct)->input_q);
    freeString(&(*kill_struct)->input_ec);
    freeString(&(*kill_struct)->input_pm);
    freeString(&(*kill_struct)->output_o);
    freeString(&(*kill_struct)->path_bd);
    freeString(&(*kill_struct)->inputGeoFileName);
    freeString(&(*kill_struct)->inputQryFileName);
    freeString(&(*kill_struct)->inputEcFileName);
    freeString(&(*kill_struct)->inputPmFileName);
    freeString(&(*kill_struct)->inputGeoName);
    freeString(&(*kill_struct)->outputQrySvgName);
    freeString(&(*kill_struct)->outputSvgStandardFileName);
    freeString(&(*kill_struct)->outputTxtFileName);
    freeString(&(*kill_struct)->full_path_bd);
    free(*kill_struct);
}

// Imprimir fileArguments
void printInputArguments(fileArguments *print_struct) {
    printThis(print_struct->input_e);
    printThis(print_struct->input_f);
    printThis(print_struct->input_q);
    printThis(print_struct->input_ec);
    printThis(print_struct->input_pm);
    printThis(print_struct->output_o);
    printThis(print_struct->path_bd);
    printThis(print_struct->inputGeoFileName);
    printThis(print_struct->inputQryFileName);
    printThis(print_struct->inputEcFileName);
    printThis(print_struct->inputPmFileName);
    printThis(print_struct->inputGeoName);
    printThis(print_struct->outputQrySvgName);
    printThis(print_struct->outputSvgStandardFileName);
    printThis(print_struct->outputTxtFileName);
    printThis(print_struct->full_path_bd);
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
        if (strcmp("-q", argv[i]) == 0) {
            i++;
            copyString(&(*set_struct)->input_q, argv[i]);
        }
        if (strcmp("-ec", argv[i]) == 0) {
            i++;
            copyString(&(*set_struct)->input_ec, argv[i]);
        }
        if (strcmp("-pm", argv[i]) == 0) {
            i++;
            copyString(&(*set_struct)->input_pm, argv[i]);
        }
        if (strcmp("-bd", argv[i]) == 0) {
            i++;
            copyString(&(*set_struct)->path_bd, argv[i]);
        }
    }

    // Concatenar path do banco de dados
    strcatFileName(&(*set_struct)->full_path_bd, (*set_struct)->output_o, &(*set_struct)->path_bd, "\0");
    struct stat st = {0};
    if (stat((*set_struct)->full_path_bd, &st) == -1) { // Verifica se o diretorio já existe
        mkdir((*set_struct)->full_path_bd, 0700); // Cria o diretorio
    }

    // Verificar se existe input
    if ((*set_struct)->input_f != NULL) {
        // Isolar nome do arquivo
        cutFileName(&(*set_struct)->inputGeoName, (*set_struct)->input_f);
        // Concatenar nome do arquivo de saida .svg
        strcatFileName(&(*set_struct)->outputSvgStandardFileName, (*set_struct)->output_o, &(*set_struct)->inputGeoName,
                       ".svg\0");
        // Verificar se -f possui "." e concatenar nome do arquivo geo
        if ((*set_struct)->input_e != NULL) {
            if ((*set_struct)->input_f[0] == '.') {
                removeFirstChar(&(*set_struct)->input_f);
            }
            strcatFileName((&(*set_struct)->inputGeoFileName), (*set_struct)->input_e, &(*set_struct)->input_f,
                           "\0");
        } else {
            copyString(&(*set_struct)->inputGeoFileName, (*set_struct)->input_f);
        }
    }

    // Verificar se existe qry
    if ((*set_struct)->input_q != NULL) {
        // Verificar se -f possui "." e concatenar nome do arquivo qry
        if ((*set_struct)->input_e != NULL) {
            if ((*set_struct)->input_q[0] == '.') {
                removeFirstChar(&(*set_struct)->input_q);
            }
            strcatFileName((&(*set_struct)->inputQryFileName), (*set_struct)->input_e, &(*set_struct)->input_q,
                           "\0");
        } else {
            copyString(&(*set_struct)->inputQryFileName, (*set_struct)->input_q);
        }
        // Isolar nome do arquivo qry
        cutFileName(&(*set_struct)->outputQrySvgName, (*set_struct)->input_q);
        // Concatenar nome do arquivo de saida .svg do qry
        strcatName(&(*set_struct)->input_q, (*set_struct)->inputGeoName, &(*set_struct)->outputQrySvgName, "-");
        strcatFileName(&(*set_struct)->outputQrySvgName, (*set_struct)->output_o, &(*set_struct)->input_q, ".svg");
    }

    // Verificar se existe ec
    if ((*set_struct)->input_ec != NULL) {
        // Verificar se -ec possui "." e concatenar nome do arquivo ec
        if ((*set_struct)->input_e != NULL) {
            if ((*set_struct)->input_ec[0] == '.') {
                removeFirstChar(&(*set_struct)->input_ec);
            }
            strcatFileName((&(*set_struct)->inputEcFileName), (*set_struct)->input_e, &(*set_struct)->input_ec,
                           "\0");
        } else {
            copyString(&(*set_struct)->inputEcFileName, (*set_struct)->input_ec);
        }
    }

    // Verificar se existe pm
    if ((*set_struct)->input_pm != NULL) {
        // Verificar se -pm possui "." e concatenar nome do arquivo pm
        if ((*set_struct)->input_pm != NULL) {
            if ((*set_struct)->input_pm[0] == '.') {
                removeFirstChar(&(*set_struct)->input_pm);
            }
            strcatFileName((&(*set_struct)->inputPmFileName), (*set_struct)->input_e, &(*set_struct)->input_pm,
                           "\0");
        } else {
            copyString(&(*set_struct)->inputPmFileName, (*set_struct)->input_pm);
        }
    }

    // Concatenar nome do arquivo de saida .txt
    strcatFileName(&(*set_struct)->outputTxtFileName, (*set_struct)->output_o, &(*set_struct)->inputGeoName,
                   ".txt\0");
}

// Lê uma linha do arquivo de entrada
void readLine(char **line, FILE **input) {
    freeString(line);
    *line = (char *) calloc(M_BUFFER, sizeof(char));
    fgets(*line, M_BUFFER, *input);
    *line = strtok(*line, "\r\n");
}

// Abre um arquivo
FILE *openFile(char *fileName, char accessType[6]) {
    FILE *fileToOpen = NULL; // Arquivo a ser aberto
    fileToOpen = fopen(fileName, accessType); // Abrir arquivo
    return fileToOpen; // Retorno
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

// Imprime um tipo de dado no arquivo binario
void printToBin(FILE **binFile, size_t dataSize, void *data) {
    fwrite(data, dataSize, 1, *binFile);
}

// Lê um tipo de dado no arquivo binario
void readFromBin(FILE **binFile, size_t dataSize, void *data) {
    fread(data, dataSize, 1, *binFile);
}

// Retorna o nome de do arquivo base
char *getInputGeoName(fileArguments *tmpStructs) {
    return tmpStructs->inputGeoName;
}

// Retorna o nome de do arquivo de entrada .geo
char *getInputGeoFileName(fileArguments *tmpStructs) {
    return tmpStructs->inputGeoFileName;
}

// Retorna o nome de do arquivo de entrada .qry
char *getInputQryFileName(fileArguments *tmpStructs) {
    return tmpStructs->inputQryFileName;
}

// Retorna o nome de do arquivo de entrada .ec
char *getInputEcFileName(fileArguments *tmpStructs) {
    return tmpStructs->inputEcFileName;
}

// Retorna o nome de do arquivo de entrada .pm
char *getInputPmFileName(fileArguments *tmpStructs) {
    return tmpStructs->inputPmFileName;
}

// Retorna o nome de do arquivo de saida .svg do qry
char *getOutputQrySvgName(fileArguments *tmpStructs) {
    return tmpStructs->outputQrySvgName;
}

// Retorna o nome do arquivo de saida .svg padrão
char *getOutputSvgStandardFileName(fileArguments *tmpStructs) {
    return tmpStructs->outputSvgStandardFileName;
}

// Retorna o nome do arquivo de saida .txt padrão
char *getOutputTxtFileName(fileArguments *tmpStructs) {
    return tmpStructs->outputTxtFileName;
}

// Retorna o nome base
char *getBaseName(fileArguments *tmpStructs) {
    return tmpStructs->inputGeoName;
}

// Retorna o output path
char *getOutputPath(fileArguments *tmpStructs) {
    return tmpStructs->output_o;
}

// Retorna o diretorio do banco de dados
char *getFullPathBd(fileArguments *tmpStructs) {
    return tmpStructs->full_path_bd;
}
