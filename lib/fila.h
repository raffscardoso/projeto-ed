#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>

// TAD da fila
typedef struct fila{
    int numero;
    struct fila* prox;
} Fila;

// Prototipos
Fila* filaInicializar();
void filaFrente(Fila** f);
int filaEnfileira(Fila** f, int valor);
int filaDesenfileira(Fila** f);
void filaLiberar(Fila** f);
int filaVazia(Fila* f);

#endif