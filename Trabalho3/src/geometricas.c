#include "geometricas.h"

/*##################################
############  Circulos  ############
##################################*/

/* Função teste para imprimir lista */
void print_circle(Circle *temp_circ) {
	Circle *head_temp = temp_circ;

	while (head_temp != NULL) {
		printf("\n|%d|", head_temp->id);
		printf("|%s|",   head_temp->cor1);
		printf("|%s|",   head_temp->cor2);
		printf("|%.2f|", head_temp->raio);
		printf("|%.2f|", head_temp->x);
		printf("|%.2f|", head_temp->y);
		head_temp = head_temp->next;
	}
}

/* Aloca espaço para um nó */
Circle* create_cnode(Circle *temp_struct) {
	temp_struct       = (Circle *)calloc(1, sizeof(Circle));
	temp_struct->cor1 = NULL;
	temp_struct->cor2 = NULL;
	return temp_struct;
}

/* Free na struct e seus elementos */
void free_cstruct(Circle *temp_struct) {
	Circle *temp_free;

	while (temp_struct != NULL) {
		temp_free   = temp_struct;
		temp_struct = temp_struct->next;
		free_string(&(temp_free->cor1));
		free_string(&(temp_free->cor2));
		free(temp_free);
	}
}

/* Adiciona um nó na lista de circulos */
void new_cnode(Circle **temp_struct, Circle **temp_end, char *input_line) {
	Circle *Node  = NULL;
	char   *token = NULL;

	Node  = create_cnode(Node);
	token = strtok(input_line, " ");

	token    = strtok(NULL, " ");
	Node->id = atoi(token);

	token      = strtok(NULL, " ");
	Node->cor1 = (char *)calloc(strlen(token) + 1, sizeof(char));
	strcpy(Node->cor1, token);

	token      = strtok(NULL, " ");
	Node->cor2 = (char *)calloc(strlen(token) + 1, sizeof(char));
	strcpy(Node->cor2, token);

	token      = strtok(NULL, " ");
	Node->raio = atof(token);

	token   = strtok(NULL, " ");
	Node->x = atof(token);

	token   = strtok(NULL, " ");
	Node->y = atof(token);

	if (*temp_struct == NULL) {
		*temp_struct      = Node;
		*temp_end         = *temp_struct;
		(*temp_end)->next = NULL;
	} else {
		(*temp_end)->next = Node;
		(*temp_end)       = (*temp_end)->next;
		(*temp_end)->next = NULL;
	}
}

/* Adiciona um nó na lista de circulos dash */
void new_dash_node(Circle **temp_struct, Circle **temp_end, float x, float y, float raio) {
	Circle *Node  = NULL;

	Node  = create_cnode(Node);
	Node->id = 0;
	Node->raio = raio;
	Node->x = x;
	Node->y = y;

	if (*temp_struct == NULL) {
		*temp_struct      = Node;
		*temp_end         = *temp_struct;
		(*temp_end)->next = NULL;
	} else {
		(*temp_end)->next = Node;
		(*temp_end)       = (*temp_end)->next;
		(*temp_end)->next = NULL;
	}
}

/* Encontra a figura dado um id */
int find_id_circle(Circle **cnode, Circle *Circulos, int id) {
	Circle *temp_node = Circulos;

	while (temp_node != NULL) {
		if (temp_node->id == id) {
			*cnode = temp_node;
			return 1;
		}
		temp_node = temp_node->next;
	}

	return 0;
}

/*##################################
###########  Retangulos  ###########
##################################*/

/* Função teste para imprimir lista */
void print_rect(Rectangle *temp_circ) {
	Rectangle *head_temp = temp_circ;

	while (head_temp != NULL) {
		printf("\n|%d|", head_temp->id);
		printf("|%s|",   head_temp->cor1);
		printf("|%s|",   head_temp->cor2);
		printf("|%.2f|", head_temp->width);
		printf("|%.2f|", head_temp->height);
		printf("|%.2f|", head_temp->x);
		printf("|%.2f|", head_temp->y);
		head_temp = head_temp->next;
	}
}

/* Aloca espaço para um nó */
Rectangle* create_rnode(Rectangle *temp_struct) {
	temp_struct       = (Rectangle *)calloc(1, sizeof(Rectangle));
	temp_struct->cor1 = NULL;
	temp_struct->cor2 = NULL;
	return temp_struct;
}

/* Imprimir as figuras */
void print_geometricas(FILE **OutputFile, Circle *Circulos,
                       Rectangle *Retangulos) {
	Circle *temp_chead = Circulos;

	while (temp_chead != NULL) {
		rtprint_svg(OutputFile, temp_chead, NULL);
		temp_chead = temp_chead->next;
	}

	Rectangle *temp_rhead = Retangulos;

	while (temp_rhead != NULL) {
		rtprint_svg(OutputFile, NULL, temp_rhead);
		temp_rhead = temp_rhead->next;
	}
}

/* Imprime a figura geometrica no arquivo de saida */
void rtprint_svg(FILE **OutputFile, Circle *rs_circ, Rectangle *rs_rect) {
	/* Imprimir Circulo */
	if (rs_rect == NULL) {
		fprintf(*OutputFile,
		        "\t<circle cx=\"%f\" cy=\"%f\" r=\"%f\" ",
		        rs_circ->x,
		        rs_circ->y,
		        rs_circ->raio);
		fprintf(*OutputFile,
		        "stroke=\"%s\" fill=\"%s\"/>\n",
		        rs_circ->cor1,
		        rs_circ->cor2);
	} else

	/* Imprimir retangulo */
	if (rs_circ == NULL) {
		fprintf(*OutputFile,
		        "\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" ",
		        rs_rect->x,
		        rs_rect->y,
		        rs_rect->width,
		        rs_rect->height);
		fprintf(*OutputFile,
		        "stroke=\"%s\" fill=\"%s\"/>\n",
		        rs_rect->cor1,
		        rs_rect->cor2);
	}
}

/* Free na struct e seus elementos */
void free_rstruct(Rectangle *temp_struct) {
	Rectangle *temp_free;

	while (temp_struct != NULL) {
		temp_free   = temp_struct;
		temp_struct = temp_struct->next;
		free_string(&(temp_free->cor1));
		free_string(&(temp_free->cor2));
		free(temp_free);
	}
}

/* Adiciona um nó na lista de circulos */
void new_rnode(Rectangle **temp_struct, Rectangle **temp_end, char *input_line) {
	Rectangle *Node = NULL;
	char *token     = NULL;

	Node  = create_rnode(Node);
	token = strtok(input_line, " ");

	token    = strtok(NULL, " ");
	Node->id = atoi(token);

	token      = strtok(NULL, " ");
	Node->cor1 = (char *)calloc(strlen(token) + 1, sizeof(char));
	strcpy(Node->cor1, token);

	token      = strtok(NULL, " ");
	Node->cor2 = (char *)calloc(strlen(token) + 1, sizeof(char));
	strcpy(Node->cor2, token);

	token       = strtok(NULL, " ");
	Node->width = atof(token);

	token        = strtok(NULL, " ");
	Node->height = atof(token);

	token   = strtok(NULL, " ");
	Node->x = atof(token);

	token   = strtok(NULL, " ");
	Node->y = atof(token);


	if (*temp_struct == NULL) {
		*temp_struct      = Node;
		*temp_end         = *temp_struct;
		(*temp_end)->next = NULL;
	} else {
		(*temp_end)->next = Node;
		(*temp_end)       = (*temp_end)->next;
		(*temp_end)->next = NULL;
	}

	/*(Node->next = (*temp_struct);
	   (*temp_struct) = Node;*/
}

/* Encontra a figura dado um id */
int find_id_rect(Rectangle **rnode, Rectangle *Retangulos, int id) {
	Rectangle *temp_node = Retangulos;

	while (temp_node != NULL) {
		if (temp_node->id == id) {
			*rnode = temp_node;
			return 2;
		}
		temp_node = temp_node->next;
	}

	return -1;
}
