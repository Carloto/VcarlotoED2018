/* Vinicius Carloto Carnelocce */

/* 201600560546 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "arquivo.h"
#include "geometricas.h"
#include "functions.h"
#include "quadra.h"

/* Função main para execução da leitura dos arquivos */
int main(int argc, char *argv[]) {

	/* Declarar variaveis */

	/* Variaveis */
	int limite        = 1000;
	int controle      = 1;
	int count_lim     = 0;
	float distancia     = 0;
	char   *input_line    = NULL;
	char   *resposta      = NULL;

	/* Arquivos */
	Arqs   *MainPaths     = criar_arqs();
	FILE   *GeoInput      = NULL;
	FILE   *OutputSvgStd  = NULL;
	FILE   *OutputTxtStd  = NULL;

	/* Figuras */
	Circle *Circulos      = NULL;
	Circle *CircFim       = NULL;
	Rectangle *Retangulos = NULL;
	Rectangle *RetFim     = NULL;

	/* Cores */
	Cores* MainColors = create_colors();

	/* Quadras */
	ListaGenerica *Quadras = NULL;
	ListaGenerica *QuadFim = NULL;

	/* Inicializar variaveis */
	MainPaths = ler_argv(argc, argv, MainPaths);

	/*print_arqs(MainPaths);*/

	GeoInput = fopen(MainPaths->input_path, "r");

	if (!GeoInput) {
		printf("\n Erro! Arquivo não encontrado! \n");
		destruir_arqs(MainPaths);
		return -1;
	}

	OutputSvgStd = cria_svg(OutputSvgStd, MainPaths);
	OutputTxtStd = cria_txt(OutputTxtStd, MainPaths);
	input_line   = (char *)calloc(M_BUFFER, sizeof(char));

	/* Loop de leitura */
	while (controle) {
		get_linha(input_line, GeoInput);

		/*	if (feof(GeoInput)) {
		                break;
		        }*/

		switch (input_line[0]) {
		case 'c':

			switch (input_line[1]) {

			case 'q':
			case 'h':
			case 's':
			case 't':

				MainColors = get_colors(input_line, MainColors);

				break;

			default:

				if (count_lim + 1 > limite) {
					printf("\n VOCE CHEGOU NO LIMITE");
					break;
				}
				count_lim++;

				/*printf("\n %s", input_line);*/
				new_cnode(&Circulos, &CircFim, input_line);
				rtprint_svg(&OutputSvgStd, CircFim, NULL);
				break;

			}
			break;

		case 'r':

			if (count_lim + 1 > limite) {
				printf("\n VOCE CHEGOU NO LIMITE");
				break;
			}
			count_lim++;

			/*printf("\n %s", input_line);*/
			new_rnode(&Retangulos, &RetFim, input_line);
			rtprint_svg(&OutputSvgStd, NULL, RetFim);
			break;

		case 'q':
			new_quadra(&Quadras, &QuadFim, input_line, MainColors);
			rtquad_svg(&OutputSvgStd, QuadFim);
			break;

		case 'o':
			rtprint_txt(&OutputTxtStd, NULL,     input_line, -1);
			resposta = sobrepoe(Circulos, Retangulos, input_line, &OutputSvgStd);
			rtprint_txt(&OutputTxtStd, resposta, NULL,       -1);
			free_string(&resposta);
			break;

		case 'i':
			rtprint_txt(&OutputTxtStd, NULL,     input_line, -1);
			resposta = pto_int(Circulos, Retangulos, input_line);
			rtprint_txt(&OutputTxtStd, resposta, NULL,       -1);
			free_string(&resposta);
			break;

		case 'd':
			rtprint_txt(&OutputTxtStd, NULL, input_line,  -1);
			distancia = dist(Circulos, Retangulos, input_line);
			rtprint_txt(&OutputTxtStd, NULL, NULL, distancia);
			distancia = -1;
			break;

		case 'a':
			cmd_a(Circulos, Retangulos, input_line, MainPaths);

		case 'n':

			if (input_line[1] == 'x') {
				limite = update_lim(input_line);
			}
			break;

		case '#':
			controle = 0;
			break;

		default:
			break;
		}
	}

	print_circle(Circulos);

	print_rect(Retangulos);

	print_quadra(Quadras);

	/* Liberar variaveis */
	fclose(GeoInput);
	destroi_svg(&OutputSvgStd);
	destroi_txt(&OutputTxtStd);
	destruir_arqs(MainPaths);
	free_cstruct(Circulos);
	free_rstruct(Retangulos);
	free_quadra(Quadras);
	destruir_colors(MainColors);
	free_string(&resposta);
	free_string(&input_line);

	return 0;
}
