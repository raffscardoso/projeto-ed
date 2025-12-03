#include "fila.h"
#include <stdlib.h>

void filaInicializar(Fila* f) {
    f->inicio = NULL;
    f->fim = NULL;
}

int filaVazia(Fila* f) {
    return f->inicio == NULL;
}

void filaEnfileirar(Fila* f, No* valor) {
    NodoFila* novo = malloc(sizeof(NodoFila));
    novo->dado = valor;
    novo->prox = NULL;

    if (filaVazia(f)) {
        f->inicio = novo;
        f->fim = novo;
    } else {
        f->fim->prox = novo;
        f->fim = novo;
    }
}

No* filaDesenfileirar(Fila* f) {
    if (filaVazia(f)) return NULL;

    NodoFila* aux = f->inicio;
    No* valor = aux->dado;

    f->inicio = aux->prox;
    if (!f->inicio)
        f->fim = NULL;

    free(aux);
    return valor;
}

No* filaPrimeiro(Fila* f) {
    if (filaVazia(f)) return NULL;
    return f->inicio->dado;
}

void filaLimpar(Fila* f) {
    while (!filaVazia(f)) {
        filaDesenfileirar(f);
    }
}


