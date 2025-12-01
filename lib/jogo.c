#include "jogo.h"

// Arvore

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

// Pilha

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

// Fila

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


// jogador
void jogadorInicializar(Jogador* j, int id, No* inicio) {
    j->id = id;
    j->atual = inicio;

    // Marca o nó como ocupado
    if (inicio)
        inicio->ocupado = id;

    // Histórico vazio
    pilhaInicializar(&j->historico);

    // Zera visitados
    for (int i = 0; i < 4; i++) {
        j->visitados[i] = 0;
    }

    // Marca o primeiro nó como visitado
    jogadorVisitarNo(j, inicio);
}

void jogadorVisitarNo(Jogador* j, No* no) {
    if (!no) return;

    int nivel = no->nivel;
    j->visitados[nivel] += 1;

    // coloca no histórico
    pilhaPush(&j->historico, no);
}