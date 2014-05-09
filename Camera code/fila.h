#ifndef _FILA_H_
#define _FILA_H_


typedef struct _elemento {
  int x, y;
  struct _elemento *prox;
} elemento;

typedef struct {
  elemento *comeco, *fim;
  int count;
} fila;


fila *aloca();
void libera(fila *f);

void retira(fila *f);
void insere(fila *f, int x, int y);

#endif