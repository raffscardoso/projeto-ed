#include "../lib/fila.h"
#include "../lib/jogo.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// logica para esperar o enter para limpeza do terminal
void esperar_enter() {
  printf("\n\n--- Pressione Enter para continuar ---");
  fflush(stdout);
  int c;
  do {
    c = getchar();
  } while (c != '\n' && c != EOF);
}

int main() {
  srand(time(NULL));

  // inicializar o Log
  Fila logEventos;
  filaInicializar(&logEventos);
  filaEnfileirar(&logEventos, "--- INICIO DO JOGO CODEBATTLE ---");

  system("clear");
  printf("========================\n");
  printf("=   CODEBATTLE (C)    =\n");
  printf("========================\n\n");

  // cria a árvore
  No *raiz = arvoreCriar();

  // Jogadores
  No *inicioJ1 = arvoreBuscarPorIndice(raiz, 8);
  No *inicioJ2 = arvoreBuscarPorIndice(raiz, 15);

  Jogador j1, j2;
  jogadorInicializar(&j1, 1, inicioJ1);
  jogadorInicializar(&j2, 2, inicioJ2);

  // log inicial
  char msgInicial[200];
  sprintf(msgInicial, "J1 em %s | J2 em %s", j1.atual->nome, j2.atual->nome);
  filaEnfileirar(&logEventos, msgInicial);

  printf("Jogador 1 comecou em: %s (index %d)\n", j1.atual->nome,
         j1.atual->index);
  printf("Jogador 2 comecou em: %s (index %d)\n\n", j2.atual->nome,
         j2.atual->index);

  esperar_enter();

  int opcao;
  int vencedor = 0;               // 0 = jogo continua
  int nucleo_chegou_primeiro = 0; // 0 = ninguem, 1 = J1, 2 = J2

  while (vencedor == 0) {
    system("clear");
    // Turno jogador 1
    // checa vitoria por espera
    if (nucleo_chegou_primeiro == 1) {
      printf("\n=== Jogador 1 defendeu o NUCLEO-X e venceu o jogo! ===\n");
      filaEnfileirar(&logEventos, "VITORIA: Jogador 1 defendeu o NUCLEO-X!");
      vencedor = 1;
      esperar_enter();
      break;
    }

    printf("\n========================================\n");
    printf(" TURNO DO JOGADOR 1\n");
    printf(" Local: %s (Nivel: %d) | Vida:%d/%d Forca:%d Defesa:%d\n",
           j1.atual->nome, j1.atual->nivel, j1.vida, j1.vidaMaxima, j1.forca,
           j1.defesa);
    if (j1.atual == raiz)
      printf("!!! VOCE ESTA DEFENDENDO O NUCLEO-X. AGUENTE FIRME! !!!\n");
    printf("----------------------------------------\n");
    printf("1 - Subir ao Pai\n2 - Descer para Esquerda\n3 - Descer para "
           "Direita\n4 - "
           "Ver inventario\n5 - Usar Pocao\n0 - Sair\nEscolha: ");
    fflush(stdout);

    opcao = lerInteiro();
    if (opcao < 0) {
      printf("Entrada invalida.\n");
      esperar_enter();
      continue;
    }

    if (opcao == 0)
      break;

    // se o jogador está no nucleo, ele nao pode se mover.
    if (j1.atual == raiz) {
      printf("Voce esta defendendo o Nucleo-X e nao pode se mover!\n");
      opcao = -1; // invalida a opcao para nao fazer nada
    }

    if (opcao == 1)
      vencedor = jogadorMover(&j1, &j2, raiz, 0, &logEventos); // 0 = Pai
    else if (opcao == 2)
      vencedor = jogadorMover(&j1, &j2, raiz, 2, &logEventos); // 2 = Esquerda
    else if (opcao == 3)
      vencedor = jogadorMover(&j1, &j2, raiz, 1, &logEventos); // 1 = Direita
    else if (opcao == 4)
      inventarioListar(j1.inventario);
    else if (opcao == 5) {
      int cura = inventarioConsumirPocao(&j1.inventario);
      if (cura > 0) {
        j1.vida += cura;
        if (j1.vida > j1.vidaMaxima)
          j1.vida = j1.vidaMaxima;
        printf("Voce usou uma pocao e recuperou %d de vida!\n", cura);
      } else {
        printf("Voce nao possui nenhuma pocao de vida!\n");
      }
    } else if (opcao != -1) {
      printf("Opcao invalida.\n");
      esperar_enter();
      continue;
    }

    if (vencedor != 0) {
      esperar_enter();
      break;
    }

    // lógica de posse do Nucleo-X
    if (j1.atual == raiz && nucleo_chegou_primeiro == 0) {
      printf("\n!!! Jogador 1 alcancou o Nucleo-X! Deve esperar um turno para "
             "vencer. !!!\n");
      nucleo_chegou_primeiro = 1;
    }

    esperar_enter();
    system("clear");

    // Turno jogador 2
    // checa vitoria por espera
    if (nucleo_chegou_primeiro == 2) {
      printf("\n=== Jogador 2 defendeu o NUCLEO-X e venceu o jogo! ===\n");
      filaEnfileirar(&logEventos, "VITORIA: Jogador 2 defendeu o NUCLEO-X!");
      vencedor = 2;
      esperar_enter();
      break;
    }

    printf("\n========================================\n");
    printf(" TURNO DO JOGADOR 2\n");
    printf(" Local: %s (Nivel: %d) | Vida:%d/%d Forca:%d Defesa:%d\n",
           j2.atual->nome, j2.atual->nivel, j2.vida, j2.vidaMaxima, j2.forca,
           j2.defesa);
    if (j2.atual == raiz)
      printf("!!! VOCE ESTA DEFENDENDO O NUCLEO-X. AGUENTE FIRME! !!!\n");

    printf("----------------------------------------\n");
    printf("1 - Subir ao Pai\n2 - Descer para Esquerda\n3 - Descer para "
           "Direita\n4 - "
           "Ver inventario\n5 - Usar Pocao\n0 - Sair\nEscolha: ");
    fflush(stdout);
    opcao = lerInteiro();
    if (opcao < 0) {
      printf("Entrada invalida.\n");
      esperar_enter();
      continue;
    }

    if (opcao == 0)
      break;

    // se o jogador está no nucleo, ele nao pode se mover.
    if (j2.atual == raiz) {
      printf("Voce esta defendendo o Nucleo-X e nao pode se mover!\n");
      opcao = -1;
    }

    if (opcao == 1)
      vencedor = jogadorMover(&j2, &j1, raiz, 0, &logEventos); // 0 = Pai
    else if (opcao == 2)
      vencedor = jogadorMover(&j2, &j1, raiz, 2, &logEventos); // 2 = Esquerda
    else if (opcao == 3)
      vencedor = jogadorMover(&j2, &j1, raiz, 1, &logEventos); // 1 = Direita
    else if (opcao == 4)
      inventarioListar(j2.inventario);
    else if (opcao == 5) {
      int cura = inventarioConsumirPocao(&j2.inventario);
      if (cura > 0) {
        j2.vida += cura;
        if (j2.vida > j2.vidaMaxima)
          j2.vida = j2.vidaMaxima;
        printf("Voce usou uma pocao e recuperou %d de vida!\n", cura);
      } else {
        printf("Voce nao possui nenhuma pocao de vida!\n");
      }
    } else if (opcao != -1) {
      printf("Opcao invalida.\n");
      esperar_enter();
      continue;
    }

    if (vencedor != 0) {
      esperar_enter();
      break;
    }

    // lógica de posse do Nucleo-X
    if (j2.atual == raiz && nucleo_chegou_primeiro == 0) {
      printf("\n!!! Jogador 2 alcancou o Nucleo-X! Deve esperar um turno para "
             "vencer. !!!\n");
      nucleo_chegou_primeiro = 2;
    }

    esperar_enter();
  }

  printf("\nSalvando log de eventos...\n");
  filaSalvarLog(&logEventos, "logEventos.txt");
  filaLimpar(&logEventos);

  printf("Encerrando...\n");
  return 0;
}
