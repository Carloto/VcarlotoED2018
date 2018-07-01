#include "misc.h"

/* Imprime uma string não nula */
void print_this(char *output) {
	if (output != NULL) {
		printf("\n|%s|", output);
	}
}

/* Libera a string caso não seja nula, e aponta o ponteiro restante para NULL*/
void free_string(char **temp_free) {
	if (*temp_free != NULL) {
		free(*temp_free);
	}
	*temp_free = NULL;
}

/* Atualiza o valor do limite */
int update_lim(char *input_line) {
	char *token;
	int ret;

	token = strtok(input_line, " ");
	token = strtok(NULL, " ");
	ret   = atoi(token);

	return ret;
}

/* Inicializa a struct de cores */
Cores *create_colors() {
	Cores* temp_colors  = (Cores *)calloc(1, sizeof(Cores));
	temp_colors->quad_stroke = NULL;
	temp_colors->quad_fill = NULL;
	temp_colors->hid_stroke = NULL;
	temp_colors->hid_fill = NULL;
	temp_colors->tor_stroke = NULL;
	temp_colors->tor_fill = NULL;
	temp_colors->sem_stroke = NULL;
	temp_colors->sem_fill = NULL;
	return temp_colors;
}

/* Destroi a struct de cores */
void destruir_colors(Cores *dc_kill) {
	free_string(&(dc_kill->quad_stroke));
	free_string(&(dc_kill->quad_fill));
	free_string(&(dc_kill->hid_stroke));
	free_string(&(dc_kill->hid_fill));
	free_string(&(dc_kill->tor_stroke));
	free_string(&(dc_kill->tor_fill));
	free_string(&(dc_kill->sem_stroke));
	free_string(&(dc_kill->sem_fill));
	free(dc_kill);
}

/* Atualiza as cores de preenchimento e borda*/
Cores *get_colors(char *input_line, Cores* temp_colors) {

	char   *token = NULL;

	switch (input_line[1]) {

	case 'q':
		token = strtok(input_line, " ");

		token      = strtok(NULL, " ");
		free_string(&(temp_colors->quad_stroke));
		temp_colors->quad_stroke = (char *)calloc(strlen(token) + 1, sizeof(char));
		strcpy(temp_colors->quad_stroke, token);
		printf("\n%s", temp_colors->quad_stroke);

		token      = strtok(NULL, " ");
		free_string(&(temp_colors->quad_fill));
		temp_colors->quad_fill = (char *)calloc(strlen(token) + 1, sizeof(char));
		strcpy(temp_colors->quad_fill, token);
		printf("\n%s", temp_colors->quad_fill);
		break;

	case 'h':
		token = strtok(input_line, " ");

		token      = strtok(NULL, " ");
		free_string(&(temp_colors->hid_stroke));
		temp_colors->hid_stroke = (char *)calloc(strlen(token) + 1, sizeof(char));
		strcpy(temp_colors->hid_stroke, token);
		printf("\n%s", temp_colors->hid_stroke);

		token      = strtok(NULL, " ");
		free_string(&(temp_colors->hid_fill));
		temp_colors->hid_fill = (char *)calloc(strlen(token) + 1, sizeof(char));
		strcpy(temp_colors->hid_fill, token);
		printf("\n%s", temp_colors->hid_fill);
		break;

	case 't':
		token = strtok(input_line, " ");

		token      = strtok(NULL, " ");
		free_string(&(temp_colors->tor_stroke));
		temp_colors->tor_stroke = (char *)calloc(strlen(token) + 1, sizeof(char));
		strcpy(temp_colors->tor_stroke, token);
		printf("\n%s", temp_colors->tor_stroke);

		token      = strtok(NULL, " ");
		free_string(&(temp_colors->tor_fill));
		temp_colors->tor_fill = (char *)calloc(strlen(token) + 1, sizeof(char));
		strcpy(temp_colors->tor_fill, token);
		printf("\n%s", temp_colors->tor_fill);
		break;

	case 's':
		token = strtok(input_line, " ");

		token      = strtok(NULL, " ");
		free_string(&(temp_colors->sem_stroke));
		temp_colors->sem_stroke = (char *)calloc(strlen(token) + 1, sizeof(char));
		strcpy(temp_colors->sem_stroke, token);
		printf("\n%s", temp_colors->sem_stroke);

		token      = strtok(NULL, " ");
		free_string(&(temp_colors->sem_fill));
		temp_colors->sem_fill = (char *)calloc(strlen(token) + 1, sizeof(char));
		strcpy(temp_colors->sem_fill, token);
		printf("\n%s", temp_colors->sem_fill);
		break;

	default:
		break;

	}

	return temp_colors;

}
