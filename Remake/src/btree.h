// Define
#ifndef BTREE_H
#define BTREE_H

typedef struct btNode *bTree; // Nó da b-tree

// Este modulo contem as funcoes de manipulação da b-tree
// Cada nó contem uma chave e um endereco para a estrutura dentro do arquivo

// Aloca um no da b-tree
bTree btCreate(void);

// Destroi a b-tree
void btDestroy(bTree t);

// Deleta uma certa chave
int btDeleteInfo(bTree b, unsigned long key, long int *address);

// Retorna a posicao (ftell) da struct caso esteja presente na arvore
int btGetAddress(bTree b, unsigned long key, long int *address);

// Retorna um valor diferente de zero caso a chave esteja presente
int btSearch(bTree t, unsigned long key);

// Insere um novo elemento na arvore
void btInsert(bTree t, unsigned long key, long int addr);

// Imprime os elementos da arvore
// void btPrintKeys(bTree t);

#endif //BTREE_H
