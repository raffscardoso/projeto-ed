#include "jogo.h"
#include "fila.h"
#include <stdio.h>
#include <string.h>

// leitura segura de inteiro via fgets
int lerInteiro() {
  char buffer[64];
  if (!fgets(buffer, sizeof(buffer), stdin))
    return -1;
  int inteiroLido = 0;
  if (sscanf(buffer, "%d", &inteiroLido) != 1)
    return -1;
  return inteiroLido;
}

// jogador
void jogadorInicializar(Jogador *j, int id, No *inicio) {
  j->id = id;
  j->atual = inicio;

  // Marca o nó como ocupado
  if (inicio)
    inicio->ocupado = id;

  // Histórico vazio
  pilhaInicializar(&j->historico);

  // Zera visitados
  for (int i = 0; i < 4; i++) {
    j->visitados[i] = 0;
  }

  // atributos iniciais
  j->vidaMaxima = 100;
  j->vida = j->vidaMaxima;
  j->forca = 10;
  j->defesa = 5;
  j->inventario = NULL;
  j->chave = 0;

  // Marca o primeiro nó como visitado
  jogadorVisitarNo(j, inicio);
}

void jogadorVisitarNo(Jogador *j, No *no) {
  if (!no)
    return;

  int nivel = no->nivel;
  j->visitados[nivel] += 1;

  // coloca no histórico
  pilhaPush(&j->historico, no);
}

No *obterNoDestino(No *raiz, Jogador *j, int direcao) {
  if (!j || !j->atual)
    return NULL;

  // 0 = subir, 1 = direita, 2 = esquerda
  if (direcao == 0) {
    return j->atual->pai;
  } else if (direcao == 1) {
    return j->atual->dir;
  } else if (direcao == 2) {
    return j->atual->esq;
  }

  return NULL;
}

// batalha por turnos
int batalhaContraInimigo(Jogador *j, int poderInimigo) {
  printf("\n--- BATALHA INICIADA ---\n");
  printf(
      "Inimigo (Poder: %d) vs Jogador %d (Vida: %d, Forca: %d, Defesa: %d)\n",
      poderInimigo, j->id, j->vida, j->forca, j->defesa);

  int vidaInimigo = poderInimigo * 3;

  while (j->vida > 0 && vidaInimigo > 0) {
    // turno do Jogador
    // dano base = Forca, com variação aleatória (-5 a +5)
    int variacao = (rand() % 11) - 5;
    int danoJogador = j->forca + variacao;

    // dano minimo
    if (danoJogador < 1)
      danoJogador = 1;

    vidaInimigo -= danoJogador;
    char *mensagensAtaqueJogador[] = {
        ">> Voce desfere um golpe certeiro! Dano: %d | Inimigo HP: %d\n",
        ">> Sua arma encontra o alvo! Dano: %d | Inimigo HP: %d\n",
        ">> Um ataque fulminante! Dano: %d | Inimigo HP: %d\n"};
    printf(mensagensAtaqueJogador[rand() % 3], danoJogador, vidaInimigo);

    // vitoria do jogador
    if (vidaInimigo <= 0)
      break;

    // turno do Inimigo
    variacao = (rand() % 11) - 5;
    int danoInimigo = (poderInimigo / 2 - j->defesa) + variacao;
    if (danoInimigo < 0)
      danoInimigo = 0;

    j->vida -= danoInimigo;
    char *mensagensAtaqueInimigo[] = {
        "<< O inimigo contra-ataca! Dano: %d | Jogador HP: %d\n",
        "<< Voce e atingido! Dano: %d | Jogador HP: %d\n",
        "<< Um golpe brutal do inimigo! Dano: %d | Jogador HP: %d\n"};
    printf(mensagensAtaqueInimigo[rand() % 3], danoInimigo, j->vida);
  }

  if (j->vida > 0) {
    return 1;
  } else {
    return 0;
  }
}

void resolverEncontroComum(Jogador *j, No *destino, Fila *log) {
  char buffer[256];
  if (!j || !destino)
    return;
  printf("\n!!! ENCONTRO DE BATALHA !!!\n");
  printf("Ao adentrar %s, Jogador %d foi surpreendido por um inimigo!\n",
         destino->nome, j->id);

  // determina força do inimigo com base no nível do território
  int poderInimigo = 10 + (3 - destino->nivel) * 10;

  printf("Poder do inimigo: %d | Forca do jogador: %d\n", poderInimigo,
         j->forca);

  int resultado = batalhaContraInimigo(j, poderInimigo);

  if (resultado) {
    printf("\n*** VITORIA! ***\n");
    printf("Jogador %d derrota o inimigo em %s! Vida restante: %d/%d\n", j->id,
           destino->nome, j->vida, j->vidaMaxima);
    j->atual->ocupado = 0;
    destino->ocupado = j->id;
    j->atual = destino;

    jogadorVisitarNo(j, destino);
    sprintf(buffer, "Jogador %d venceu batalha em %s. Vida restante: %d", j->id,
            destino->nome, j->vida);
    filaEnfileirar(log, buffer);

  } else {
    printf("\n--- DERROTA --- \n");
    printf("Jogador %d foi humilhado em %s e perde a batalha!\n", j->id,
           destino->nome);
    printf("Exausto, Jogador %d permanece em %s, reunindo suas forcas e "
           "recuperando parte da vida.\n",
           j->id, j->atual->nome);

    if (j->vida <= 0)
      j->vida = 30; // recupera vida apos desmaio
    sprintf(buffer,
            "Jogador %d perdeu batalha em %s. Permanece em %s. Vida: %d", j->id,
            destino->nome, j->atual->nome, j->vida);
    filaEnfileirar(log, buffer);
  }
}

// altera a assinatura e adiciona logs
int jogadorMover(Jogador *j, Jogador *outro, No *raiz, int direcao, Fila *log) {
  char buffer[256];

  No *destino = obterNoDestino(raiz, j, direcao);

  if (!destino) {
    char *mensagensInvalido[] = {
        "Nao ha caminho por ali... A parede e solida.",
        "Um abismo intransponivel bloqueia essa direcao.",
        "A passagem esta desmoronada. Nao e possivel avancar.",
        "Voce encontra um emaranhado de vinhas e espinhos. Impossivel "
        "prosseguir."};
    printf("Jogador %d: %s\n", j->id, mensagensInvalido[rand() % 4]);
    sprintf(buffer, "[FALHA] Jogador %d tentou mover em direcao invalida.",
            j->id);
    filaEnfileirar(log, buffer);
    return 0;
  }

  if (strcmp(destino->nome, "Nucleo-X") == 0) {
    int total_visitados = 0;
    for (int i = 0; i < 4; i++) {
      total_visitados += j->visitados[i];
    }

    // se o jogador nao visitou pelo menos 4 nós, ele nao poderá subir para o
    // Nucleo-X
    if (total_visitados < 4) {
      printf("Jogador %d: Voce precisa explorar mais o mapa (pelo menos 4 "
             "areas) antes de tentar acessar o Nucleo-X!\n",
             j->id);
      sprintf(buffer,
              "[FALHA] Jogador %d tentou acessar o Nucleo-X sem explorar o "
              "suficiente.",
              j->id);
      filaEnfileirar(log, buffer);
      return 0;
    }
  }

  // log de movimento para debug
  sprintf(buffer, "Jogador %d moveu-se para %s (Tipo: %d)", j->id,
          destino->nome, destino->tipo);
  filaEnfileirar(log, buffer);

  // checa o Nucleo-X e verifica se o outro jogador esta la para um duelo
  if (strcmp(destino->nome, "Nucleo-X") == 0 && destino->ocupado == outro->id) {
    sprintf(buffer, "[DUELO FINAL] Jogador %d encontrou Jogador %d em %s!",
            j->id, outro->id, destino->nome);
    filaEnfileirar(log, buffer);

    return resolverDuelo(j, outro, destino, raiz); // Retorna o vencedor
  }

  // logica do nó de batalha
  if (destino->tipo == BATALHA) {
    sprintf(buffer, "[BATALHA] Jogador %d entrou em zona de perigo %s", j->id,
            destino->nome);
    filaEnfileirar(log, buffer);
    resolverEncontroComum(j, destino, log);
    return 0; // resolverEncontroComum handles movement if player wins
  }

  // Se o nó estiver ocupado pelo outro jogador (e não for Nucleo-X), impede o
  // movimento
  if (destino->ocupado == outro->id) {
    printf("Jogador %d: O caminho para %s esta bloqueado pelo outro jogador!\n",
           j->id, destino->nome);
    sprintf(buffer,
            "[FALHA] Jogador %d tentou mover para %s, mas estava ocupado pelo "
            "Jogador %d.",
            j->id, destino->nome, outro->id);
    filaEnfileirar(log, buffer);
    return 0;
  }

  // Se o nó estiver livre, realiza o movimento
  j->atual->ocupado = 0;
  destino->ocupado = j->id;
  j->atual = destino;
  jogadorVisitarNo(j, destino);

  // nó de recurso
  if (destino->tipo == RECURSO) {
    int rng = rand() % 100;
    ItemTipo tipoItem;
    int valorItem = 0;
    char nomeItem[50];

    if (rng < 40) { // 40% Pocao
      tipoItem = ITEM_POCAO;
      valorItem = 20 + (rand() % 21); // 20-40 HP
      sprintf(nomeItem, "Pocao de Vida");
    } else if (rng < 65) { // 25% Arma
      tipoItem = ITEM_ARMA;
      valorItem = 3 + (rand() % 6); // 3-8 Forca
      sprintf(nomeItem, "Espada Longa");
    } else if (rng < 85) { // 20% Armadura
      tipoItem = ITEM_ARMADURA;
      valorItem = 2 + (rand() % 5); // 2-6 Defesa
      sprintf(nomeItem, "Escudo de Aco");
    } else { // 15% Amuleto
      tipoItem = ITEM_AMULETO;
      valorItem = 15 + (rand() % 16); // 15-30 Vida Max/Atual
      sprintf(nomeItem, "Amuleto Antigo");
    }

    inventarioAdicionar(&j->inventario, tipoItem, valorItem);

    if (tipoItem != ITEM_POCAO) {
      inventarioAplicarAoJogador(j->inventario, j);
      printf("Item equipado automaticamente!\n");
    } else {
      printf("Poção guardada no inventário.\n");
    }

    printf("\n*** AREA DE RECURSO! ***\n");
    printf("Enquanto explorava %s, Jogador %d encontrou algo cintilante...\n",
           destino->nome, j->id);
    printf("Ao investigar mais de perto, revelou-se um bau antigo!\n");
    printf("Dentro dele havia: %s (+%d)!\n", nomeItem, valorItem);

    sprintf(buffer, "Jogador %d pegou %s (+%d) em %s", j->id, nomeItem,
            valorItem, destino->nome);
    filaEnfileirar(log, buffer);

    // consome o recurso, transformando o nó em tipo normal
    destino->tipo = NORMAL;
  } else if (destino->tipo == NORMAL) {
    char *mensagensNormal[] = {
        "O ar aqui e denso, mas nao ha perigo aparente. Voce segue adiante.",
        "A passagem se estreita e depois se abre em uma caverna vazia. Tudo "
        "calmo.",
        "Rochas umidas e um eco distante. Nenhum sinal de presenca inimiga.",
        "Uma area estranhamente serena. Bom para um breve descanso, mas você "
        "não tem tempo para isso."};

    int mensagemNormalSorteada = rand() % 4;
    printf("\n--- CAMINHO SEGURO ---\n");
    printf("%s\n", mensagensNormal[mensagemNormalSorteada]);

    sprintf(buffer, "Jogador %d avancou em seguranca para %s.", j->id,
            destino->nome);
    filaEnfileirar(log, buffer);
  }
  return 0; // Jogo continua
}

int resolverDuelo(Jogador *j1, Jogador *j2, No *destino, No *raiz) {
  printf("\n!!! DUELO FINAL NO NUCLEO-X !!!\n");
  printf("Os olhares se cruzam: Jogador %d desafia Jogador %d!\n", j1->id,
         j2->id);

  // Lógica de batalha simplificada
  int poderJ1 = j1->forca + j1->defesa + j1->vida;
  int poderJ2 = j2->forca + j2->defesa + j2->vida;
  int vencedor = (poderJ1 > poderJ2) ? j1->id : j2->id;

  printf("\nO combate final comeca!\n");

  if (vencedor == j1->id) {
    printf("\n*** Jogador %d domina o duelo e conquista o Nucleo-X! ***\n",
           j1->id);
    printf("VITORIA PARA O JOGADOR %d!\n", j1->id);
  } else {
    printf("\n*** Jogador %d domina o duelo e conquista o Nucleo-X! ***\n",
           j2->id);
    printf("VITORIA PARA O JOGADOR %d!\n", j2->id);
  }

  printf("\n=== O JOGO CHEGA AO FIM ===\n\n");

  // retorna o ID do vencedor
  return vencedor;
}
void inventarioAplicarAoJogador(Item *it, Jogador *j) {
  if (!it || !j)
    return;
  if (it->tipo == ITEM_ARMADURA)
    j->defesa += it->valor;
  else if (it->tipo == ITEM_ARMA)
    j->forca += it->valor;
  else if (it->tipo == ITEM_AMULETO)
    j->vidaMaxima += it->valor; // amuleto aumenta vida maxima
}
