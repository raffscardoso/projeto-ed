#ifndef FILA_H
#define FILA_H

#include "arvore.h"

typedef struct nodoFila {
    char* mensagem;
    struct nodoFila* prox;
} NodoFila;

typedef struct {
    NodoFila* inicio;
    NodoFila* fim;
} Fila;

void filaInicializar(Fila* f);
int  filaVazia(Fila* f);
void filaEnfileirar(Fila* f, const char* msg);
char*  filaDesenfileirar(Fila* f);
No*  filaPrimeiro(Fila* f);
void filaLimpar(Fila* f);

void filaSalvarLog(Fila* f, const char* nomeArquivo);

#endif
