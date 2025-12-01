#include "lib/fila.h"

Fila* filaInicializar(){
    return NULL;
}

void filaFrente(Fila** f){
    if(*f == NULL){
        printf("Fila Vazia\n");
    }else{
        printf("Frente: %d\n", (*f)->numero);
    }
}

int filaEnfileira(Fila** f, int valor){
    Fila* novo = (Fila*)malloc(sizeof(Fila));
    if(novo == NULL) return 0;

    novo->numero = valor;
    if(*f == NULL){
        novo->prox = NULL;
        *f = novo;
        return 1;
    }

    Fila* aux = *f;
    while(aux->prox != NULL){
        aux = aux->prox;
    }

    novo->prox = NULL;
    aux->prox = novo;
    return 1;
}

int filaDesenfileira(Fila** f){
    if(*f == NULL){
        return 0;
    }

    Fila* novo = *f;
    *f = (*f)->prox;
    free(novo);
    return 1;
}

void filaLiberar(Fila** f){
    Fila* atual = *f;
    while(atual != NULL){
        Fila* tmp = atual;
        atual = atual->prox;
        free(tmp);
    }
    *f = NULL;
}

int filaVazia(Fila* f){
    return (f == NULL);
}