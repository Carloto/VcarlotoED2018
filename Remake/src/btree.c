// Include
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "btree.h"

#define MAX_KEYS (1024)

struct btNode {
    int isLeaf; // Mostra se se este nó é folha
    int numKeys; // Numero de chaves que este no contem
    unsigned long keys[MAX_KEYS]; // Vetor de chaves
    long int address[MAX_KEYS]; // Vetor de enderecos
    struct btNode *kids[MAX_KEYS + 1];  // Vetor de nós
};

// Aloca um no da b-tree
bTree btCreate(void) {
    bTree b;

    b = malloc(sizeof(*b));
    assert(b);

    b->isLeaf = 1;
    b->numKeys = 0;

    return b;
}

// Destroi a b-tree
void btDestroy(bTree b) {
    int i;

    if (!b->isLeaf) {
        for (i = 0; i < b->numKeys + 1; i++) {
            btDestroy(b->kids[i]);
        }
    }

    free(b);
}

// retorna  menor indice i de forma que key <= a[i]
// (ou n caso i não exista)
static int searchKey(int n, const unsigned long *a, unsigned long key) {
    int lo;
    int hi;
    int mid;

    // invariavel : a[lo] < key <= a[hi]
    lo = -1;
    hi = n;

    while (lo + 1 < hi) {
        mid = (lo + hi) / 2;
        if (a[mid] == key) {
            return mid;
        } else if (a[mid] < key) {
            lo = mid;
        } else {
            hi = mid;
        }
    }

    return hi;
}

// Deleta uma certa chave
int btDeleteInfo(bTree b, unsigned long key, long int *address) {
    int pos;

    // verificar arvore vazia
    if (b->numKeys == 0) {
        return 0;
    }

    // verificar menor posicao onde a chave pode ser encontrada
    pos = searchKey(b->numKeys, b->keys, key);

    if (pos < b->numKeys && b->keys[pos] == key) {
        *address = b->address[pos];
        b->address[pos] = -1;
        return 1;
    } else {
        return (!b->isLeaf && btGetAddress(b->kids[pos], key, address));
    }
}

int btGetAddress(bTree b, unsigned long key, long int *address) {
    int pos;

    // verificar arvore vazia
    if (b->numKeys == 0) {
        return 0;
    }


    // verificar menor posicao onde a chave pode ser encontrada
    pos = searchKey(b->numKeys, b->keys, key);


    if (pos < b->numKeys && b->keys[pos] == key) {
        // verificar informacao deletada
        if (b->address[pos] == -1) {
            return 0;
        }
        *address = b->address[pos];
        return 1;
    } else {
        return (!b->isLeaf && btGetAddress(b->kids[pos], key, address));
    }
}

int btSearch(bTree b, unsigned long key) {
    int pos;

    // verificar arvore vazia
    if (b->numKeys == 0) {
        return 0;
    }

    //verificar menor posicao onde a chave pode ser encontrada
    pos = searchKey(b->numKeys, b->keys, key);

    if (pos < b->numKeys && b->keys[pos] == key) {
        return 1;
    } else {
        return (!b->isLeaf && btSearch(b->kids[pos], key));
    }
}

// inserir um novo no na arvore
// retorna nova criança a direita cas o no seja separado
// e guarda a mediana em *median
// caso contrario retorna 0
static bTree
btInsertInternal(bTree b, unsigned long key, long int addr, unsigned long *median, long int *medianAddress) {
    int pos, mid2;
    unsigned long mid;
    long int midAddr;
    bTree b2;

    pos = searchKey(b->numKeys, b->keys, key);

    if (pos < b->numKeys && b->keys[pos] == key) {
        // nada a ser feito
        return 0;
    }

    if (b->isLeaf) {

        // todos acima de pos sobem 1 espaço
        memmove(&b->keys[pos + 1], &b->keys[pos], sizeof(*(b->keys)) * (b->numKeys - pos));
        memmove(&b->address[pos + 1], &b->address[pos], sizeof(*(b->address)) * (b->numKeys - pos));
        b->keys[pos] = key;
        b->address[pos] = addr;
        b->numKeys++;

    } else {

        // insere na criança
        b2 = btInsertInternal(b->kids[pos], key, addr, &mid, &midAddr);

        // talvez inserir em b
        if (b2) {

            // todas acima de pos sobem 1 espaço
            memmove(&b->keys[pos + 1], &b->keys[pos], sizeof(*(b->keys)) * (b->numKeys - pos));
            memmove(&b->address[pos + 1], &b->address[pos], sizeof(*(b->address)) * (b->numKeys - pos));
            // nova criança em pos + 1
            memmove(&b->kids[pos + 2], &b->kids[pos + 1], sizeof(*(b->keys)) * (b->numKeys - pos));
            memmove(&b->address[pos + 2], &b->address[pos + 1], sizeof(*(b->address)) * (b->numKeys - pos));

            b->keys[pos] = mid;
            b->address[pos] = midAddr;
            b->kids[pos + 1] = b2;
            b->numKeys++;
        }
    }

    if (b->numKeys >= MAX_KEYS) {
        mid2 = b->numKeys / 2;

        *median = b->keys[mid2];
        *medianAddress = b->address[mid2];

        // cria novo no se keys > median
        /* arvore é:
         *
         *      3 5 7
         *      A B C D
         *
         * se torna
         *          (5)
         *      3        7
         *      A B      C D
         */
        b2 = malloc(sizeof(*b2));

        b2->numKeys = b->numKeys - mid2 - 1;
        b2->isLeaf = b->isLeaf;

        memmove(b2->keys, &b->keys[mid2 + 1], sizeof(*(b->keys)) * b2->numKeys);
        memmove(b2->address, &b->address[mid2 + 1], sizeof(*(b->address)) * b2->numKeys);
        if (!b->isLeaf) {
            memmove(b2->kids, &b->kids[mid2 + 1], sizeof(*(b->kids)) * (b2->numKeys + 1));
        }

        b->numKeys = mid2;

        return b2;
    } else {
        return 0;
    }
}

void btInsert(bTree b, unsigned long key, long int addr) {
    bTree b1;   // nova criança a esquerda
    bTree b2;   // nova criança a deireita
    unsigned long median;
    long int medianAddress;

    b2 = btInsertInternal(b, key, addr, &median, &medianAddress);

    if (b2) {
        // verificar mudança de raiz

        b1 = malloc(sizeof(*b1));
        assert(b1);

        // copia a raiz para b1
        memmove(b1, b, sizeof(*b));

        // atualiza a raiz
        b->numKeys = 1;
        b->isLeaf = 0;
        b->keys[0] = median;
        b->address[0] = medianAddress;
        b->kids[0] = b1;
        b->kids[1] = b2;
    }
}
