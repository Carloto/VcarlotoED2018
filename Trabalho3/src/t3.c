/* Vinicius Carloto Carnelocce */

/* 201600560546 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "arquivo.h"
#include "geometricas.h"
#include "functions.h"
#include "quadra.h"
#include "semaforo.h"
#include "hidrante.h"
#include "torre.h"
#include "qryfunctions.h"

/* Função main para execução da leitura dos arquivos */
int main(int argc, char *argv[]) {
  /* Declarar variaveis */

  /* Variaveis */
  int   limite       = 1000;
  int   controle     = 1;
  int   count_lim    = 0;
  float distancia    = 0;
  char *input_line   = NULL;
  char *resposta     = NULL;
  char *qry_svg_name = NULL;

  /* Arquivos */
  Arqs *MainPaths    = criar_arqs();
  FILE *GeoInput     = NULL;
  FILE *QryInput     = NULL;
  FILE *OutputSvgStd = NULL;
  FILE *OutputTxtStd = NULL;
  FILE *OutputSvgQry = NULL;

  /* Figuras */
  Circle *Circulos      = NULL;
  Circle *CircFim       = NULL;
  Rectangle *Retangulos = NULL;
  Rectangle *RetFim     = NULL;

  /* Cores */
  Cores *MainColors = create_colors();

  /* Quadras */
  ListaGenerica *Quadras = NULL;
  ListaGenerica *QuadFim = NULL;

  /* Semaforos */
  ListaGenerica *Semaforos = NULL;
  ListaGenerica *SemFim    = NULL;

  /* Hidrantes */
  ListaGenerica *Hidrantes = NULL;
  ListaGenerica *HidFim    = NULL;

  /* Torre */
  ListaGenerica *Torres = NULL;
  ListaGenerica *TorFim = NULL;

  /* Inicializar variaveis */
  MainPaths = ler_argv(argc, argv, MainPaths);

  /*print_arqs(MainPaths);*/

  GeoInput = fopen(MainPaths->input_path, "r");

  if (!GeoInput) {
    printf("\n Erro! Arquivo .geo não encontrado! \n");
    destruir_arqs(MainPaths);
    return -1;
  }

  OutputSvgStd = cria_svg(OutputSvgStd, MainPaths, MainPaths->input_name);
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

      /*rtquad_svg(&OutputSvgStd, QuadFim);*/
      break;

    case 's':
      new_semaforo(&Semaforos, &SemFim, input_line, MainColors);

      /*rtsem_svg(&OutputSvgStd, SemFim);*/
      break;

    case 'h':
      new_hidrante(&Hidrantes, &HidFim, input_line, MainColors);

      /*rthid_svg(&OutputSvgStd, HidFim);*/
      break;

    case 't':
      new_torre(&Torres, &TorFim, input_line, MainColors);

      /*rttor_svg(&OutputSvgStd, TorFim);*/
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
      rtprint_txt(&OutputTxtStd, NULL, input_line, -1);
      distancia = dist(Circulos, Retangulos, input_line);
      rtprint_txt(&OutputTxtStd, NULL, NULL,       distancia);
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

  controle = 0;

  /*print_circle(Circulos);*/
  /*print_rect(Retangulos);*/
  /*print_quadra(Quadras);*/
  /*print_semaforo(Semaforos);*/
  /*print_hidrante(Hidrantes);*/

  pquad_svg(&OutputSvgStd, Quadras);
  phid_svg(&OutputSvgStd, Hidrantes);
  ptor_svg(&OutputSvgStd, Torres);
  psem_svg(&OutputSvgStd, Semaforos);

  /* Liberar variaveis */
  destroi_svg(&OutputSvgStd);

  /* Verificar se existe arquivo qry */
  if (MainPaths->input_qry != NULL) {
    QryInput = fopen(MainPaths->input_qry, "r");

    if (!QryInput) {
      printf("\n Erro! Arquivo .qry não encontrado! \n");
    } else {
      controle = 1;
    }
  }

  /* Imprimir as figuras no svg do qry */
  if (controle == 1) {
    MainPaths->input_qry = cut_name(MainPaths->input_qry);
    qry_svg_name         =
      concat_file(MainPaths->input_name, MainPaths->input_qry);
    OutputSvgQry = cria_svg(OutputSvgQry, MainPaths, qry_svg_name);
    print_geometricas(&OutputSvgQry, Circulos, Retangulos);
  }

  /* Loop de leitura qry */
  while (controle) {
    get_linha(input_line, QryInput);

    if (feof(QryInput)) {
      break;
    }

    print_this(input_line);

    switch (input_line[0]) {
    case 'c':

      switch (input_line[1]) {
      case 'c':
        change_color(&OutputSvgQry,
                     Hidrantes,
                     Torres,
                     Semaforos,
                     Quadras,
                     input_line);
        break;
      }

      break;

    case 'q':
      rtprint_txt(&OutputTxtStd, NULL, input_line, -1);
      interno_retangulo(&OutputSvgQry,
                        &OutputTxtStd,
                        Hidrantes,
                        Torres,
                        Semaforos,
                        Quadras,
                        input_line);
      break;

    case 'Q':
      rtprint_txt(&OutputTxtStd, NULL, input_line, -1);
      interno_circulo(&OutputSvgQry,
                      &OutputTxtStd,
                      Hidrantes,
                      Torres,
                      Semaforos,
                      Quadras,
                      input_line);
      break;

    case 'd':
    case 'D':
      rtprint_txt(&OutputTxtStd, NULL, input_line, -1);

      /*switch () {
              :
         }*/
      kill_inside(&OutputSvgQry,
                  &OutputTxtStd,
                  Hidrantes,
                  Torres,
                  Semaforos,
                  &Quadras,
                  input_line);
      break;

    default:
      break;
    }
  }


  /* Fechar o arquivo svg do qry */
  if (controle == 1) {
    pquad_svg(&OutputSvgQry, Quadras);
    phid_svg(&OutputSvgQry, Hidrantes);
    ptor_svg(&OutputSvgQry, Torres);
    psem_svg(&OutputSvgQry, Semaforos);
    destroi_svg(&OutputSvgQry);
    fclose(QryInput);
  }


  /* Liberar variaveis */
  fclose(GeoInput);
  destroi_txt(&OutputTxtStd);
  destruir_arqs(MainPaths);
  free_cstruct(Circulos);
  free_rstruct(Retangulos);
  free_quadra(Quadras);
  free_semaforo(Semaforos);
  free_hidrante(Hidrantes);
  free_torre(Torres);
  destruir_colors(MainColors);
  free_string(&qry_svg_name);
  free_string(&resposta);
  free_string(&input_line);

  return 0;
}
