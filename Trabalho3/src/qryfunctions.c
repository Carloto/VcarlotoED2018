#include "qryfunctions.h"

/* Muda a cor de uma figura dado um id/cep */
void change_color(FILE** OutputFile, ListaGenerica *Hidrantes, ListaGenerica *Torres, ListaGenerica *Semaforos, ListaGenerica *Quadras, char *input_line) {

	int hidrante_check = 0;
	int torre_check = 0;
	int semaforo_check = 0;
	int quadra_check = 0;
	char *token = 0;
	ListaGenerica *temp_node = NULL;

	token  = strtok(input_line, " ");
	token  = strtok(NULL, " ");
	print_this(token);

	hidrante_check = find_id_hidrante(&temp_node, Hidrantes, token);
	if (hidrante_check == 1) {
		free_string(&((Hidrante *)temp_node->data)->cor1);
		token = strtok(NULL, " ");
		((Hidrante *)temp_node->data)->cor1 = (char *)calloc(strlen(token) + 1, sizeof(char));
		strcpy(((Hidrante *)temp_node->data)->cor1, token);
		free_string(&((Hidrante *)temp_node->data)->cor2);
		token = strtok(NULL, " ");
		((Hidrante *)temp_node->data)->cor2 = (char *)calloc(strlen(token) + 1, sizeof(char));
		strcpy(((Hidrante *)temp_node->data)->cor2, token);
		return;
	}

	torre_check = find_id_torre(&temp_node, Torres, token);
	if (torre_check == 1) {
		free_string(&((Torre *)temp_node->data)->cor1);
		token = strtok(NULL, " ");
		((Torre *)temp_node->data)->cor1 = (char *)calloc(strlen(token) + 1, sizeof(char));
		strcpy(((Torre *)temp_node->data)->cor1, token);
		free_string(&((Torre *)temp_node->data)->cor2);
		token = strtok(NULL, " ");
		((Torre *)temp_node->data)->cor2 = (char *)calloc(strlen(token) + 1, sizeof(char));
		strcpy(((Torre *)temp_node->data)->cor2, token);
		return;
	}

	semaforo_check = find_id_semaforo(&temp_node, Semaforos, token);
	if (semaforo_check == 1) {
		free_string(&((Semaforo *)temp_node->data)->cor1);
		token = strtok(NULL, " ");
		((Semaforo *)temp_node->data)->cor1 = (char *)calloc(strlen(token) + 1, sizeof(char));
		strcpy(((Semaforo *)temp_node->data)->cor1, token);
		free_string(&((Semaforo *)temp_node->data)->cor2);
		token = strtok(NULL, " ");
		((Semaforo *)temp_node->data)->cor2 = (char *)calloc(strlen(token) + 1, sizeof(char));
		strcpy(((Semaforo *)temp_node->data)->cor2, token);
		return;
	}

	quadra_check = find_id_quadra(&temp_node, Quadras, token);
	if (quadra_check == 1) {
		free_string(&((Quadra *)temp_node->data)->cor1);
		token = strtok(NULL, " ");
		((Quadra *)temp_node->data)->cor1 = (char *)calloc(strlen(token) + 1, sizeof(char));
		strcpy(((Quadra *)temp_node->data)->cor1, token);
		free_string(&((Quadra *)temp_node->data)->cor2);
		token = strtok(NULL, " ");
		((Quadra *)temp_node->data)->cor2 = (char *)calloc(strlen(token) + 1, sizeof(char));
		strcpy(((Quadra *)temp_node->data)->cor2, token);
		rtquad_svg(OutputFile, temp_node);
		return;
	}

}

/* Executa o comando q? */
void interno_retangulo(FILE **OutputFile, ListaGenerica *Hidrantes, ListaGenerica *Torres, ListaGenerica *Semaforos, ListaGenerica *Quadras, char *input_line) {

	char *token;
	float x = 0;
	float y = 0;
	float width = 0;
	float height = 0;
	/*long size = 0;*/

	token = strtok(input_line, " ");
	token = strtok(NULL, " ");
	x = atof(token);
	token = strtok(NULL, " ");
	y = atof(token);
	token = strtok(NULL, " ");
	width = atof(token);
	token = strtok(NULL, " ");
	height = atof(token);

/*	size = ftell (*OutputFile);*/
	vazado_svg(OutputFile, x, y, width, height);
/*	fseek (*OutputFile, size, SEEK_SET);*/

}
