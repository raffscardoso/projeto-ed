#include "arvore.h"
#include <stdlib.h>

// Cria árvore binária completa
No* arvoreCriar(int index, int nivel, int maxNivel) {
    if (nivel > maxNivel) return NULL;

    No* novo = malloc(sizeof(No));
    novo->index = index;
    novo->nivel = nivel;
    novo->ocupado = 0;

    sprintf(novo->nome, "T%d", index);

    // Define tipo aleatório
    novo->tipo = rand() % 3;

    // Cria filhos
    novo->esq = arvoreCriar(index * 2, nivel + 1, maxNivel);
    novo->dir = arvoreCriar(index * 2 + 1, nivel + 1, maxNivel);

    return novo;
}

// Busca recursiva por índice do nó
No* arvoreBuscarPorIndice(No* raiz, int index) {
    if (!raiz) return NULL;
    if (raiz->index == index) return raiz;

    No* e = arvoreBuscarPorIndice(raiz->esq, index);
    if (e) return e;

    return arvoreBuscarPorIndice(raiz->dir, index);
}

// Encontra o pai de um nó percorrendo a árvore
No* arvoreEncontrarPai(No* raiz, No* alvo) {
    if (!raiz || raiz == alvo) return NULL;

    if (raiz->esq == alvo || raiz->dir == alvo)
        return raiz;

    No* e = arvoreEncontrarPai(raiz->esq, alvo);
    if (e) return e;

    return arvoreEncontrarPai(raiz->dir, alvo);
}


