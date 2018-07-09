#include "mergesort.h"

/* Inicializa as variaveis necessarias para o MergeSort e imprime o resultado no txt */
void crb(FILE** OutputTxtStd, ListaGenerica** headRef, Circle **CircDash, Circle **CircDashFim) {

	char space[2] = " ";
	char resposta[20];
	space[1] = '\0';

	*CircDash = create_cnode(*CircDash);
	*CircDashFim = create_cnode(*CircDash);
	(*CircDashFim)->next = NULL;
	(*CircDash)->next = *CircDashFim;
	(*CircDash)->raio = 10;
	(*CircDashFim)->raio = 10;

	float *dist = (float *) calloc(1, sizeof(float));
	float exp = 2;
	ListaGenerica *temp_node;

	/* Verificar se a cabaça tem mais de 1 nó */
	if (((*headRef) == NULL) || ((*headRef)->next == NULL))
	{
		return;
	}

	temp_node = (*headRef)->next;

	/* Inicializar a distancia */
	*dist = sqrt(pow(((Torre *)(*headRef)->data)->x - ((Torre *)temp_node->data)->x, exp) + pow(((Torre *)(*headRef)->data)->y - ((Torre *)temp_node->data)->y, exp));

	MergeSort(headRef, dist, CircDash, CircDashFim);

	sprintf(resposta, "%s : ", "Torres");
	rtprint_txt(OutputTxtStd, NULL,
	            resposta, -2);
	rtprint_txt(OutputTxtStd, NULL,
	            (*CircDash)->cor1, -2);
	rtprint_txt(OutputTxtStd, NULL,
	            (*CircDashFim)->cor1, -2);
	sprintf(resposta, " | %s : ", "Distancia");
	rtprint_txt(OutputTxtStd, NULL,
	            resposta, -2);
	rtprint_txt(OutputTxtStd, ((*CircDash)->cor1),
	            (*CircDash)->cor1,
	            *dist);
	rtprint_txt(OutputTxtStd,
	            NULL,
	            space,
	            -1);


	free(dist);

}

/* Ordena a lista mudando para onde os nós apontam */
void MergeSort(ListaGenerica** headRef, float *d, Circle **CircDash, Circle **CircDashFim) {
	ListaGenerica* head = *headRef;
	ListaGenerica* a;
	ListaGenerica* b;

	if ((head == NULL) || (head->next == NULL))
	{
		return;
	}

	FrontBackSplit(head, &a, &b);

	MergeSort(&a, d, CircDash, CircDashFim);
	MergeSort(&b, d, CircDash, CircDashFim);

	*headRef = SortedMerge(a, b, d, CircDash, CircDashFim);
}

/* Verifica a distancia e mescla as listas */
ListaGenerica* SortedMerge(ListaGenerica* a, ListaGenerica* b, float *d, Circle **CircDash, Circle **CircDashFim) {
	ListaGenerica* result = NULL;

	float dist;
	float exp = 2;

	if (a == NULL)
		return(b);
	else if (b == NULL)
		return(a);

	dist = sqrt(pow(((Torre *)a->data)->x - ((Torre *)b->data)->x, exp) + pow(((Torre *)a->data)->y - ((Torre *)b->data)->y, exp));

	if (dist < *d) {
		*d = dist;
		(*CircDash)->x = ((Torre *)a->data)->x;
		(*CircDashFim)->x = ((Torre *)b->data)->x;
		(*CircDash)->y = ((Torre *)a->data)->y;
		(*CircDashFim)->y = ((Torre *)b->data)->y;
		free_string(&((*CircDash)->cor1));
		(*CircDash)->cor1 = (char *)calloc(strlen(((Torre *)a->data)->id)+1, sizeof(char));
		strcpy((*CircDash)->cor1,((Torre *)a->data)->id);
		free_string(&((*CircDashFim)->cor1));
		(*CircDashFim)->cor1 = (char *)calloc(strlen(((Torre *)b->data)->id)+1, sizeof(char));
		strcpy((*CircDashFim)->cor1,((Torre *)b->data)->id);
		result = a;
		result->next = SortedMerge(a->next, b, d, CircDash, CircDashFim);
	}
	else
	{
		result = b;
		result->next = SortedMerge(a, b->next, d, CircDash, CircDashFim);
	}
	return(result);
}

/* Separa a lista em duas partes. */
void FrontBackSplit(ListaGenerica* source,
                    ListaGenerica** frontRef, ListaGenerica** backRef) {
	ListaGenerica* fast;
	ListaGenerica* slow;
	slow = source;
	fast = source->next;

	/* 'fast' avança dois nós, e slow avança um nó */
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}

	*frontRef = source;
	*backRef = slow->next;
	slow->next = NULL;
}
