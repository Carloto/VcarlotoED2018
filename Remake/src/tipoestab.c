// Include
#include "tipoestab.h"

struct tmpTipo { // Tipo
    char codt[25]; // Id do Tipo
    char descricao[50]; // Descrição do tipo
};

// Aloca e inicializa uma struct Tipo
Tipo *allocTipo() {
    Tipo *tmpTipo = (Tipo *) calloc(1, sizeof(Tipo));
    return tmpTipo;
}

// Libera a memoria de um unica Tipo
void killTipo(Tipo *tmpTipo) {
    if (tmpTipo != NULL) {
        free(tmpTipo);
    }
}

// Deleta a Tipo
void deleteTipo(Tipo *tmpQuad) {
    sprintf(tmpQuad->codt, "%s", "deletado");
}

// Retorna o tamanho de uma Tipo
size_t getTipoSize(){
    return sizeof(Tipo);
}

// Set codt
void setTipoCodt(Tipo *tmpTipo, char tmpCodt[25]) {
    sprintf(tmpTipo->codt, "%s", tmpCodt);
}

// Set descricao
void setTipodDesc(Tipo *tmpTipo, char desc[50]) {
    sprintf(tmpTipo->descricao, "%s", desc);
}

// Get codt
char *getTipoCodt(Tipo *tmpTipo) {
    return tmpTipo->codt;
}

// Get descricao
char *getTipoDesc(Tipo *tmpTipo) {
    return tmpTipo->descricao;
}

// Imprime as informações do Retangulo
void printTipo(Tipo *tmpTipo) {
    printf("\ncodt = |%s|", tmpTipo->codt);
    printf("  descricao = |%s|", tmpTipo->descricao);
}
