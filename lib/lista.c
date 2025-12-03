#include "lista.h"
#include <stdlib.h>

void listaInicializar(Lista* l) {
    l->inicio = NULL;
}

int listaVazia(Lista* l) {
    return l->inicio == NULL;
}

// Insere um inteiro no começo da lista
void listaInserirInicio(Lista* l, int elemento) {
    NodoLista* novo = (NodoLista*)malloc(sizeof(NodoLista));
    novo->info = elemento;
    novo->prox = l->inicio;
    l->inicio = novo;
}

// Remove o primeiro elemento e retorna seu valor ou -1 caso a lista esteja vazia
int listaRemoverInicio(Lista* l) {
    if (listaVazia(l)) return -1;

    NodoLista* aux = l->inicio;
    int valor = aux->info;

    l->inicio = aux->prox;
    free(aux); 

    return valor;
}

void listaLimparMemoria(Lista* l) {
    while (!listaVazia(l)) {
        listaRemoverInicio(l);
    }
}
