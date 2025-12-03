#ifndef JOGO_H
#define JOGO_H

#include "arvore.h"
#include "pilha.h"
#include "lista.h"

// -------------- INVENTÁRIO (LISTA SIMPLES) ---------------- 

typedef enum {
    ITEM_ARMADURA,
    ITEM_ARMA,
    ITEM_AMULETO
} ItemTipo;

typedef struct item {
    ItemTipo tipo;
    int valor; // quantidade a adicionar na estatística
    struct item* prox;
} Item;

// Jogador
typedef struct {
    int id;                 // 1 ou 2
    No* atual;              // posição atual
    Pilha historico;        // histórico de passos
    Lista inventario;       // inventario do jogador 
    int visitados[4];       // quantidade de nós visitados por nível

    // atributos do jogador
    int vida;
    int forca;
    int defesa;

    // inventário (lista encadeada de itens)
    Item* inventario;
    // chave para subir niveis
    int chave;
} Jogador;

void jogadorInicializar(Jogador* j, int id, No* inicio);
void jogadorVisitarNo(Jogador* j, No* no);

// movimento: direcao = -1 (esquerda no mesmo nível), +1 (direita no mesmo nível), 2 (subir/ir ao pai)
No* obterNoDestino(No* raiz, Jogador* j, int direcao);
No* obterNoPai(No* raiz, Jogador* j);
void resolverEncontroComum(Jogador* j, No* destino);
void resolverDuelo(Jogador* j1, Jogador* j2, No* destino, No* raiz);
void jogadorMover(Jogador* j, Jogador* outro, No* raiz, int direcao);

// leitura segura de inteiro (usa fgets)
int lerInteiro();

// funcoes de inventario
void inventarioAdicionar(Item** head, ItemTipo tipo, int valor);
void inventarioListar(Item* head);
void inventarioLiberar(Item** head);
void inventarioAplicarAoJogador(Item* it, Jogador* j);

#endif
