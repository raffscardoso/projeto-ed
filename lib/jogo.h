#ifndef JOGO_H
#define JOGO_H

#include "arvore.h"
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
  int forca;
  int defesa;

  Item *inventario; // inventario (lista encadeada simples)
  int chave;        // chave para subir niveis
} Jogador;

void jogadorInicializar(Jogador *j, int id, No *inicio);
void jogadorVisitarNo(Jogador *j, No *no);

// movimento: direcao = -1 (esquerda no mesmo nível), +1 (direita no mesmo
// nível), 2 (subir/ir ao pai)
No *obterNoDestino(No *raiz, Jogador *j, int direcao);
No *obterNoPai(No *raiz, Jogador *j);
void resolverEncontroComum(Jogador *j, No *destino);
void resolverDuelo(Jogador *j1, Jogador *j2, No *destino, No *raiz);
void jogadorMover(Jogador *j, Jogador *outro, No *raiz, int direcao);
void inventarioAplicarAoJogador(Item *it, Jogador *j);
int lerInteiro(); // leitura segura de inteiro (usa fgets)

#endif
