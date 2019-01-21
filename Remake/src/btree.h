// Define
#ifndef BTREE_H
#define BTREE_H

typedef struct btNode *bTree; // No da b-tree

// Este modulo contem as funcoes de manipulação da b-tree

// Aloca um no da b-tree
bTree btCreate(void);

// Destroi a b-tree
void btDestroy(bTree t);

// Retorna a posicao (ftell) da struct caso esteja presente na arvore
int btGetAddress(bTree b, unsigned long key, long int *address);

/* return nonzero if key is present in tree */
int btSearch(bTree t, unsigned long key);

/* insert a new element into a tree */
void btInsert(bTree t, unsigned long key, long int addr);

/* print all keys of the tree in order */
void btPrintKeys(bTree t);

#endif //BTREE_H
