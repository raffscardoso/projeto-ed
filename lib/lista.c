#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

// Inventário (lista simples)
void inventarioAdicionar(Item **head, ItemTipo tipo, int valor) {
  if (!head)
    return;
  Item *novo = malloc(sizeof(Item));
  novo->tipo = tipo;
  novo->valor = valor;
  novo->prox = *head;
  *head = novo;
}

void inventarioListar(Item *head) {
  Item *it = head;
  printf("Inventario:\n");
  while (it) {
    if (it->tipo == ITEM_ARMADURA)
      printf(" - Armadura (+%d defesa)\n", it->valor);
    else if (it->tipo == ITEM_ARMA)
      printf(" - Arma (+%d forca)\n", it->valor);
    else
      printf(" - Amuleto (+%d vida)\n", it->valor);
    it = it->prox;
  }
}

void inventarioLiberar(Item **head) {
  if (!head)
    return;
  Item *it = *head;
  while (it) {
    Item *aux = it->prox;
    free(it);
    it = aux;
  }
  *head = NULL;
}