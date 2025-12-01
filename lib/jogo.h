#ifndef JOGO_H
#define JOGO_H

#include <stdio.h>
#include <stdlib.h>

// Tipo de Territorio de cada nó

typedef enum {
    NORMAL = 0,
    RECURSO = 1,
    BATALHA = 2
} TipoTerritorio;

// Árvore

typedef struct no {
    int index;              // índice do nó (1 a 15)
    int nivel;              // nível (0 a 3)
    char nome[50];
    TipoTerritorio tipo;
    int ocupado;            // 0=livre, 1=jog1, 2=jog2
    struct no *esq, *dir;
} No;

/* ------------ CRIAÇÃO E UTILIDADES DA ÁRVORE ---------------- */

No* arvoreCriar(int index, int nivel, int maxNivel);
No* arvoreBuscarPorIndice(No* raiz, int index);
No* arvoreEncontrarPai(No* raiz, No* alvo);

// Pilha

typedef struct nodoPilha {
    No* dado;
    struct nodoPilha* prox;
} NodoPilha;

typedef struct {
    NodoPilha* topo;
} Pilha;

void pilhaInicializar(Pilha* p);
int  pilhaVazia(Pilha* p);
void pilhaPush(Pilha* p, No* valor);
No*  pilhaPop(Pilha* p);
No*  pilhaTopo(Pilha* p);
void pilhaLimpar(Pilha* p);

// Fila

typedef struct nodoFila {
    No* dado;
    struct nodoFila* prox;
} NodoFila;

typedef struct {
    NodoFila* inicio;
    NodoFila* fim;
} Fila;

void filaInicializar(Fila* f);
int  filaVazia(Fila* f);
void filaEnfileirar(Fila* f, No* valor);
No*  filaDesenfileirar(Fila* f);
No*  filaPrimeiro(Fila* f);
void filaLimpar(Fila* f);

// Jogador

typedef struct {
    int id;                 // 1 ou 2
    No* atual;              // posição atual
    Pilha historico;        // histórico de passos
    int visitados[4];       // quantidade de nós visitados por nível
} Jogador;

void jogadorInicializar(Jogador* j, int id, No* inicio);
void jogadorVisitarNo(Jogador* j, No* no);

No* obterNoDestino(No* raiz, Jogador* j, int direcao);
void resolverEncontroComum(Jogador* j, No* destino);
void resolverDuelo(Jogador* j1, Jogador* j2, No* destino, No* raiz);
void jogadorMover(Jogador* j, Jogador* outro, No* raiz, int direcao);


#endif