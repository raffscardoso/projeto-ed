#include "arvore.h"
#include <stdlib.h>
#include <string.h>

No* criarNo(int index, int nivel, const char* nome, No* pai) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo) {
        novo->index = index;
        novo->nivel = nivel;
        strcpy(novo->nome, nome);
        novo->tipo = rand() % 3; 
        novo->ocupado = 0;
        novo->pai = pai;
        novo->esq = NULL;
        novo->dir = NULL;
    }
    return novo;
}

// cria a árvore com a estrutura do mapa (3 niveis)
No* arvoreCriar() {
    // nível 0
    No* nucleoX = criarNo(1, 0, "Nucleo-X", NULL);
    nucleoX->tipo = NORMAL; // Nucleo-X é sempre NORMAL

    // nível 1
    nucleoX->esq = criarNo(2, 1, "T1", nucleoX);
    nucleoX->dir = criarNo(3, 1, "T2", nucleoX);

    // nível 2
    nucleoX->esq->esq = criarNo(4, 2, "T3", nucleoX->esq);
    nucleoX->esq->dir = criarNo(5, 2, "T4", nucleoX->esq);
    nucleoX->dir->esq = criarNo(6, 2, "T5", nucleoX->dir);
    nucleoX->dir->dir = criarNo(7, 2, "T6", nucleoX->dir);

    // nível 3
    nucleoX->esq->esq->esq = criarNo(8, 3, "F1", nucleoX->esq->esq);
    nucleoX->esq->esq->dir = criarNo(9, 3, "F2", nucleoX->esq->esq);
    nucleoX->esq->dir->esq = criarNo(10, 3, "F3", nucleoX->esq->dir);
    nucleoX->esq->dir->dir = criarNo(11, 3, "F4", nucleoX->esq->dir);
    nucleoX->dir->esq->esq = criarNo(12, 3, "F5", nucleoX->dir->esq);
    nucleoX->dir->esq->dir = criarNo(13, 3, "F6", nucleoX->dir->esq);
    nucleoX->dir->dir->esq = criarNo(14, 3, "F7", nucleoX->dir->dir);
    nucleoX->dir->dir->dir = criarNo(15, 3, "F8", nucleoX->dir->dir);
    
    return nucleoX;
}


// busca recursiva por índice do nó
No *arvoreBuscarPorIndice(No *raiz, int index) {
  if (!raiz)
    return NULL;
  if (raiz->index == index)
    return raiz;

  No *e = arvoreBuscarPorIndice(raiz->esq, index);
  if (e)
    return e;

  return arvoreBuscarPorIndice(raiz->dir, index);
}
