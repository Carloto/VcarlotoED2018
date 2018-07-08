#include "arquivo.h"

/* Lê uma linha do arquivo de entrada */
void get_linha(char *linha, FILE *entrada) {
	linha = fgets(linha, M_BUFFER, entrada);
	linha = strtok(linha, "\r\n");
}

/* Ler e separar parametros */
Arqs* ler_argv(int argc, char *argv[], Arqs *la_argv) {
	int i;
	int j = 1;
	int len;
	char *aux;

	/* Encontrar os parametros */
	for (i = 0; i < argc; i++) {
		if (strcmp("-e", argv[i]) == 0) {
			i++;
			len                 = strlen(argv[i]);
			la_argv->input_path = (char *)calloc(len + 1, sizeof(char));
			strcpy(la_argv->input_path, argv[i]);
		}

		if (strcmp("-f", argv[i]) == 0) {
			i++;
			len                 = strlen(argv[i]);
			la_argv->input_name = (char *)calloc(len + 1, sizeof(char));
			strcpy(la_argv->input_name, argv[i]);
		}

		if (strcmp("-o", argv[i]) == 0) {
			i++;
			len                  = strlen(argv[i]);
			la_argv->output_path = (char *)calloc(len + 1, sizeof(char));
			strcpy(la_argv->output_path, argv[i]);
		}

		if (strcmp("-q", argv[i]) == 0) {
			i++;
			len                = strlen(argv[i]);
			la_argv->input_qry = (char *)calloc(len + 1, sizeof(char));
			strcpy(la_argv->input_qry, argv[i]);
		}
	}

	/* Verificar a presença de "." no -q */
	if ((la_argv->input_path != NULL) && (la_argv->input_qry != NULL)) {
		if (la_argv->input_qry[0] == '.') {
			len = strlen(la_argv->input_qry);
			aux = (char *)calloc(len, sizeof(char));

			for (i = 1, j = 0; i < len; i++, j++) {
				aux[j] = la_argv->input_qry[i];
			}
			aux[len - 1] = '\0';
			free_string(&(la_argv->input_qry));
			la_argv->input_qry = (char *)calloc(len, sizeof(char));
			strcpy(la_argv->input_qry, aux);
			free_string(&aux);
		}
	}

	/* Verificar a presença de / no -e e -q */
	if ((la_argv->input_path != NULL) && (la_argv->input_qry != NULL)) {
		len = strlen(la_argv->input_path);

		if ((la_argv->input_path[len - 1] == '/') &&
		    (la_argv->input_qry[0] == '/')) {
			la_argv->input_path[len - 1] = '\0';
			aux                          = (char *)calloc(strlen(la_argv->input_qry) + 1, sizeof(char));
			strcpy(aux, la_argv->input_qry);
			free_string(&(la_argv->input_qry));
			la_argv->input_qry = (char *)calloc(len + strlen(aux),
			                                    sizeof(char));
			sprintf(la_argv->input_qry, "%s%s", la_argv->input_path, aux);
			free_string(&aux);
		} else

		if ((la_argv->input_path[len - 1] != '/') &&
		    (la_argv->input_qry[0] != '/')) {
			aux = (char *)calloc(strlen(la_argv->input_qry) + 1, sizeof(char));
			strcpy(aux, la_argv->input_qry);
			free_string(&(la_argv->input_qry));
			la_argv->input_qry = (char *)calloc(len + 2 + strlen(aux),
			                                    sizeof(char));
			sprintf(la_argv->input_qry, "%s/%s", la_argv->input_path, aux);
			free_string(&aux);
		} else {
			aux = (char *)calloc(strlen(la_argv->input_qry) + 1, sizeof(char));
			strcpy(aux, la_argv->input_qry);
			free_string(&(la_argv->input_qry));
			la_argv->input_qry = (char *)calloc(len + 1 + strlen(aux),
			                                    sizeof(char));
			sprintf(la_argv->input_qry, "%s%s", la_argv->input_path, aux);
			free_string(&aux);
		}
	}

	/* Verificar a presença de "." no -f */
	if (la_argv->input_path != NULL) {
		if (la_argv->input_name[0] == '.') {
			len = strlen(la_argv->input_name);
			aux = (char *)calloc(len, sizeof(char));

			for (i = 1, j = 0; i < len; i++, j++) {
				aux[j] = la_argv->input_name[i];
			}
			aux[len - 1] = '\0';
			free_string(&(la_argv->input_name));
			la_argv->input_name = (char *)calloc(len, sizeof(char));
			strcpy(la_argv->input_name, aux);
			free_string(&aux);
		}
	}

	/* Verificar a presença de / no -e e -f */
	if (la_argv->input_path != NULL) {
		len = strlen(la_argv->input_path);

		if ((la_argv->input_path[len - 1] == '/') &&
		    (la_argv->input_name[0] == '/')) {
			la_argv->input_path[len - 1] = '\0';
			aux                          = (char *)calloc(len, sizeof(char));
			strcpy(aux, la_argv->input_path);
			free_string(&(la_argv->input_path));
			la_argv->input_path = (char *)calloc(len + strlen(la_argv->input_name),
			                                     sizeof(char));
			sprintf(la_argv->input_path, "%s%s", aux, la_argv->input_name);
			free_string(&aux);
		} else

		if ((la_argv->input_path[len - 1] != '/') &&
		    (la_argv->input_name[0] != '/')) {
			aux = (char *)calloc(len + 1, sizeof(char));
			strcpy(aux, la_argv->input_path);
			free_string(&(la_argv->input_path));
			la_argv->input_path = (char *)calloc(len + 2 + strlen(la_argv->input_name),
			                                     sizeof(char));
			sprintf(la_argv->input_path, "%s/%s", aux, la_argv->input_name);
			free_string(&aux);
		} else {
			aux = (char *)calloc(len + 1, sizeof(char));
			strcpy(aux, la_argv->input_path);
			free_string(&(la_argv->input_path));
			la_argv->input_path = (char *)calloc(len + 1 + strlen(la_argv->input_name),
			                                     sizeof(char));
			sprintf(la_argv->input_path, "%s%s", aux, la_argv->input_name);
			free_string(&aux);
		}
	} else {
		la_argv->input_path =
			(char *)calloc(strlen(la_argv->input_name) + 1, sizeof(char));
		strcpy(la_argv->input_path, la_argv->input_name);
	}

	/* Isolar nome do arquivo */
	len = strlen(la_argv->input_name);

	for (i = len; i > -1; i--) {
		if (la_argv->input_name[i] == '/') {
			break;
		}
	}

	/* O loop chegou no final, logo, não há path */
	if (i == -1) {
		aux = (char *)calloc(len + 1, sizeof(char));
		i   = 0;

		for (j = 0; j < len - 4; j++, i++) {
			aux[j] = la_argv->input_name[i];
		}
		aux[len - 4] = '\0';
		free_string(&(la_argv->input_name));
		la_argv->input_name = (char *)calloc(len + 1, sizeof(char));
		strcpy(la_argv->input_name, aux);
		free_string(&aux);
	} else {
		/* O loop não chegou no final, logo, há path */
		len = len - i;
		aux = (char *)calloc(len + 1, sizeof(char));
		i++;

		for (j = 0; j < len - 5; j++, i++) {
			aux[j] = la_argv->input_name[i];
		}
		aux[len - 5] = '\0';
		free_string(&(la_argv->input_name));
		la_argv->input_name = (char *)calloc(len + 1, sizeof(char));
		strcpy(la_argv->input_name, aux);
		free_string(&aux);
	}

	return la_argv;
}

/* Inicializar Arqs */
Arqs* criar_arqs() {
	Arqs *ca_ret = (Arqs *)malloc(1 * sizeof(Arqs));

	ca_ret->input_path  = NULL;
	ca_ret->output_path = NULL;
	ca_ret->input_name  = NULL;
	ca_ret->input_qry   = NULL;
	return ca_ret;
}

/* Destruir Arqs */
void destruir_arqs(Arqs *da_kill) {
	free_string(&(da_kill->input_path));
	free_string(&(da_kill->output_path));
	free_string(&(da_kill->input_name));
	free_string(&(da_kill->input_qry));
	free(da_kill);
}

/* Imprimir Arqs */
void print_arqs(Arqs *pa_arq) {
	print_this(pa_arq->input_path);
	print_this(pa_arq->output_path);
	print_this(pa_arq->input_name);
	print_this(pa_arq->input_qry);
}

/* Inicializar arquivo svg */
FILE* cria_svg(FILE *OutputFile, Arqs *temp_arq, char *after) {
	char *file_name = NULL;
	int len;

	if (temp_arq->output_path != NULL) {
		len = strlen(temp_arq->output_path);

		if (temp_arq->output_path[len - 1] == '/') {
			len       = strlen(temp_arq->output_path) + strlen(after);
			file_name = (char *)calloc(len + 5, sizeof(char));
			sprintf(file_name, "%s%s.svg", temp_arq->output_path, after);
		} else {
			len       = strlen(temp_arq->output_path) + strlen(after);
			file_name = (char *)calloc(len + 6, sizeof(char));
			sprintf(file_name, "%s/%s.svg", temp_arq->output_path,
			        after);
		}
	} else {
		len       = strlen(after);
		file_name = (char *)calloc(len + 5, sizeof(char));
		sprintf(file_name, "%s.svg", after);
	}

	OutputFile = fopen(file_name, "w");
	fprintf(OutputFile, "<svg>\n");
	free_string(&file_name);
	return OutputFile;
}

/* Fechar arquivo svg */
void destroi_svg(FILE **OutputFile) {
	fprintf(*OutputFile, "</svg>");
	fclose(*OutputFile);
}

/* Imprime a sobreposição */
void sbprint_svg(float x,
                 float y,
                 float width,
                 float height,
                 char  *cor1,
                 FILE **OutputFile) {
	/* Imprimir retangulo */
	fprintf(*OutputFile,
	        "\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" \n",
	        x,
	        y,
	        width,
	        height);
	fprintf(*OutputFile,
	        "\t\tstyle=\"stroke: %s;\n\t\t\tstroke-dasharray: 10 5;\n\t\t\tfill: none;\n\t\t\"\n\t/>",
	        cor1);
	fprintf(*OutputFile,
	        "\t<text x=\"%f\" y=\"%f\" fill=\"%s\">Sobrepõe</text>\n",
	        x,
	        y - 3,
	        cor1);
}

/* Inicializar arquivo txt */
FILE* cria_txt(FILE *OutputFile, Arqs *temp_arq) {
	char *file_name = NULL;
	int len;

	if (temp_arq->output_path != NULL) {
		len = strlen(temp_arq->output_path);

		if (temp_arq->output_path[len - 1] == '/') {
			len       = strlen(temp_arq->output_path) + strlen(temp_arq->input_name);
			file_name = (char *)calloc(len + 5, sizeof(char));
			sprintf(file_name, "%s%s.txt", temp_arq->output_path, temp_arq->input_name);
		} else {
			len       = strlen(temp_arq->output_path) + strlen(temp_arq->input_name);
			file_name = (char *)calloc(len + 6, sizeof(char));
			sprintf(file_name, "%s/%s.txt", temp_arq->output_path,
			        temp_arq->input_name);
		}
	} else {
		len       = strlen(temp_arq->input_name);
		file_name = (char *)calloc(len + 5, sizeof(char));
		sprintf(file_name, "%s.txt", temp_arq->input_name);
	}

	/*print_this(file_name);*/
	OutputFile = fopen(file_name, "a");
	free_string(&file_name);
	return OutputFile;
}

/* Fechar arquivo txt */
void destroi_txt(FILE **OutputFile) {
	fclose(*OutputFile);
}

/* Imprimir figura traçejada */
void vazado_svg(FILE **OutputFile, float x, float y, float width, float height) {
	if (width > -1) {
		fprintf(*OutputFile,
		        "\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" \n",
		        x,
		        y,
		        width,
		        height);
		fprintf(*OutputFile,
		        "\t\tstyle=\"stroke: %s; stroke-dasharray: 10 5; stroke-width: 3; fill: none;\"\n\t/>",
		        "black");
	} else {
		fprintf(*OutputFile,
		        "\t<circle cx=\"%f\" cy=\"%f\" r=\"%f\" \n",
		        x,
		        y,
		        height);
		fprintf(*OutputFile,
		        "\t\tstyle=\"stroke: %s; stroke-dasharray: 10 5; stroke-width: 3; fill: none;\"\n\t/>",
		        "black");
	}
}

/* Imprime a linha de resposta no txt de saida */
void rtprint_txt(FILE **OutputFile, char *resposta, char *linha,
                 float distancia) {
	if ((resposta == NULL) && (distancia == -1)) {
		fprintf(*OutputFile, "%s\n", linha);
	} else
	if ((linha == NULL) && (distancia == -1)) {
		fprintf(*OutputFile, "%s\n", resposta);
	} else
	if ((linha == NULL) && (distancia > -1)) {
		fprintf(*OutputFile, "%.2f\n", distancia);
	} else
	if ((resposta == NULL) && (distancia == -2) && (linha != NULL)) {
		fprintf(*OutputFile, "%s ", linha);
	} else
	if (strcmp(linha, resposta) == 0) {
		fprintf(*OutputFile, "%f ", distancia);
	}
}
