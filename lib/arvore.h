#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>
#include <stdlib.h>

typedef enum {
  NORMAL = 0,
  RECURSO = 1,
  BATALHA = 2,
} TipoTerritorio;

typedef struct no {
  int index; // índice do nó (1 a 15)
  int nivel; // nível (0 a 3)
  char nome[50];
  TipoTerritorio tipo;
  int ocupado; // 0=livre, 1=jog1, 2=jog2
  struct no *pai, *esq, *dir;
} No;

No *criarNo(int index, int nivel, const char *nome, No *pai);
No *arvoreCriar();
No *arvoreBuscarPorIndice(No *raiz, int index);

#endif
