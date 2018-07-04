#include "semaforo.h"


/* Adiciona um novo semaforo*/
void new_semaforo(ListaGenerica **sem_head,
                  ListaGenerica **sem_end,
                  char           *input_line,
                  Cores          *colors) {
	char *token = NULL;

	/* Cria um novo no na lista */
	ListaGenerica *new_node = (ListaGenerica *)calloc(1, sizeof(ListaGenerica));

	/* Inicializa a struct semaforo*/
	Semaforo *temp_sem = (Semaforo *)calloc(1, sizeof(Semaforo));

	temp_sem->id = NULL;

	token = strtok(input_line, " ");

	token        = strtok(NULL, " ");
	temp_sem->id = (char *)calloc(strlen(token) + 1, sizeof(char));
	strcpy(temp_sem->id, token);

	token       = strtok(NULL, " ");
	temp_sem->x = atof(token);

	token       = strtok(NULL, " ");
	temp_sem->y = atof(token);

	temp_sem->width  = 15;
	temp_sem->height = 35;

	temp_sem->cor1 = (char *)calloc(strlen(colors->sem_stroke) + 1, sizeof(char));
	strcpy(temp_sem->cor1, colors->sem_stroke);

	temp_sem->cor2 = (char *)calloc(strlen(colors->sem_fill) + 1, sizeof(char));
	strcpy(temp_sem->cor2, colors->sem_fill);

	new_node->data = temp_sem;

	if (*sem_head == NULL) {
		(*sem_head)      = new_node;
		*sem_end         = *sem_head;
		(*sem_end)->next = NULL;
	} else {
		(*sem_end)->next = new_node;
		(*sem_end)       = (*sem_end)->next;
		(*sem_end)->next = NULL;
	}

	/*printf("\n%s", ((Semaforo *)(*quad_end)->data)->cep);*/
}

/* Free na struct e seus elementos */
void free_semaforo(ListaGenerica *temp_struct) {
	ListaGenerica *aux;

	while (temp_struct != NULL) {
		aux         = temp_struct;
		temp_struct = temp_struct->next;
		free_string(&(((Semaforo *)aux->data)->id));
		free_string(&(((Semaforo *)aux->data)->cor1));
		free_string(&(((Semaforo *)aux->data)->cor2));
		free(aux->data);
		free(aux);
	}
}

/* Imprimir o ultimo semaforo lido no svg */
void rtsem_svg(FILE **OutputFile, ListaGenerica *SemFim) {
	float x;
	float y;

	fprintf(*OutputFile,
	        "\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill-opacity=\"0.7\" stroke-opacity=\"0.7\" ",
	        ((Semaforo *)SemFim->data)->x,
	        ((Semaforo *)SemFim->data)->y,
	        ((Semaforo *)SemFim->data)->width,
	        ((Semaforo *)SemFim->data)->height);

	fprintf(*OutputFile,
	        "stroke=\"%s\" fill=\"%s\" style=\"stroke-width: 3\" />\n",
	        ((Semaforo *)SemFim->data)->cor1,
	        ((Semaforo *)SemFim->data)->cor2);

	x = (((Semaforo *)SemFim->data)->width / 2) + ((Semaforo *)SemFim->data)->x;
	y = (((Semaforo *)SemFim->data)->height / 2) + ((Semaforo *)SemFim->data)->y;

	fprintf(*OutputFile,
	        "\t<text x=\"%f\" y=\"%f\" fill=\"white\" stroke=\"black\" text-anchor=\"middle\" alignment-baseline=\"central\" style=\"stroke-width: 0.5\" fill-opacity=\"0.7\" stroke-opacity=\"0.7\" >%s</text>\n",
	        x,
	        y,
	        "S");
}

/* Imprimir toda a lista de semaforos na saida svg */
void psem_svg(FILE **OutputFile, ListaGenerica *lista_semaforo) {
	ListaGenerica *sem_head = lista_semaforo;

	while (sem_head != NULL) {
		rtsem_svg(OutputFile, sem_head);
		sem_head = sem_head->next;
	}
}

/* Encontra a figura dado um id */
int find_id_semaforo(ListaGenerica **sem_node, ListaGenerica *Semaforos, char *id) {
	ListaGenerica *temp_node = Semaforos;

	while (temp_node != NULL) {
		if (strcmp(id, ((Semaforo *)temp_node->data)->id) == 0) {
			*sem_node = temp_node;
			return 1;
		}
		temp_node = temp_node->next;
	}

	return 0;
}

/* Função teste para imprimir lista */
void print_semaforo(ListaGenerica *lista_semaforo) {
	ListaGenerica *sem_head = lista_semaforo;

	while (sem_head != NULL) {
		printf("\n|%s|", ((Semaforo *)sem_head->data)->id);
		printf("\n|%s|", ((Semaforo *)sem_head->data)->cor1);
		printf("\n|%s|", ((Semaforo *)sem_head->data)->cor2);
		printf("|%.2f|", ((Semaforo *)sem_head->data)->x);
		printf("|%.2f|", ((Semaforo *)sem_head->data)->y);
		printf("|%.2f|", ((Semaforo *)sem_head->data)->width);
		printf("|%.2f|", ((Semaforo *)sem_head->data)->height);
		sem_head = sem_head->next;
	}
}
