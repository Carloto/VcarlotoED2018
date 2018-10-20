// Include
#include <stdio.h>
#include "miscfunctions.h"

// Imprime uma string
void print_this(char *output) {
    if (output != NULL) {
        printf("\n|%s|", output);
    }
}

// Copia uma string
void copyString(char **final, char *aux) {
    size_t len = 0;
    len = strlen(aux);
    free_string(final);
    *final = (char *) calloc(len + 1, sizeof(char));
    strcpy(*final, aux);
}

// Free String
void free_string(char **temp_free) {
    if (*temp_free != NULL) {
        free(*temp_free);
    }
    *temp_free = NULL;
}

// Remove o primeiro character
void removeFirstChar(char **final) {
    size_t len;
    char *aux;
    len = strlen(*final);
    aux = (char *) calloc(len, sizeof(char));
    for (int i = 1, j = 0; i < len; i++, j++) {
        aux[j] = (*final)[i];
    }

    aux[len - 1] = '\0';
    free_string(final);
    *final = (char *) calloc(len, sizeof(char));
    strcpy(*final, aux);
    free_string(&aux);
}

// Concatena nomes de arquivos
void strcatFileName(char **final, char *before, char **after) {
    size_t lenBefore = 0;
    size_t lenAfter = 0;
    lenBefore = strlen(before);
    lenAfter = strlen(*after);

    // Verifica a occorencia de "/"
    if ((before[lenBefore - 1] == '/' && *after[0] != '/') || (before[lenBefore - 1] != '/' && (*after)[0] == '/')) {
        *final = (char *) calloc(lenBefore + lenAfter + 1, sizeof(char));
        sprintf(*final, "%s%s", before, *after);
    } else if (before[lenBefore - 1] == '/' && (*after)[0] == '/') {
        removeFirstChar(after);
        *final = (char *) calloc(lenBefore + lenAfter + 1, sizeof(char));
        sprintf(*final, "%s%s", before, *after);
    } else if (before[lenBefore - 1] != '/' && (*after)[0] != '/') {
        *final = (char *) calloc(lenBefore + lenAfter + 2, sizeof(char));
        sprintf(*final, "%s/%s", before, *after);
    }

}

// Função de hashing para strings
unsigned long hash(unsigned char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = (hash * 33) + c; /* hash * 33 + c */
    }
    return hash;
}

// Isola o nome de um arquivo
void cutFileName(char **final, char *aux) {
    int i, j;
    size_t len = 0;
    free_string(final);
    len = strlen(aux);
    for (i = (int) len; i > -1; i--) { // Verificar a ocorrencia de / no meio do nome
        if (aux[i] == '/') {
            break;
        }
    }
    if (i == -1) { // Loop no final, não há path
        *final = (char *) calloc(len + 1, sizeof(char));
        i = 0;

        for (j = 0; j < (int) len - 4; j++, i++) {
            (*final)[j] = aux[i];
        }
        (*final)[len - 4] = '\0';
    } else {
        /* O loop não chegou no final, logo, há path */
        len = len - i;
        *final = (char *) calloc(len + 1, sizeof(char));
        i++;
        for (j = 0; j < len - 5; j++, i++) {
            (*final)[j] = aux[i];
        }
        (*final)[len - 5] = '\0';
    }
}
