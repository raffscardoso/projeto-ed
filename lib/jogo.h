#ifndef JOGO_H
#define JOGO_H

#include "arvore.h"
#include "pilha.h"
#include "lista.h"

// Jogador
typedef struct {
    int id;                 // 1 ou 2
    No* atual;              // posição atual
    Pilha historico;        // histórico de passos
    Lista inventario;       // inventario do jogador 
    int visitados[4];       // quantidade de nós visitados por nível
} Jogador;

void jogadorInicializar(Jogador* j, int id, No* inicio);
void jogadorVisitarNo(Jogador* j, No* no);

No* obterNoDestino(No* raiz, Jogador* j, int direcao);
void resolverEncontroComum(Jogador* j, No* destino);
void resolverDuelo(Jogador* j1, Jogador* j2, No* destino, No* raiz);
void jogadorMover(Jogador* j, Jogador* outro, No* raiz, int direcao);


#endif
