#ifndef LISTA_H
#define LISTA_H

// -------------- INVENTÁRIO (LISTA SIMPLES) ----------------

typedef enum { ITEM_ARMADURA, ITEM_ARMA, ITEM_AMULETO, ITEM_POCAO } ItemTipo;

typedef struct item {
  ItemTipo tipo;
  int valor; // quantidade a adicionar na estatística
  struct item *prox;
} Item;

void inventarioAdicionar(Item **head, ItemTipo tipo, int valor);
void inventarioListar(Item *head);
int inventarioConsumirPocao(Item **head);
void inventarioLiberar(Item **head);

#endif
