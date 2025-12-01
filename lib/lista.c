#include "lista.h"

/*
    listaInserirInicio
    parâmetros: Ponteiro para lista e um valor inteiro para inserir
    retorno: Lista com valor inteiro inserido no início
*/
Lista *listaInserirInicio(Lista *l, int valor) {
  Lista *no = (Lista *)malloc(sizeof(Lista));
  if (no == NULL)
    exit(1);

  no->numero = valor;
  no->prox = l;

  return no;
}

/*
    listaInserirFinal
    parâmetros: Ponteiro para lista e um valor inteiro para inserir
    retorno: Lista com valor inteiro inserido no final
*/
Lista *listaInserirFinal(Lista *l, int valor) {
  Lista *no = (Lista *)malloc(sizeof(Lista));
  if (no == NULL)
    exit(1);

  no->numero = valor;
  no->prox = NULL;

  if (l == NULL) {
    return no;
  }

  Lista *l_aux = l;
  while (l_aux->prox != NULL) {
    l_aux = l_aux->prox;
  }
  l_aux->prox = no;

  return l;
}

/*
    listaReoordenar
    parâmetros: Ponteiro para lista
    retorno: Lista reoordenada
*/
Lista *listaReoordenar(Lista *l) {
  // se a lista original for vazia retorna nulo
  if (l == NULL) {
    return NULL;
  }

  // declaração das listas
  Lista *l_par = NULL;
  Lista *l_impar = NULL;
  Lista *l_aux = l;

  while (l_aux != NULL) {
    if (l_aux->numero % 2 == 0) {
      l_par = listaInserirFinal(l_par, l_aux->numero);
    } else {
      l_impar = listaInserirFinal(l_impar, l_aux->numero);
    }
    l_aux = l_aux->prox;
  }

  if (l_par == NULL) {
    return l_impar;
  }

  Lista *ultimo_par = l_par;

  while (ultimo_par->prox != NULL) {
    ultimo_par = ultimo_par->prox;
  }

  ultimo_par->prox = l_impar;

  return l_par;
}

/*
    listaImprimir
    parâmetro: Ponteiro para lista
    retorno: nenhum, imprime a lista no terminal
*/
void listaImprimir(Lista *l) {
  while (l != NULL) {
    printf("%d -> ", l->numero);
    l = l->prox;
  }
  printf("NULL\n");
}

/*
    listaLiberar
    parâmetros: Ponteiro para lista
    retorno: Nenhum, libera memória alocada da lista
*/
void listaLiberar(Lista *l) {
  Lista *atual = l;
  Lista *proximo_no;

  while (atual != NULL) {
    proximo_no = atual->prox;
    free(atual);
    atual = proximo_no;
  }
}
