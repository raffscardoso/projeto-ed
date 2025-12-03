#ifndef FILA_H
#define FILA_H

#include "arvore.h"

typedef struct nodoFila {
    No* dado;
    struct nodoFila* prox;
} NodoFila;

typedef struct {
    NodoFila* inicio;
    NodoFila* fim;
} Fila;

void filaInicializar(Fila* f);
int  filaVazia(Fila* f);
void filaEnfileirar(Fila* f, No* valor);
No*  filaDesenfileirar(Fila* f);
No*  filaPrimeiro(Fila* f);
void filaLimpar(Fila* f);

#endif
