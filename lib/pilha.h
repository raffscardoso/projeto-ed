#ifndef PILHA_H
#define PILHA_H

#include "arvore.h"

typedef struct nodoPilha {
    No* dado;
    struct nodoPilha* prox;
} NodoPilha;

typedef struct {
    NodoPilha* topo;
} Pilha;

void pilhaInicializar(Pilha* p);
int  pilhaVazia(Pilha* p);
void pilhaPush(Pilha* p, No* valor);
No*  pilhaPop(Pilha* p);
No*  pilhaTopo(Pilha* p);
void pilhaLimpar(Pilha* p);

#endif
