#ifndef JOGO_H
#define JOGO_H

#include "arvore.h"
#include "fila.h"
#include "lista.h"
#include "pilha.h"

// Jogador
typedef struct {
  int id;           // 1 ou 2
  No *atual;        // posição atual
  Pilha historico;  // histórico de passos
  int visitados[4]; // quantidade de nós visitados por nível

  // atributos do jogador
  int vida;
  int vidaMaxima;
  int forca;
  int defesa;

  Item *inventario; // inventario (lista encadeada simples)
} Jogador;

void jogadorInicializar(Jogador *j, int id, No *inicio);
void jogadorVisitarNo(Jogador *j, No *no);

No *obterNoDestino(No *raiz, Jogador *j, int direcao);
void resolverEncontroComum(Jogador *j, No *destino, Fila *log);
int resolverDuelo(Jogador *j1, Jogador *j2, No *destino, No *raiz);
int jogadorMover(Jogador *j, Jogador *outro, No *raiz, int direcao, Fila *log);
void inventarioAplicarAoJogador(Item *it, Jogador *j);
int lerInteiro();

#endif
