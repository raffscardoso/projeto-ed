#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "jogo.h"

int main() {
    srand(time(NULL));

    printf("=== Teste do Sistema de Jogo ===\n\n");

    // Criar a árvore completa (nível máximo = 3 → 15 nós)
    No* raiz = arvoreCriar(1, 0, 3);

    // Jogador 1 começa no nó mais à esquerda do nível 3 (índice 8)
    No* inicioJ1 = arvoreBuscarPorIndice(raiz, 8);

    // Jogador 2 começa no nó mais à direita do nível 3 (índice 15)
    No* inicioJ2 = arvoreBuscarPorIndice(raiz, 15);

    Jogador j1, j2;

    jogadorInicializar(&j1, 1, inicioJ1);
    jogadorInicializar(&j2, 2, inicioJ2);

    printf("Jogador 1 começou em: %s (index %d)\n", j1.atual->nome, j1.atual->index);
    printf("Jogador 2 começou em: %s (index %d)\n\n", j2.atual->nome, j2.atual->index);

    int opcao;
    while (1) {
        printf("\n--- TURNO DO JOGADOR 1 ---\n");
        printf("1 - Mover esquerda\n");
        printf("2 - Mover direita\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 0) break;

        if (opcao == 1)
            jogadorMover(&j1, &j2, raiz, -1);
        else if (opcao == 2)
            jogadorMover(&j1, &j2, raiz, +1);

        printf("Jogador 1 agora está em: %s (index %d)\n", j1.atual->nome, j1.atual->index);

        // Turno do jogador 2 (automático só para teste)
        printf("\n--- TURNO AUTOMÁTICO DO JOGADOR 2 (vai para a esquerda) ---\n");
        jogadorMover(&j2, &j1, raiz, -1);

        printf("Jogador 2 agora está em: %s (index %d)\n", j2.atual->nome, j2.atual->index);
    }

    printf("\nEncerrando...\n");
    return 0;
}
