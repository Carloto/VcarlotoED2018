#include "torre.h"


/* Adiciona uma nova torre */
void new_torre(ListaGenerica **tor_head,
               ListaGenerica **tor_end,
               char           *input_line,
               Cores          *colors) {
  char *token = NULL;

  /* Cria um novo no na lista */
  ListaGenerica *new_node = (ListaGenerica *)calloc(1, sizeof(ListaGenerica));

  /* Inicializa a struct semaforo*/
  Torre *temp_tor = (Torre *)calloc(1, sizeof(Torre));

  temp_tor->id = NULL;

  token = strtok(input_line, " ");

  token        = strtok(NULL, " ");
  temp_tor->id = (char *)calloc(strlen(token) + 1, sizeof(char));
  strcpy(temp_tor->id, token);

  token       = strtok(NULL, " ");
  temp_tor->x = atof(token);

  token       = strtok(NULL, " ");
  temp_tor->y = atof(token);

  temp_tor->raio = 8;

  temp_tor->cor1 = (char *)calloc(strlen(colors->tor_stroke) + 1, sizeof(char));
  strcpy(temp_tor->cor1, colors->tor_stroke);

  temp_tor->cor2 = (char *)calloc(strlen(colors->tor_fill) + 1, sizeof(char));
  strcpy(temp_tor->cor2, colors->tor_fill);

  new_node->data = temp_tor;

  if (*tor_head == NULL) {
    (*tor_head)      = new_node;
    *tor_end         = *tor_head;
    (*tor_end)->next = NULL;
  } else {
    (*tor_end)->next = new_node;
    (*tor_end)       = (*tor_end)->next;
    (*tor_end)->next = NULL;
  }

  /*printf("\n%s", ((Torre *)(*quad_end)->data)->cep);*/
}

/* Free na struct e seus elementos */
void free_torre(ListaGenerica *temp_struct) {
  ListaGenerica *aux;

  while (temp_struct != NULL) {
    aux         = temp_struct;
    temp_struct = temp_struct->next;
    free_string(&(((Torre *)aux->data)->id));
    free_string(&(((Torre *)aux->data)->cor1));
    free_string(&(((Torre *)aux->data)->cor2));
    free(aux->data);
    free(aux);
  }
}

/* Imprimir a ultima torre lida no svg */
void rttor_svg(FILE **OutputFile, ListaGenerica *TorFim) {
  float x;
  float y;

  fprintf(*OutputFile,
          "\t<circle cx=\"%f\" cy=\"%f\" r=\"%f\" ",
          ((Torre *)TorFim->data)->x,
          ((Torre *)TorFim->data)->y,
          ((Torre *)TorFim->data)->raio);

  fprintf(*OutputFile,
          "stroke=\"%s\" fill=\"%s\" style=\"stroke-width: 3\" fill-opacity=\"0.7\" stroke-opacity=\"0.7\" />\n",
          ((Torre *)TorFim->data)->cor1,
          ((Torre *)TorFim->data)->cor2);

  x = ((Torre *)TorFim->data)->x;
  y = ((Torre *)TorFim->data)->y + ((Torre *)TorFim->data)->raio / 2;

  fprintf(*OutputFile,
          "\t<text x=\"%f\" y=\"%f\" fill=\"white\" stroke=\"black\" text-anchor=\"middle\" alignment-baseline=\"central\" style=\"stroke-width: 0.5\" fill-opacity=\"0.7\" stroke-opacity=\"0.7\" >%s</text>\n",
          x,
          y,
          "T");
}

/* Imprimir toda a lista de torres na saida svg */
void ptor_svg(FILE **OutputFile, ListaGenerica *lista_torre) {
  ListaGenerica *tor_head = lista_torre;

  while (tor_head != NULL) {
    rttor_svg(OutputFile, tor_head);
    tor_head = tor_head->next;
  }
}

/* Função teste para imprimir lista */
void print_torre(ListaGenerica *lista_torre) {
  ListaGenerica *tor_head = lista_torre;

  while (tor_head != NULL) {
    printf("\n|%s|", ((Torre *)tor_head->data)->id);
    printf("\n|%s|", ((Torre *)tor_head->data)->cor1);
    printf("\n|%s|", ((Torre *)tor_head->data)->cor2);
    printf("|%.2f|", ((Torre *)tor_head->data)->x);
    printf("|%.2f|", ((Torre *)tor_head->data)->y);
    printf("|%.2f|", ((Torre *)tor_head->data)->raio);
    tor_head = tor_head->next;
  }
}
