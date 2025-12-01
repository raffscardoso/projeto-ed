#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>

// TAD da Pilha
typedef struct pilha{
    int numero;
    struct pilha* prox;
} Pilha;

// Prototipos
Pilha* pilhaInicializar();
int pilhaPush(Pilha** p, int valor);
int pilhaPop(Pilha** p);
void pilhaTopo(Pilha** p);
void pilhaLiberar(Pilha** p);

#endif