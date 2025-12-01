#include "lib/fila.h"


/*
    filaInicializar
    parêmetros: Nenhum
    retorno: Uma fila inicializada com NULL
*/
Fila* filaInicializar(){
    return NULL;
}

/*
    filaFrente
    parêmetros: Um ponteiro duplo para fila
    retorno: nenhum, printa na tela a frente da fila caso exista
*/
void filaFrente(Fila** f){
    if(*f == NULL){
        printf("Fila Vazia\n");
    }else{
        printf("Frente: %d\n", (*f)->numero);
    }
}


/*
    filaEnfileira
    parâmetro: Ponteiro duplo para fila e um inteiro para enfileirar
    retorno: 0 se o enfileiramento der errado, 1 se der certo
*/
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

/*
    filaDesenfileira
    parâmetro: Ponteiro duplo para fila
    retorno: 0 se der errado, 1 se der certo
*/
int filaDesenfileira(Fila** f){
    if(*f == NULL){
        return 0;
    }

    Fila* novo = *f;
    *f = (*f)->prox;
    free(novo);
    return 1;
}

/*
    filaLiberar
    parâmetro: Ponteiro duplo para fila
    retorno: nenhum, porém, libera memória da fila
*/
void filaLiberar(Fila** f){
    Fila* atual = *f;
    while(atual != NULL){
        Fila* tmp = atual;
        atual = atual->prox;
        free(tmp);
    }
    *f = NULL;
}

/*
    filaVazia
    parâmetro: Ponteiro para fila
    retorno: 1 se a fila estiver vazia, 0 se não estiver
*/
int filaVazia(Fila* f){
    return (f == NULL);
}