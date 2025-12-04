#include "fila.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void filaInicializar(Fila* f) {
    f->inicio = NULL;
    f->fim = NULL;
}

int filaVazia(Fila* f) {
    return f->inicio == NULL;
}

void filaEnfileirar(Fila* f, const char* msg) {
    NodoFila* novo = malloc(sizeof(NodoFila));
    
    // aloca memória a mensagem e copia
    novo->mensagem = malloc(strlen(msg) + 1);
    strcpy(novo->mensagem, msg);
    
    novo->prox = NULL;

    if (filaVazia(f)) {
        f->inicio = novo;
    } else {
        f->fim->prox = novo;
    }
    f->fim = novo;
}

char* filaDesenfileirar(Fila* f) {
    if (filaVazia(f)) return NULL;

    NodoFila* aux = f->inicio;

    // guarda a mensagem para retornar
    char* msg = aux->mensagem; 

    f->inicio = aux->prox;
    if (f->inicio == NULL) {
        f->fim = NULL;
    }

    free(aux); 
    return msg;
}

void filaLimpar(Fila* f) {
    while (!filaVazia(f)) {
        char* msg = filaDesenfileirar(f);
        free(msg);
    }
}

// salvar o Log em TXT
void filaSalvarLog(Fila* f, const char* nomeArquivo) {
    FILE* arq = fopen(nomeArquivo, "w");
    if (!arq) {
        printf("Erro ao criar arquivo de log!\n");
        return;
    }

    fprintf(arq, "=== LOG DE EVENTOS - CODEBATTLE ===\n\n");

    NodoFila* atual = f->inicio;
    while (atual != NULL) {
        fprintf(arq, "%s\n", atual->mensagem);
        atual = atual->prox;
    }

    fclose(arq);
    printf("Log salvo com sucesso em '%s'!\n", nomeArquivo);
}
