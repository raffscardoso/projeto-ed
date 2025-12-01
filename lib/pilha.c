#include "lib/pilha.h"

/*
    pilhaInicializar
    parâmetro: Nenhum
    retorno: Pilha inicializada com NULL
*/
Pilha* pilhaInicializar() {
    return NULL;
}

/*
    pilhaPush
    parâmetros: Ponteiro duplo para pilha e valor inteiro a ser inserido
    retorno: 1 se for bem sucedido, 0 se não for
*/
int pilhaPush(Pilha** p, int valor){
    Pilha* novo = (Pilha*)malloc(sizeof(Pilha));
    if(novo == NULL){
        return 0;
    }

    novo->numero = valor;
    novo->prox = *p;
    *p = novo;

    return 1;
}

/*
    pilhaPop
    parâmetros: Ponteiro duplo para pilha
    retorno: 1 se for bem sucedido, 0 se não for
*/
int pilhaPop(Pilha** p){
    if(*p == NULL){
        return 0;
    }

    Pilha* novo = *p;
    *p = (*p)->prox;

    free(novo);
    return 1;
}

/*
    pilhaTopo
    parçametro: Ponteiro duplo para pilha
    retorno: Nenhum, printa o topo da Pilha no terminal
*/
void pilhaTopo(Pilha** p){
    if(*p == NULL){
        printf("Pilha vazia\n");
        return;
    }
    printf("Topo: %d\n", (*p)->numero);
}

/*
    pilhaLiberar
    parâmetro: Ponteiro duplo para pilha
    retorno: Nanhum, porém libera a memória da pilha alocada
*/
void pilhaLiberar(Pilha** p){
    while(*p != NULL){
        Pilha* tmp = *p;
        *p = (*p)->prox;
        free(tmp);
    }
}