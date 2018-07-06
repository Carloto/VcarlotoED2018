#include "qryfunctions.h"

/* Muda a cor de uma figura dado um id/cep */
void change_color(FILE         **OutputFile,
                  ListaGenerica *Hidrantes,
                  ListaGenerica *Torres,
                  ListaGenerica *Semaforos,
                  ListaGenerica *Quadras,
                  char          *input_line) {
  int   hidrante_check     = 0;
  int   torre_check        = 0;
  int   semaforo_check     = 0;
  int   quadra_check       = 0;
  char *token              = 0;
  ListaGenerica *temp_node = NULL;

  token = strtok(input_line, " ");
  token = strtok(NULL, " ");
  print_this(token);

  hidrante_check = find_id_hidrante(&temp_node, Hidrantes, token);

  if (hidrante_check == 1) {
    free_string(&((Hidrante *)temp_node->data)->cor1);
    token                               = strtok(NULL, " ");
    ((Hidrante *)temp_node->data)->cor1 = (char *)calloc(strlen(token) + 1,
                                                         sizeof(char));
    strcpy(((Hidrante *)temp_node->data)->cor1, token);
    free_string(&((Hidrante *)temp_node->data)->cor2);
    token                               = strtok(NULL, " ");
    ((Hidrante *)temp_node->data)->cor2 = (char *)calloc(strlen(token) + 1,
                                                         sizeof(char));
    strcpy(((Hidrante *)temp_node->data)->cor2, token);
    return;
  }

  torre_check = find_id_torre(&temp_node, Torres, token);

  if (torre_check == 1) {
    free_string(&((Torre *)temp_node->data)->cor1);
    token                            = strtok(NULL, " ");
    ((Torre *)temp_node->data)->cor1 =
      (char *)calloc(strlen(token) + 1, sizeof(char));
    strcpy(((Torre *)temp_node->data)->cor1, token);
    free_string(&((Torre *)temp_node->data)->cor2);
    token                            = strtok(NULL, " ");
    ((Torre *)temp_node->data)->cor2 =
      (char *)calloc(strlen(token) + 1, sizeof(char));
    strcpy(((Torre *)temp_node->data)->cor2, token);
    return;
  }

  semaforo_check = find_id_semaforo(&temp_node, Semaforos, token);

  if (semaforo_check == 1) {
    free_string(&((Semaforo *)temp_node->data)->cor1);
    token                               = strtok(NULL, " ");
    ((Semaforo *)temp_node->data)->cor1 = (char *)calloc(strlen(token) + 1,
                                                         sizeof(char));
    strcpy(((Semaforo *)temp_node->data)->cor1, token);
    free_string(&((Semaforo *)temp_node->data)->cor2);
    token                               = strtok(NULL, " ");
    ((Semaforo *)temp_node->data)->cor2 = (char *)calloc(strlen(token) + 1,
                                                         sizeof(char));
    strcpy(((Semaforo *)temp_node->data)->cor2, token);
    return;
  }

  quadra_check = find_id_quadra(&temp_node, Quadras, token);

  if (quadra_check == 1) {
    free_string(&((Quadra *)temp_node->data)->cor1);
    token                             = strtok(NULL, " ");
    ((Quadra *)temp_node->data)->cor1 =
      (char *)calloc(strlen(token) + 1, sizeof(char));
    strcpy(((Quadra *)temp_node->data)->cor1, token);
    free_string(&((Quadra *)temp_node->data)->cor2);
    token                             = strtok(NULL, " ");
    ((Quadra *)temp_node->data)->cor2 =
      (char *)calloc(strlen(token) + 1, sizeof(char));
    strcpy(((Quadra *)temp_node->data)->cor2, token);
    rtquad_svg(OutputFile, temp_node);
    return;
  }
}

/* Executa o comando q? */
void interno_retangulo(FILE         **OutputFile,
                       FILE         **OutputTxtStd,
                       ListaGenerica *Hidrantes,
                       ListaGenerica *Torres,
                       ListaGenerica *Semaforos,
                       ListaGenerica *Quadras,
                       char          *input_line) {
  char *token;
  float x                  = 0;
  float y                  = 0;
  float width              = 0;
  float height             = 0;
  char  space[2]           = " ";
  ListaGenerica *sem_head  = Semaforos;
  ListaGenerica *quad_head = Quadras;
  ListaGenerica *hid_head  = Hidrantes;
  ListaGenerica *tor_head  = Torres;

  space[2] = '\0';
  token    = strtok(input_line, " ");
  token    = strtok(NULL, " ");
  x        = atof(token);
  token    = strtok(NULL, " ");
  y        = atof(token);
  token    = strtok(NULL, " ");
  width    = atof(token);
  token    = strtok(NULL, " ");
  height   = atof(token);

  vazado_svg(OutputFile, x, y, width, height);

  while (sem_head != NULL) {
    if ((x < (((Semaforo *)sem_head->data)->x)) &&
        ((x + width) >
         (((Semaforo *)sem_head->data)->x /*+ ((Semaforo
                                           *)sem_head->data)->width*/
         ))
        &&
        (y < ((((Semaforo *)sem_head->data)->y))) &&
        ((y + height) >
         (((Semaforo *)sem_head->data)->y)) /*+ ((Semaforo
                                             *)sem_head->data)->height*/
        )
    {
      rtprint_txt(OutputTxtStd, NULL,
                  (((Semaforo *)sem_head->data)->id), -2);
      rtprint_txt(OutputTxtStd, (((Semaforo *)sem_head->data)->id),
                  (((Semaforo *)sem_head->data)->id),
                  (((Semaforo *)sem_head->data)
                   ->x));
      rtprint_txt(OutputTxtStd, (((Semaforo *)sem_head->data)->id),
                  (((Semaforo *)sem_head->data)->id),
                  (((Semaforo *)sem_head->data)
                   ->y));
      rtprint_txt(OutputTxtStd,
                  NULL,
                  space,
                  -1);
    }
    sem_head = sem_head->next;
  }

  while (quad_head != NULL) {
    if ((x < (((Quadra *)quad_head->data)->x)) &&
        ((x + width) >
         (((Quadra *)quad_head->data)->x + ((Quadra *)quad_head->data)->width)) &&
        (y < ((((Quadra *)quad_head->data)->y))) &&
        ((y + height) >
         (((Quadra *)quad_head->data)->y) +
         ((Quadra *)quad_head->data)->height)) {
      rtprint_txt(OutputTxtStd, NULL,
                  (((Quadra *)quad_head->data)->cep), -2);
      rtprint_txt(OutputTxtStd, (((Quadra *)quad_head->data)->cep),
                  (((Quadra *)quad_head->data)->cep),
                  (((Quadra *)quad_head->data)
                   ->x));
      rtprint_txt(OutputTxtStd, (((Quadra *)quad_head->data)->cep),
                  (((Quadra *)quad_head->data)->cep),
                  (((Quadra *)quad_head->data)
                   ->y));
      rtprint_txt(OutputTxtStd, (((Quadra *)quad_head->data)->cep),
                  (((Quadra *)quad_head->data)->cep),
                  (((Quadra *)quad_head->data)
                   ->width));
      rtprint_txt(OutputTxtStd, (((Quadra *)quad_head->data)->cep),
                  (((Quadra *)quad_head->data)->cep),
                  (((Quadra *)quad_head->data)
                   ->height));
      rtprint_txt(OutputTxtStd,
                  NULL,
                  space,
                  -1);
    }
    quad_head = quad_head->next;
  }

  while (hid_head != NULL) {
    if ((x < (((Hidrante *)hid_head->data)->x)) &&
        ((x + width) >
         (((Hidrante *)hid_head->data)->x /*+ ((Hidrante
                                           *)hid_head->data)->width*/
         ))
        &&
        (y < ((((Hidrante *)hid_head->data)->y))) &&
        ((y + height) >
         (((Hidrante *)hid_head->data)->y)) /*+ ((Hidrante
                                             *)hid_head->data)->height*/
        )
    {
      rtprint_txt(OutputTxtStd, NULL,
                  (((Hidrante *)hid_head->data)->id), -2);
      rtprint_txt(OutputTxtStd, (((Hidrante *)hid_head->data)->id),
                  (((Hidrante *)hid_head->data)->id),
                  (((Hidrante *)hid_head->data)
                   ->x));
      rtprint_txt(OutputTxtStd, (((Hidrante *)hid_head->data)->id),
                  (((Hidrante *)hid_head->data)->id),
                  (((Hidrante *)hid_head->data)
                   ->y));
      rtprint_txt(OutputTxtStd,
                  NULL,
                  space,
                  -1);
    }
    hid_head = hid_head->next;
  }

  while (tor_head != NULL) {
    if ((x < (((Torre *)tor_head->data)->x)) &&
        ((x + width) >
         (((Torre *)tor_head->data)->x /*+ ((Torre *)tor_head->data)->width*/)) &&
        (y < ((((Torre *)tor_head->data)->y))) &&
        ((y + height) >
         (((Torre *)tor_head->data)->y)) /*+ ((Torre *)tor_head->data)->height*/)
    {
      rtprint_txt(OutputTxtStd, NULL,
                  (((Torre *)tor_head->data)->id), -2);
      rtprint_txt(OutputTxtStd, (((Torre *)tor_head->data)->id),
                  (((Torre *)tor_head->data)->id),
                  (((Torre *)tor_head->data)->x));
      rtprint_txt(OutputTxtStd, (((Torre *)tor_head->data)->id),
                  (((Torre *)tor_head->data)->id),
                  (((Torre *)tor_head->data)->y));
      rtprint_txt(OutputTxtStd,
                  NULL,
                  space,
                  -1);
    }
    tor_head = tor_head->next;
  }
}

/* Executa o comando Q? */
void interno_circulo(FILE         **OutputFile,
                     FILE         **OutputTxtStd,
                     ListaGenerica *Hidrantes,
                     ListaGenerica *Torres,
                     ListaGenerica *Semaforos,
                     ListaGenerica *Quadras,
                     char          *input_line) {
  char *token;
  float x                  = 0;
  float y                  = 0;
  float distX              = 0;
  float distY              = 0;
  float raio               = 0;
  float exp                = 2;
  char  space[2]           = " ";
  ListaGenerica *sem_head  = Semaforos;
  ListaGenerica *quad_head = Quadras;
  ListaGenerica *hid_head  = Hidrantes;
  ListaGenerica *tor_head  = Torres;

  space[2] = '\0';
  token    = strtok(input_line, " ");
  token    = strtok(NULL, " ");
  raio     = atof(token);
  token    = strtok(NULL, " ");
  x        = atof(token);
  token    = strtok(NULL, " ");
  y        = atof(token);

  vazado_svg(OutputFile, x, y, -1, raio);

  while (sem_head != NULL) {
    distX =
      sqrt(pow(x - (((Semaforo *)sem_head->data)->x),
               exp) + pow(y - (((Semaforo *)sem_head->data)->y), exp));
    distX = distX - raio;

    if (distX < 0) {
      rtprint_txt(OutputTxtStd, NULL,
                  (((Semaforo *)sem_head->data)->id), -2);
      rtprint_txt(OutputTxtStd, (((Semaforo *)sem_head->data)->id),
                  (((Semaforo *)sem_head->data)->id),
                  (((Semaforo *)sem_head->data)
                   ->x));
      rtprint_txt(OutputTxtStd, (((Semaforo *)sem_head->data)->id),
                  (((Semaforo *)sem_head->data)->id),
                  (((Semaforo *)sem_head->data)
                   ->y));
      rtprint_txt(OutputTxtStd,
                  NULL,
                  space,
                  -1);
    }
    sem_head = sem_head->next;
  }

  while (quad_head != NULL) {
    distX =
      sqrt(pow(x - (((Quadra *)quad_head->data)->x),
               exp) + pow(y - (((Quadra *)quad_head->data)->y), exp));
    distX = distX - raio;
    distY =
      sqrt(pow(x -
               (((Quadra *)quad_head->data)->x +
                ((Quadra *)quad_head->data)->width),
               exp) + pow(y - (((Quadra *)quad_head->data)->y), exp));
    distY = distY - raio;

    if ((distX < 0) && (distY < 0)) {
      distX =
        sqrt(pow(x - (((Quadra *)quad_head->data)->x),
                 exp) +
             pow(y -
                 (((Quadra *)quad_head->data)->y +
                  ((Quadra *)quad_head->data)->height),
                 exp));
      distX = distX - raio;
      distY =
        sqrt(pow(x -
                 (((Quadra *)quad_head->data)->x +
                  ((Quadra *)quad_head->data)->width),
                 exp) +
             pow(y -
                 (((Quadra *)quad_head->data)->y +
                  ((Quadra *)quad_head->data)->height),
                 exp));
      distY = distY - raio;

      if ((distX < 0) && (distY < 0)) {
        rtprint_txt(OutputTxtStd, NULL,
                    (((Quadra *)quad_head->data)->cep), -2);
        rtprint_txt(OutputTxtStd, (((Quadra *)quad_head->data)->cep),
                    (((Quadra *)quad_head->data)->cep),
                    (((Quadra *)quad_head->
                      data)->x));
        rtprint_txt(OutputTxtStd, (((Quadra *)quad_head->data)->cep),
                    (((Quadra *)quad_head->data)->cep),
                    (((Quadra *)quad_head->
                      data)->y));
        rtprint_txt(OutputTxtStd, (((Quadra *)quad_head->data)->cep),
                    (((Quadra *)quad_head->data)->cep),
                    (((Quadra *)quad_head->
                      data)->width));
        rtprint_txt(OutputTxtStd, (((Quadra *)quad_head->data)->cep),
                    (((Quadra *)quad_head->data)->cep),
                    (((Quadra *)quad_head->
                      data)->height));
        rtprint_txt(OutputTxtStd,
                    NULL,
                    space,
                    -1);
      }
    }
    quad_head = quad_head->next;
  }

  while (hid_head != NULL) {
    distX =
      sqrt(pow(x - (((Hidrante *)hid_head->data)->x),
               exp) + pow(y - (((Hidrante *)hid_head->data)->y), exp));
    distX = distX - raio;

    if (distX < 0) {
      rtprint_txt(OutputTxtStd, NULL,
                  (((Hidrante *)hid_head->data)->id), -2);
      rtprint_txt(OutputTxtStd, (((Hidrante *)hid_head->data)->id),
                  (((Hidrante *)hid_head->data)->id),
                  (((Hidrante *)hid_head->data)
                   ->x));
      rtprint_txt(OutputTxtStd, (((Hidrante *)hid_head->data)->id),
                  (((Hidrante *)hid_head->data)->id),
                  (((Hidrante *)hid_head->data)
                   ->y));
      rtprint_txt(OutputTxtStd,
                  NULL,
                  space,
                  -1);
    }
    hid_head = hid_head->next;
  }

  while (tor_head != NULL) {
    distX =
      sqrt(pow(x - (((Torre *)tor_head->data)->x),
               exp) + pow(y - (((Torre *)tor_head->data)->y), exp));
    distX = distX - raio;

    if (distX < 0) {
      rtprint_txt(OutputTxtStd, NULL,
                  (((Torre *)tor_head->data)->id), -2);
      rtprint_txt(OutputTxtStd, (((Torre *)tor_head->data)->id),
                  (((Torre *)tor_head->data)->id),
                  (((Torre *)tor_head->data)->x));
      rtprint_txt(OutputTxtStd, (((Torre *)tor_head->data)->id),
                  (((Torre *)tor_head->data)->id),
                  (((Torre *)tor_head->data)->y));
      rtprint_txt(OutputTxtStd,
                  NULL,
                  space,
                  -1);
    }
    tor_head = tor_head->next;
  }
}

/* Executa a destruição de figuras dentro de retangulos */
void kill_inside(FILE          **OutputFile,
                 FILE          **OutputTxtStd,
                 ListaGenerica  *Hidrantes,
                 ListaGenerica  *Torres,
                 ListaGenerica  *Semaforos,
                 ListaGenerica **Quadras,
                 char           *input_line) {
  char *token;
  float x        = 0;
  float y        = 0;
  float distX    = 0;
  float distY    = 0;
  float exp      = 2;
  float width    = 0;
  float height   = 0;
  char  space[2] = " ";
  char  comando[4];
  ListaGenerica *quad_head     = *Quadras;
  ListaGenerica *quad_anterior = *Quadras;

  /*  ListaGenerica *sem_head  = Semaforos;
     ListaGenerica *hid_head  = Hidrantes;
     ListaGenerica *tor_head  = Torres;*/

  space[2] = '\0';
  token    = strtok(input_line, " ");
  strcpy(comando, token);


  /*
     while (sem_head != NULL) {
      if ((x < (((Semaforo *)sem_head->data)->x)) &&
          ((x + width) >
           (((Semaforo *)sem_head->data)->x))
          &&
          (y < ((((Semaforo *)sem_head->data)->y))) &&
          ((y + height) >
           (((Semaforo *)sem_head->data)->y)))
      {
        rtprint_txt(OutputTxtStd, NULL,
                    (((Semaforo *)sem_head->data)->id), -2);
        rtprint_txt(OutputTxtStd, (((Semaforo *)sem_head->data)->id),
                    (((Semaforo *)sem_head->data)->id),
                    (((Semaforo *)sem_head->data)
                     ->x));
        rtprint_txt(OutputTxtStd, (((Semaforo *)sem_head->data)->id),
                    (((Semaforo *)sem_head->data)->id),
                    (((Semaforo *)sem_head->data)
                     ->y));
        rtprint_txt(OutputTxtStd,
                    NULL,
                    space,
                    -1);
      }
      sem_head = sem_head->next;
     }
   */

  switch (comando[0]) {
  case 'd':

    token  = strtok(NULL, " ");
    x      = atof(token);
    token  = strtok(NULL, " ");
    y      = atof(token);
    token  = strtok(NULL, " ");
    width  = atof(token);
    token  = strtok(NULL, " ");
    height = atof(token);
    vazado_svg(OutputFile, x, y, width, height);

    while (quad_head != NULL) {
      if ((x < (((Quadra *)(quad_head)->data)->x)) &&
          ((x + width) >
           (((Quadra *)(quad_head)->data)->x +
            ((Quadra *)(quad_head)->data)->width)) &&
          (y < ((((Quadra *)(quad_head)->data)->y))) &&
          ((y + height) >
           (((Quadra *)(quad_head)->data)->y) +
           ((Quadra *)(quad_head)->data)->height)) {
        rtprint_txt(OutputTxtStd,
                    NULL,
                    (((Quadra *)(quad_head)->data)->cep),
                    -1);

        if ((quad_head) == *Quadras) {
          (*Quadras)        = (*Quadras)->next;
          (quad_head)->next = NULL;
          free_quadra((quad_head));
          (quad_head) = (*Quadras);
        } else {
          (quad_anterior)->next = (quad_head)->next;
          (quad_head)->next     = NULL;
          free_quadra((quad_head));
          (quad_head) = (quad_anterior)->next;
        }
      } else {
        quad_anterior = (quad_head);
        (quad_head)   = (quad_anterior)->next;
      }
    }
    break;

  case 'D':

    token = strtok(NULL, " ");
    width = atof(token);
    token = strtok(NULL, " ");
    x     = atof(token);
    token = strtok(NULL, " ");
    y     = atof(token);
    vazado_svg(OutputFile, x, y, -1, width);

    while (quad_head != NULL) {
      distX =
        sqrt(pow(x - (((Quadra *)quad_head->data)->x),
                 exp) + pow(y - (((Quadra *)quad_head->data)->y), exp));
      distX = distX - width;
      distY =
        sqrt(pow(x -
                 (((Quadra *)quad_head->data)->x +
                  ((Quadra *)quad_head->data)->width),
                 exp) + pow(y - (((Quadra *)quad_head->data)->y), exp));
      distY = distY - width;

      if ((distX < 0) && (distY < 0)) {
        distX =
          sqrt(pow(x - (((Quadra *)quad_head->data)->x),
                   exp) +
               pow(y -
                   (((Quadra *)quad_head->data)->y +
                    ((Quadra *)quad_head->data)->height),
                   exp));
        distX = distX - width;
        distY =
          sqrt(pow(x -
                   (((Quadra *)quad_head->data)->x +
                    ((Quadra *)quad_head->data)->width),
                   exp) +
               pow(y -
                   (((Quadra *)quad_head->data)->y +
                    ((Quadra *)quad_head->data)->height),
                   exp));
        distY = distY - width;

        if ((distX < 0) && (distY < 0)) {
          rtprint_txt(OutputTxtStd,
                      NULL,
                      (((Quadra *)(quad_head)->data)->cep),
                      -1);

          if ((quad_head) == *Quadras) {
            (*Quadras)        = (*Quadras)->next;
            (quad_head)->next = NULL;
            free_quadra((quad_head));
            (quad_head) = (*Quadras);
          } else {
            (quad_anterior)->next = (quad_head)->next;
            (quad_head)->next     = NULL;
            free_quadra((quad_head));
            (quad_head) = (quad_anterior)->next;
          }
        } else {
          quad_anterior = (quad_head);
          (quad_head)   = (quad_anterior)->next;
        }
      }
      else {
        quad_anterior = (quad_head);
        (quad_head)   = (quad_anterior)->next;
      }
    }
    break;

  default:
    break;
  }

  /*
     while (hid_head != NULL) {
      if ((x < (((Hidrante *)hid_head->data)->x)) &&
          ((x + width) > (((Hidrante *)hid_head->data)->x)) &&
          (y < ((((Hidrante *)hid_head->data)->y))) &&
          ((y + height) > (((Hidrante *)hid_head->data)->y))) {
        rtprint_txt(OutputTxtStd, NULL,
                    (((Hidrante *)hid_head->data)->id), -2);
        rtprint_txt(OutputTxtStd, (((Hidrante *)hid_head->data)->id),
                    (((Hidrante *)hid_head->data)->id),
                    (((Hidrante *)hid_head->data)
                     ->x));
        rtprint_txt(OutputTxtStd, (((Hidrante *)hid_head->data)->id),
                    (((Hidrante *)hid_head->data)->id),
                    (((Hidrante *)hid_head->data)
                     ->y));
        rtprint_txt(OutputTxtStd,
                    NULL,
                    space,
                    -1);
      }
      hid_head = hid_head->next;
     }

     while (tor_head != NULL) {
      if ((x < (((Torre *)tor_head->data)->x)) &&
          ((x + width) >
           (((Torre *)tor_head->data)->x)) &&
          (y < ((((Torre *)tor_head->data)->y))) &&
          ((y + height) >
           (((Torre *)tor_head->data)->y)))
      {
        rtprint_txt(OutputTxtStd, NULL,
                    (((Torre *)tor_head->data)->id), -2);
        rtprint_txt(OutputTxtStd, (((Torre *)tor_head->data)->id),
                    (((Torre *)tor_head->data)->id),
                    (((Torre *)tor_head->data)->x));
        rtprint_txt(OutputTxtStd, (((Torre *)tor_head->data)->id),
                    (((Torre *)tor_head->data)->id),
                    (((Torre *)tor_head->data)->y));
        rtprint_txt(OutputTxtStd,
                    NULL,
                    space,
                    -1);
      }
      tor_head = tor_head->next;
     }
   */
}
