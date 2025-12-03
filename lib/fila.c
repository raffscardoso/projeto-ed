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
    
    // Aloca memória exata para a mensagem e copia
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
    char* msg = aux->mensagem; // Guarda a mensagem para retornar

    f->inicio = aux->prox;
    if (f->inicio == NULL) {
        f->fim = NULL;
    }

    free(aux); // Libera apenas o nó, não a string (quem chamou que libere)
    return msg;
}

void filaLimpar(Fila* f) {
    while (!filaVazia(f)) {
        char* msg = filaDesenfileirar(f);
        free(msg); // Aqui liberamos a string pois estamos limpando tudo
    }
}

// Função para salvar o Log em TXT
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