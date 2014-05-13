#include <stdio.h>
#include <stdlib.h>

#include "fila.h"


fila *aloca() {
  fila *f = malloc(sizeof(fila));

  f->comeco = NULL;

  f->fim = NULL;

  f->count = 0;

  return f;
}


void libera(fila *f) {
  elemento *e, *temp;

  e = f->comeco;

  while(e != NULL) {
    temp = e->prox;

    free(e);

    e = temp;
  }

  free(f);
}


void retira(fila *f) {
  elemento *e = f->comeco;

  if(e == NULL) {
    fprintf(stderr, "tentou retirar de lista vazia\n");
    exit(EXIT_FAILURE);
  }

  f->comeco = e->prox;

  if(f->comeco == NULL)
    f->fim = NULL;

  f->count--;

  free(e);
}


void insere(fila *f, int x, int y) {
  elemento *e = malloc(sizeof(elemento));

  e->x = x;
  e->y = y;

  f->count++;

  e->prox = NULL;

  if(f->fim == NULL) {
    f->comeco = e;

    f->fim = e;
  }
  else {
    f->fim->prox = e;

    f->fim = e;
  }
}