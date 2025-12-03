#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../lib/jogo.h"

int main() {
    srand(time(NULL));

    printf("========================\n");
    printf("=   CODEBATTLE (C)    =\n");
    printf("========================\n\n");

    // Criar a árvore completa (nível máximo = 3 → 15 nós)
    No* raiz = arvoreCriar(1, 0, 3);

    // Jogador 1 começa no nó mais à esquerda do nível 3 (índice 8)
    No* inicioJ1 = arvoreBuscarPorIndice(raiz, 8);

    // Jogador 2 começa no nó mais à direita do nível 3 (índice 15)
    No* inicioJ2 = arvoreBuscarPorIndice(raiz, 15);

    Jogador j1, j2;

    jogadorInicializar(&j1, 1, inicioJ1);
    jogadorInicializar(&j2, 2, inicioJ2);

    printf("Jogador 1 comecou em: %s (index %d)\n", j1.atual->nome, j1.atual->index);
    printf("Jogador 2 comecou em: %s (index %d)\n\n", j2.atual->nome, j2.atual->index);

    int opcao;
    while (1) {
        // Mostra status do jogador 1
        printf("\n========================================\n");
        printf(" TURNO DO JOGADOR 1\n");
        printf(" Local: %s (index %d) | Vida:%d Forca:%d Defesa:%d Chave:%d\n", j1.atual->nome, j1.atual->index, j1.vida, j1.forca, j1.defesa, j1.chave);
        printf("----------------------------------------\n");
        printf("1 - Mover esquerda\n");
        printf("2 - Mover direita\n");
        printf("3 - Subir para o pai\n");
        printf("4 - Ver inventario\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        fflush(stdout);
        opcao = lerInteiro();
        if (opcao < 0) { printf("Entrada invalida. Tente novamente.\n"); continue; }

        if (opcao == 0) break;

        if (opcao == 1) jogadorMover(&j1, &j2, raiz, -1);
        else if (opcao == 2) jogadorMover(&j1, &j2, raiz, +1);
        else if (opcao == 3) jogadorMover(&j1, &j2, raiz, 2);
        else if (opcao == 4) inventarioListar(j1.inventario);
        else { printf("Opcao invalida.\n"); continue; }

        printf("Jogador 1 agora esta em: %s (index %d)\n", j1.atual->nome, j1.atual->index);

        if (j1.atual->index == 1) { printf("\n=== Jogador 1 conquistou o NUCLEO-X! VENCEU! ===\n"); break; }

        // Turno do jogador 2 (agora humano)
        printf("\n========================================\n");
        printf(" TURNO DO JOGADOR 2\n");
        printf(" Local: %s (index %d) | Vida:%d Forca:%d Defesa:%d Chave:%d\n", j2.atual->nome, j2.atual->index, j2.vida, j2.forca, j2.defesa, j2.chave);
        printf("----------------------------------------\n");
        printf("1 - Mover esquerda\n");
        printf("2 - Mover direita\n");
        printf("3 - Subir para o pai\n");
        printf("4 - Ver inventario\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        fflush(stdout);
        opcao = lerInteiro();
        if (opcao < 0) { printf("Entrada invalida. Tente novamente.\n"); continue; }

        if (opcao == 0) break;

        if (opcao == 1) jogadorMover(&j2, &j1, raiz, -1);
        else if (opcao == 2) jogadorMover(&j2, &j1, raiz, +1);
        else if (opcao == 3) jogadorMover(&j2, &j1, raiz, 2);
        else if (opcao == 4) inventarioListar(j2.inventario);
        else { printf("Opcao invalida.\n"); continue; }

        printf("Jogador 2 agora esta em: %s (index %d)\n", j2.atual->nome, j2.atual->index);
        if (j2.atual->index == 1) { printf("\n=== Jogador 2 conquistou o NUCLEO-X! VENCEU! ===\n"); break; }
    }

    printf("\nEncerrando...\n");
    return 0;
}
