#include "quadra.h"


/* Adiciona uma nova quadra */
void new_quadra(ListaGenerica **quad_head,
                ListaGenerica **quad_end,
                char           *input_line,
                Cores          *colors) {
	char *token = NULL;

	/* Cria um novo no na lista */
	ListaGenerica *new_node = (ListaGenerica *)calloc(1, sizeof(ListaGenerica));

	/* Inicializa a struct quadra */
	Quadra *temp_quad = (Quadra *)calloc(1, sizeof(Quadra));

	temp_quad->cep = NULL;

	token = strtok(input_line, " ");

	token          = strtok(NULL, " ");
	temp_quad->cep = (char *)calloc(strlen(token) + 1, sizeof(char));
	strcpy(temp_quad->cep, token);

	token        = strtok(NULL, " ");
	temp_quad->x = atof(token);

	token        = strtok(NULL, " ");
	temp_quad->y = atof(token);

	token            = strtok(NULL, " ");
	temp_quad->width = atof(token);

	token             = strtok(NULL, " ");
	temp_quad->height = atof(token);

	temp_quad->cor1 = (char *)calloc(strlen(colors->quad_stroke) + 1, sizeof(char));
	strcpy(temp_quad->cor1, colors->quad_stroke);

	temp_quad->cor2 = (char *)calloc(strlen(colors->quad_fill) + 1, sizeof(char));
	strcpy(temp_quad->cor2, colors->quad_fill);

	new_node->data = temp_quad;

	if (*quad_head == NULL) {
		(*quad_head)      = new_node;
		*quad_end         = *quad_head;
		(*quad_end)->next = NULL;
	} else {
		(*quad_end)->next = new_node;
		(*quad_end)       = (*quad_end)->next;
		(*quad_end)->next = NULL;
	}

	/*printf("\n%s", ((Quadra *)(*quad_end)->data)->cep);*/
}

/* Free na struct e seus elementos */
void free_quadra(ListaGenerica *temp_struct) {
	ListaGenerica *aux;

	while (temp_struct != NULL) {
		aux         = temp_struct;
		temp_struct = temp_struct->next;
		free_string(&(((Quadra *)aux->data)->cep));
		free_string(&(((Quadra *)aux->data)->cor1));
		free_string(&(((Quadra *)aux->data)->cor2));
		free(aux->data);
		free(aux);
	}
}

/* Imprimir a ultima quadra lida no svg */
void rtquad_svg(FILE **OutputFile, ListaGenerica *QuadFim) {
	float x;
	float y;

	fprintf(*OutputFile,
	        "\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" ",
	        ((Quadra *)QuadFim->data)->x,
	        ((Quadra *)QuadFim->data)->y,
	        ((Quadra *)QuadFim->data)->width,
	        ((Quadra *)QuadFim->data)->height);

	fprintf(*OutputFile,
	        "stroke=\"%s\" fill=\"%s\" style=\"stroke-width: 3;\" />\n",
	        ((Quadra *)QuadFim->data)->cor1,
	        ((Quadra *)QuadFim->data)->cor2);

	x = (((Quadra *)QuadFim->data)->width / 2) + ((Quadra *)QuadFim->data)->x;
	y = (((Quadra *)QuadFim->data)->height / 2) + ((Quadra *)QuadFim->data)->y;

	fprintf(*OutputFile,
	        "\t<text x=\"%f\" y=\"%f\" fill=\"white\" stroke=\"black\" text-anchor=\"middle\" alignment-baseline=\"central\" style=\"stroke-width: 0.5;\" >%s</text>\n",
	        x,
	        y,
	        ((Quadra *)QuadFim->data)->cep);
}

/* Imprimir toda a lista de quadras na saida svg */
void pquad_svg(FILE **OutputFile, ListaGenerica *lista_quadra) {
	ListaGenerica *quad_head = lista_quadra;

	while (quad_head != NULL) {
		rtquad_svg(OutputFile, quad_head);
		quad_head = quad_head->next;
	}
}

/* Encontra a figura dado um id */
int find_id_quadra(ListaGenerica **quad_node, ListaGenerica *Quadras, char *id) {
	ListaGenerica *temp_node = Quadras;

	while (temp_node != NULL) {
		if (strcmp(id, ((Quadra *)temp_node->data)->cep) == 0) {
			*quad_node = temp_node;
			return 1;
		}
		temp_node = temp_node->next;
	}

	return 0;
}

/* Função teste para imprimir lista */
void print_quadra(ListaGenerica *lista_quadra) {
	ListaGenerica *quad_head = lista_quadra;

	while (quad_head != NULL) {
		printf("\n|%s|", ((Quadra *)quad_head->data)->cep);
		printf("\n|%s|", ((Quadra *)quad_head->data)->cor1);
		printf("\n|%s|", ((Quadra *)quad_head->data)->cor2);
		printf("|%.2f|", ((Quadra *)quad_head->data)->x);
		printf("|%.2f|", ((Quadra *)quad_head->data)->y);
		printf("|%.2f|", ((Quadra *)quad_head->data)->width);
		printf("|%.2f|", ((Quadra *)quad_head->data)->height);
		quad_head = quad_head->next;
	}
}
