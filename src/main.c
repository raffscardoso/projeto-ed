#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "jogo.h"
#include "fila.h" // Incluir a fila

int main() {
    srand(time(NULL));

    // 1. Inicializar o Log
    Fila logEventos;
    filaInicializar(&logEventos);
    filaEnfileirar(&logEventos, "--- INICIO DO JOGO CODEBATTLE ---");

    printf("========================\n");
    printf("=   CODEBATTLE (C)    =\n");
    printf("========================\n\n");

    // Criar a árvore
    No* raiz = arvoreCriar(1, 0, 3);

    // Jogadores
    No* inicioJ1 = arvoreBuscarPorIndice(raiz, 8);
    No* inicioJ2 = arvoreBuscarPorIndice(raiz, 15);

    Jogador j1, j2;
    jogadorInicializar(&j1, 1, inicioJ1);
    jogadorInicializar(&j2, 2, inicioJ2);

    // Log inicial
    char msgInicial[100];
    sprintf(msgInicial, "J1 em %s | J2 em %s", j1.atual->nome, j2.atual->nome);
    filaEnfileirar(&logEventos, msgInicial);

    printf("Jogador 1 comecou em: %s (index %d)\n", j1.atual->nome, j1.atual->index);
    printf("Jogador 2 comecou em: %s (index %d)\n\n", j2.atual->nome, j2.atual->index);

    int opcao;
    while (1) {
        // --- TURNO JOGADOR 1 ---
        printf("\n========================================\n");
        printf(" TURNO DO JOGADOR 1\n");
        printf(" Local: %s (index %d) | Vida:%d Forca:%d Defesa:%d Chave:%d\n", j1.atual->nome, j1.atual->index, j1.vida, j1.forca, j1.defesa, j1.chave);
        printf("----------------------------------------\n");
        printf("1 - Mover esquerda\n2 - Mover direita\n3 - Subir para o pai\n4 - Ver inventario\n0 - Sair\nEscolha: ");
        fflush(stdout);
        opcao = lerInteiro();
        if (opcao < 0) { printf("Entrada invalida.\n"); continue; }

        if (opcao == 0) break;

        // Passamos &logEventos para as funções
        if (opcao == 1) jogadorMover(&j1, &j2, raiz, -1, &logEventos);
        else if (opcao == 2) jogadorMover(&j1, &j2, raiz, +1, &logEventos);
        else if (opcao == 3) jogadorMover(&j1, &j2, raiz, 2, &logEventos);
        else if (opcao == 4) inventarioListar(j1.inventario);
        else { printf("Opcao invalida.\n"); continue; }

        if (j1.atual->index == 1) { 
            printf("\n=== Jogador 1 conquistou o NUCLEO-X! VENCEU! ===\n"); 
            filaEnfileirar(&logEventos, "VITORIA: Jogador 1 conquistou o NUCLEO-X!");
            break; 
        }

        // --- TURNO JOGADOR 2 ---
        printf("\n========================================\n");
        printf(" TURNO DO JOGADOR 2\n");
        printf(" Local: %s (index %d) | Vida:%d Forca:%d Defesa:%d Chave:%d\n", j2.atual->nome, j2.atual->index, j2.vida, j2.forca, j2.defesa, j2.chave);
        printf("----------------------------------------\n");
        printf("1 - Mover esquerda\n2 - Mover direita\n3 - Subir para o pai\n4 - Ver inventario\n0 - Sair\nEscolha: ");
        fflush(stdout);
        opcao = lerInteiro();
        if (opcao < 0) { printf("Entrada invalida.\n"); continue; }

        if (opcao == 0) break;

        if (opcao == 1) jogadorMover(&j2, &j1, raiz, -1, &logEventos);
        else if (opcao == 2) jogadorMover(&j2, &j1, raiz, +1, &logEventos);
        else if (opcao == 3) jogadorMover(&j2, &j1, raiz, 2, &logEventos);
        else if (opcao == 4) inventarioListar(j2.inventario);
        else { printf("Opcao invalida.\n"); continue; }

        if (j2.atual->index == 1) { 
            printf("\n=== Jogador 2 conquistou o NUCLEO-X! VENCEU! ===\n"); 
            filaEnfileirar(&logEventos, "VITORIA: Jogador 2 conquistou o NUCLEO-X!");
            break; 
        }
    }

    printf("\nSalvando log de eventos...\n");
    // 2. Salvar o arquivo TXT
    filaSalvarLog(&logEventos, "logEventos.txt");
    
    // 3. Limpar memória da fila
    filaLimpar(&logEventos);

    printf("Encerrando...\n");
    return 0;
}