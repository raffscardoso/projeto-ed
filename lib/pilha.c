#include "pilha.h"
#include <stdlib.h>

void pilhaInicializar(Pilha* p) {
    p->topo = NULL;
}

int pilhaVazia(Pilha* p) {
    return p->topo == NULL;
}

void pilhaPush(Pilha* p, No* valor) {
    NodoPilha* novo = malloc(sizeof(NodoPilha));
    novo->dado = valor;
    novo->prox = p->topo;
    p->topo = novo;
}

No* pilhaPop(Pilha* p) {
    if (pilhaVazia(p)) return NULL;

    NodoPilha* topo = p->topo;
    No* valor = topo->dado;

    p->topo = topo->prox;
    free(topo);

    return valor;
}

No* pilhaTopo(Pilha* p) {
    if (pilhaVazia(p)) return NULL;
    return p->topo->dado;
}

void pilhaLimpar(Pilha* p) {
    while (!pilhaVazia(p)) {
        pilhaPop(p);
    }
}


