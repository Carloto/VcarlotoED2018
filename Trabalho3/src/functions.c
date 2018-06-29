#include "functions.h"

/* Verifica a sobrepósição de figuras geometricas */
char *sobrepoe (Circle *Circulos, Rectangle *Retangulos, char *input_line, FILE **OutputFile) {

	int id1, id2, check1, check2, validate;
	float dist, x, y, width, height, distX, distY;
	float exp = 2;
	char *token = NULL;
	char *ret = NULL;
	Circle *cnode1 = NULL;
	Circle *cnode2 = NULL;
	Rectangle *rnode1 = NULL;
	Rectangle *rnode2 = NULL;

	check2 = 0;

	/* Separar os ids */
	token = strtok(input_line, " ");
	token = strtok(NULL, " ");
	id1 = atoi(token);
	token = strtok(NULL, " ");
	id2 = atoi(token);

	/* Encontrar as figuras */
	check1 = find_id_circle(&cnode1, Circulos, id1);
	if (check1 != 1) {
		check1 = find_id_rect(&rnode1, Retangulos,id1);
	}

	check2 = find_id_circle(&cnode2, Circulos, id2);
	if (check2 != 1) {
		check2 = find_id_rect(&rnode2, Retangulos, id2);
	}

	if (check1 == -1 || check2 == -1) {
		ret = (char*) calloc(5, sizeof(char));
		sprintf(ret, "NÃO");
		return ret;
	}

	if (check1 != 1 && check2 == 1) {
		cnode1 = cnode2;
		rnode2 = rnode1;
		check1 = 1;
		check2 = 0;
	}

	/* Entre dois circulos */
	if ((check1 == 1) && (check2 == 1)) {
		dist = sqrt(pow(cnode1->x - cnode2->x, exp) + pow(cnode1->y - cnode2->y, exp));
		dist = dist - cnode1->raio - cnode2->raio;

		if (dist < 0) {
			/* Pega x */
			if (cnode1->x - cnode1->raio <= cnode2->x - cnode1->raio) {
				x = cnode1->x - cnode1->raio - 1;
			} else {
				x = cnode2->x - cnode2->raio - 1;
			}

			/* Pega width */
			if ((cnode2->x + cnode2->raio) > (cnode1->x + cnode1->raio)) {
				width = cnode2->x - x + cnode2->raio + 1;
			} else {
				width = cnode1->x - x + cnode1->raio + 1;
			}

			/* Pega y */
			if (cnode1->y - cnode1->raio <= cnode2->y - cnode2->raio) {
				y = cnode1->y - cnode1->raio - 1;
			} else {
				y = cnode2->y - cnode2->raio - 1;
			}

			/* Pega height */
			if ((cnode2->y + cnode2->raio) > (cnode1->y + cnode1->raio)) {
				height = cnode2->y - y + cnode2->raio + 1;
			} else {
				height = cnode1->y - y + cnode1->raio + 1;
			}

			sbprint_svg(x, y, width, height, cnode1->cor1, OutputFile);
			ret = (char*) calloc(4,sizeof(char));
			sprintf(ret, "SIM");
			return ret;
		}
	} else

	/* Entre 2 retangulos */
	if ((check1 != 1) && (check2 != 1)) {
		if (rnode1->x < (rnode2->x + rnode2->width) && (rnode1->x + rnode1->width) > rnode2->x &&
		    rnode1->y < (rnode2->y + rnode2->height) && (rnode1->y + rnode1->height) > rnode2->y) {
			/* Pega x */
			if (rnode1->x <= rnode2->x) {
				x = rnode1->x - 1;
			} else {
				x = rnode2->x - 1;
			}

			/* Pega width */
			if ((rnode2->x + rnode2->width) > (rnode1->x + rnode1->width)) {
				width = rnode2->x - x + rnode2->width + 1;
			} else {
				width = rnode1->x - x + rnode1->width + 1;
			}

			/* Pega y */
			if (rnode1->y <= rnode2->y) {
				y = rnode1->y - 1;
			} else {
				y = rnode2->y - 1;
			}

			/* Pega height */
			if ((rnode2->y + rnode2->height) > (rnode1->y + rnode1->height)) {
				height = rnode2->y - y + rnode2->height + 1;
			} else {
				height = rnode1->y - y + rnode1->height + 1;
			}

			sbprint_svg(x, y, width, height, rnode1->cor1, OutputFile);
			ret = (char*) calloc(4,sizeof(char));
			sprintf(ret, "SIM");
			return ret;

		}
	} else

	/* 1 é circulo e 2 é retangulo */
	if ((check1 == 1) && (check2 != 1)) {

		distX = abs(cnode1->x - rnode2->x - rnode2->width/2);
		distY = abs(cnode1->y - rnode2->y - rnode2->height/2);

		validate = 0;

		if (distX < (rnode2->width/2 + cnode1->raio) && distY < (rnode2->height/2 + cnode1->raio)) {
			if (distX <= (rnode2->width/2) || distY <= (rnode2->height/2)) {
				validate = 1;
			} else {
				distX = distX - rnode2->width/2;
				distY = distY - rnode2->height/2;
				if (distX*distX + distY*distY <= ((cnode1->raio) * (cnode1->raio))) {
					validate = 1;
				}
			}
		}

		if (validate) {

			/* Pega x */
			if ((cnode1->x - cnode1->raio) <= rnode2->x) {
				x = cnode1->x - cnode1->raio - 1;
			} else {
				x = rnode2->x - 1;
			}

			/* Pega width */
			if ((rnode2->x + rnode2->width) > (cnode1->x + cnode1->raio)) {
				width = rnode2->x - x + rnode2->width + 1;
			} else {
				width = cnode1->x - x + cnode1->raio + 1;
			}

			/* Pega y */
			if ((cnode1->y - cnode1->raio) <= rnode2->y) {
				y = cnode1->y - cnode1->raio - 1;
			} else {
				y = rnode2->y - 1;
			}

			/* Pega height */
			if ((rnode2->y + rnode2->height) > (cnode1->y + cnode1->raio)) {
				height = rnode2->y - y + rnode2->height + 1;
			} else {
				height = cnode1->y - y + cnode1->raio + 1;
			}

			sbprint_svg(x, y, width, height, cnode1->cor1, OutputFile);
			ret = (char*) calloc(4,sizeof(char));
			sprintf(ret, "SIM");
			return ret;
		}
	}

	ret = (char*) calloc(5, sizeof(char));
	sprintf(ret, "NÃO");
	return ret;

}

/* Verifica se o ponto é intero à figura */
char *pto_int(Circle *Circulos, Rectangle *Retangulos, char *input_line) {

	int id, x, y, check1;
	float dist;
	float exp = 2;
	char *token = NULL;
	char *ret = NULL;
	Circle *cnode1 = NULL;
	Rectangle *rnode1 = NULL;

	/* Separar os ids */
	token = strtok(input_line, " ");
	token = strtok(NULL, " ");
	id = atoi(token);
	token = strtok(NULL, " ");
	x = atoi(token);
	token = strtok(NULL, " ");
	y = atoi(token);

	/* Encontrar a figura */
	check1 = find_id_circle(&cnode1, Circulos, id);
	if (check1 != 1) {
		find_id_rect(&rnode1, Retangulos,id);
	}

	if (check1 == -1) {
		ret = (char*) calloc(5, sizeof(char));
		sprintf(ret, "NÃO");
		return ret;
	}

	/* Circulo */
	if (check1 == 1) {
		dist = sqrt(pow(cnode1->x - x, exp) + pow(cnode1->y - y, exp));
		dist = dist - cnode1->raio;
		if (dist < 0) {
			ret = (char*) calloc(4,sizeof(char));
			sprintf(ret, "SIM");
			return ret;
		}
	} else

	/* retangulo */
	if (check1 != 1) {
		if (rnode1->x < x && (rnode1->x + rnode1->width) > x &&
		    rnode1->y < y && (rnode1->y + rnode1->height) > y) {
			ret = (char*) calloc(4,sizeof(char));
			sprintf(ret, "SIM");
			return ret;
		}
	}

	ret = (char*) calloc(5, sizeof(char));
	sprintf(ret, "NÃO");
	return ret;

}

/* Retorna a distancia entre 2 figuras */
float dist (Circle *Circulos, Rectangle *Retangulos, char *input_line) {

	int id1, id2, check1, check2;
	float dist = -1;
	float exp = 2;
	char *token = NULL;
	Circle *cnode1 = NULL;
	Circle *cnode2 = NULL;
	Rectangle *rnode1 = NULL;
	Rectangle *rnode2 = NULL;

	/* Separar os ids */
	token = strtok(input_line, " ");
	token = strtok(NULL, " ");
	id1 = atoi(token);
	token = strtok(NULL, " ");
	id2 = atoi(token);

	/* Encontrar as figuras */
	check1 = find_id_circle(&cnode1, Circulos, id1);
	if (check1 != 1) {
		check1 = find_id_rect(&rnode1, Retangulos,id1);
	}

	check2 = find_id_circle(&cnode2, Circulos, id2);
	if (check2 != 1) {
		check2 = find_id_rect(&rnode2, Retangulos, id2);
	}

	if (check1 == -1 || check2 == -1) {
		return dist;
	}

	if (check1 != 1 && check2 == 1) {
		cnode1 = cnode2;
		rnode2 = rnode1;
		check1 = 1;
		check2 = 0;
	}


	/* Entre dois circulos */
	if ((check1 == 1) && (check2 == 1)) {
		dist = sqrt(pow(cnode1->x - cnode2->x, exp) + pow(cnode1->y - cnode2->y, exp));
		return dist;
	} else

	/* Entre 2 retangulos */
	if ((check1 != 1) && (check2 != 1)) {
		dist = sqrt(pow((rnode1->x + rnode1->width/2) - (rnode2->x + rnode2->width/2), exp) +
		            pow((rnode1->y + rnode1->height/2) - (rnode2->y + rnode2->height/2), exp));
		return dist;
	} else

	/* 1 é circulo e 2 é retangulo */
	if ((check1 == 1) && (check2 != 1)) {
		dist = sqrt(pow((cnode1->x) - (rnode2->x + rnode2->width/2), exp) +
		            pow((cnode1->y) - (rnode2->y + rnode2->height/2), exp));
		return dist;
	}

	return dist;

}

/* Executa o comando a */
void cmd_a (Circle *Circulos, Rectangle *Retangulos, char *input_line, Arqs *Paths) {

	int id, check1, len;
	float dist = -1;
	float exp = 2;
	float x, y, tx, ty;
	char *token = NULL;
	char *file_name = NULL;
	char *sufixo = NULL;
	char cor[100];
	Circle *cnode1 = NULL;
	Circle *temp_chead = NULL;
	Rectangle *rnode1 = NULL;
	Rectangle *temp_rhead = NULL;
	FILE *OutputFile = NULL;

	/* Separar os ids */
	token = strtok(input_line, " ");
	token = strtok(NULL, " ");
	id = atoi(token);
	token = strtok(NULL, " ");
	len = strlen(token);
	sufixo = (char*) calloc(len + 1, sizeof(char));
	strcpy(sufixo, token);

	/* Criar nome e abrir arquivo */

	if (Paths->output_path != NULL) {
		len = len + strlen(Paths->output_path) + strlen(Paths->input_name);
		if (Paths->output_path[strlen(Paths->output_path)-1] == '/') {
			file_name = (char*) calloc(len+6, sizeof(char));
			sprintf(file_name, "%s%s-%s.svg", Paths->output_path, Paths->input_name, sufixo);
		} else {
			file_name = (char*) calloc(len+7, sizeof(char));
			sprintf(file_name, "%s/%s-%s.svg", Paths->output_path, Paths->input_name, sufixo);
		}
	} else {
		len = len + strlen(Paths->input_name);
		file_name = (char*) calloc(len+6, sizeof(char));
		sprintf(file_name, "%s-%s.svg", Paths->input_name, sufixo);
	}

	/*print_this(file_name);*/
	OutputFile = fopen(file_name, "w");
	free_string(&file_name);
	free_string(&sufixo);
	fprintf(OutputFile, "<svg>\n");

	/* Imprimir as figuras */

	temp_chead = Circulos;

	while (temp_chead != NULL) {
		rtprint_svg (&OutputFile, temp_chead, NULL);
		temp_chead = temp_chead->next;
	}

	temp_rhead = Retangulos;

	while (temp_rhead != NULL) {
		rtprint_svg (&OutputFile, NULL, temp_rhead);
		temp_rhead = temp_rhead->next;
	}

	/* Encontrar as figuras */
	check1 = find_id_circle(&cnode1, Circulos, id);
	if (check1 != 1) {
		find_id_rect(&rnode1, Retangulos,id);
		if (check1 == -1) {
			x = 0;
			y = 0;
		}
		x = rnode1->x + rnode1->width/2;
		y = rnode1->x + rnode1->height/2;
		strcpy(cor, rnode1->cor1);
	} else {
		x = cnode1->x;
		y = cnode1->y;
		strcpy(cor, cnode1->cor1);
	}

	temp_chead = Circulos;

	/* Traçar linha até os circulos */
	while (temp_chead != NULL) {
		dist = sqrt(pow(x - temp_chead->x, exp) + pow(y - temp_chead->y, exp));
		fprintf(OutputFile, "\t<line x1=\"%f\" y1=\"%f\" ", x, y);
		fprintf(OutputFile, "x2=\"%f\" y2=\"%f\" ", temp_chead->x, temp_chead->y);
		fprintf(OutputFile, "style=\"stroke:%s\" />", cor);
		tx = (x + temp_chead->x)/2;
		ty = (y + temp_chead->y)/2;
		fprintf(OutputFile, "\t<text x=\"%f\" y=\"%f\" fill=\"%s\">%f</text>\n", tx, ty, cor, dist);
		temp_chead = temp_chead->next;
	}

	temp_rhead = Retangulos;

	/* Traçar linha até os retangulos */
	while (temp_rhead != NULL) {
		dist = sqrt(pow(x - temp_rhead->x + temp_rhead->width/2, exp) + pow(y - temp_rhead->y + temp_rhead->height/2, exp));
		fprintf(OutputFile, "\t<line x1=\"%f\" y1=\"%f\" ", x, y);
		fprintf(OutputFile, "x2=\"%f\" y2=\"%f\" ", temp_rhead->x + temp_rhead->width/2, temp_rhead->y + temp_rhead->height/2);
		fprintf(OutputFile, "style=\"stroke:%s\" />", cor);
		tx = (x + temp_rhead->x + temp_rhead->width/2)/2;
		ty = (y + temp_rhead->y + temp_rhead->height/2)/2;
		fprintf(OutputFile, "\t<text x=\"%f\" y=\"%f\" fill=\"%s\">%f</text>\n", tx, ty, cor, dist);
		temp_rhead = temp_rhead->next;
	}

	fprintf(OutputFile, "</svg>");
	fclose(OutputFile);

}
