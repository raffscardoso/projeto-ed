#ifndef LISTA_H
#define LISTA_H

typedef struct nodoLista {
    int info;
    struct nodoLista* prox;
} NodoLista;

typedef struct {
    NodoLista* inicio;
} Lista;

void listaInicializar(Lista* l);
int  listaVazia(Lista* l);
void listaInserirInicio(Lista* l, int elemento);
int  listaRemoverInicio(Lista* l);
void listaLimparMemoria(Lista* l);

#endif
