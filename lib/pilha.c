#include "lib/pilha.h"

Pilha* pilhaInicializar() {
    return NULL;
}

int pilhaPush(Pilha** p, int valor){
    Pilha* novo = (Pilha*)malloc(sizeof(Pilha));
    if(novo == NULL){
        return 0;
    }

    novo->numero = valor;
    novo->prox = *p;
    *p = novo;

    return 1;
}

int pilhaPop(Pilha** p){
    if(*p == NULL){
        return 0;
    }

    Pilha* novo = *p;
    *p = (*p)->prox;

    free(novo);
    return 1;
}

void pilhaTopo(Pilha** p){
    if(*p == NULL){
        printf("Pilha vazia\n");
        return;
    }
    printf("Topo: %d\n", (*p)->numero);
}

void pilhaLiberar(Pilha** p){
    while(*p != NULL){
        Pilha* tmp = *p;
        *p = (*p)->prox;
        free(tmp);
    }
}