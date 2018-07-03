#include "hidrante.h"


/* Adiciona um novo hidrante*/
void new_hidrante(ListaGenerica **hid_head,
                  ListaGenerica **hid_end,
                  char           *input_line,
                  Cores          *colors) {
  char *token = NULL;

  /* Cria um novo no na lista */
  ListaGenerica *new_node = (ListaGenerica *)calloc(1, sizeof(ListaGenerica));

  /* Inicializa a struct semaforo*/
  Hidrante *temp_hid = (Hidrante *)calloc(1, sizeof(Hidrante));

  temp_hid->id = NULL;

  token = strtok(input_line, " ");

  token        = strtok(NULL, " ");
  temp_hid->id = (char *)calloc(strlen(token) + 1, sizeof(char));
  strcpy(temp_hid->id, token);

  token       = strtok(NULL, " ");
  temp_hid->x = atof(token);

  token       = strtok(NULL, " ");
  temp_hid->y = atof(token);

  temp_hid->raio = 8;

  temp_hid->cor1 = (char *)calloc(strlen(colors->hid_stroke) + 1, sizeof(char));
  strcpy(temp_hid->cor1, colors->hid_stroke);

  temp_hid->cor2 = (char *)calloc(strlen(colors->hid_fill) + 1, sizeof(char));
  strcpy(temp_hid->cor2, colors->hid_fill);

  new_node->data = temp_hid;

  if (*hid_head == NULL) {
    (*hid_head)      = new_node;
    *hid_end         = *hid_head;
    (*hid_end)->next = NULL;
  } else {
    (*hid_end)->next = new_node;
    (*hid_end)       = (*hid_end)->next;
    (*hid_end)->next = NULL;
  }

  /*printf("\n%s", ((Hidrante *)(*quad_end)->data)->cep);*/
}

/* Free na struct e seus elementos */
void free_hidrante(ListaGenerica *temp_struct) {
  ListaGenerica *aux;

  while (temp_struct != NULL) {
    aux         = temp_struct;
    temp_struct = temp_struct->next;
    free_string(&(((Hidrante *)aux->data)->id));
    free_string(&(((Hidrante *)aux->data)->cor1));
    free_string(&(((Hidrante *)aux->data)->cor2));
    free(aux->data);
    free(aux);
  }
}

/* Imprimir o ultimo hidrante lido no svg */
void rthid_svg(FILE **OutputFile, ListaGenerica *HidFim) {
  float x;
  float y;

  fprintf(*OutputFile,
          "\t<circle cx=\"%f\" cy=\"%f\" r=\"%f\" ",
          ((Hidrante *)HidFim->data)->x,
          ((Hidrante *)HidFim->data)->y,
          ((Hidrante *)HidFim->data)->raio);

  fprintf(*OutputFile,
          "stroke=\"%s\" fill=\"%s\" style=\"stroke-width: 3\" fill-opacity=\"0.7\" stroke-opacity=\"0.7\" />\n",
          ((Hidrante *)HidFim->data)->cor1,
          ((Hidrante *)HidFim->data)->cor2);

  x = ((Hidrante *)HidFim->data)->x;
  y = ((Hidrante *)HidFim->data)->y + ((Hidrante *)HidFim->data)->raio / 2;

  fprintf(*OutputFile,
          "\t<text x=\"%f\" y=\"%f\" fill=\"white\" stroke=\"black\" text-anchor=\"middle\" alignment-baseline=\"central\" style=\"stroke-width: 0.5\" fill-opacity=\"0.7\" stroke-opacity=\"0.7\" >%s</text>\n",
          x,
          y,
          "H");
}

/* Imprimir toda a lista de hidarantes na saida svg */
void phid_svg(FILE **OutputFile, ListaGenerica *lista_hidrante) {
  ListaGenerica *hid_head = lista_hidrante;

  while (hid_head != NULL) {
    rthid_svg(OutputFile, hid_head);
    hid_head = hid_head->next;
  }
}

/* Função teste para imprimir lista */
void print_hidrante(ListaGenerica *lista_hidrante) {
  ListaGenerica *hid_head = lista_hidrante;

  while (hid_head != NULL) {
    printf("\n|%s|", ((Hidrante *)hid_head->data)->id);
    printf("\n|%s|", ((Hidrante *)hid_head->data)->cor1);
    printf("\n|%s|", ((Hidrante *)hid_head->data)->cor2);
    printf("|%.2f|", ((Hidrante *)hid_head->data)->x);
    printf("|%.2f|", ((Hidrante *)hid_head->data)->y);
    printf("|%.2f|", ((Hidrante *)hid_head->data)->raio);
    hid_head = hid_head->next;
  }
}
