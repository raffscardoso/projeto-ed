#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>

// TAD da lista
typedef struct lista{
    int numero;
    struct lista* prox;
} Lista;

// Prototipos
Lista* listaInserirInicio(Lista* l, int valor);
Lista* listaInserirFinal(Lista* l, int valor);
Lista* listaReoordenar(Lista* l);
void listaImprimir(Lista* l);
void listaLiberar(Lista* l);

#endif