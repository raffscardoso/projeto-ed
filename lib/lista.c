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
  if (!it) {
    printf(" (Vazio)\n");
    return;
  }
  while (it) {
    if (it->tipo == ITEM_ARMADURA)
      printf(" - Armadura (+%d defesa)\n", it->valor);
    else if (it->tipo == ITEM_ARMA)
      printf(" - Arma (+%d forca)\n", it->valor);
    else if (it->tipo == ITEM_AMULETO)
      printf(" - Amuleto (+%d vida max)\n", it->valor);
    else
      printf(" - Pocao de Vida (+%d HP)\n", it->valor);
    it = it->prox;
  }
}

// Procura a primeira poção, remove da lista e retorna o valor de cura.
// Retorna 0 se não houver poção.
int inventarioConsumirPocao(Item **head) {
  if (!head || !*head)
    return 0;

  Item *ant = NULL;
  Item *atual = *head;

  while (atual) {
    if (atual->tipo == ITEM_POCAO) {
      int cura = atual->valor;
      
      // Remove o nó da lista
      if (ant) {
        ant->prox = atual->prox;
      } else {
        *head = atual->prox;
      }
      
      free(atual);
      return cura;
    }
    ant = atual;
    atual = atual->prox;
  }
  return 0;
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
