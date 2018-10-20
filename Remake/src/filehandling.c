// Modulo para lidar com a entrada e saida de arquivos

// Include
#include "filehandling.h"

// Inicializar fileArguments
fileArguments *createInputArguments() {
    fileArguments *create_struct = (fileArguments *) calloc(1, sizeof(fileArguments));
    create_struct->input_e = NULL;
    create_struct->input_f = NULL;
    create_struct->output_o = NULL;
    create_struct->geo_input_name = NULL;
    return create_struct;
}

// Destruir fileArguments
void killInputArguments(fileArguments *kill_struct) {
    free_string(&(kill_struct->input_e));
    free_string(&(kill_struct->input_f));
    free_string(&(kill_struct->output_o));
    free_string(&(kill_struct->geo_input_name));
    free(kill_struct);
}

// Imprimir fileArguments
void printInputArguments(fileArguments *print_struct) {
    print_this(print_struct->input_e);
    print_this(print_struct->input_f);
    print_this(print_struct->output_o);
    print_this(print_struct->geo_input_name);
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
        strcatFileName((&(*set_struct)->geo_input_name), (*set_struct)->input_e, &(*set_struct)->input_f);
    } else {
        copyString(&(*set_struct)->geo_input_name, (*set_struct)->input_f);
    }
}

// Lê uma linha do arquivo de entrada
void readLine(char **line, FILE **input) {
    free_string(line);
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
