#include "jogo.h"

// leitura segura de inteiro via fgets
int lerInteiro() {
  char buf[64];
  if (!fgets(buf, sizeof(buf), stdin))
    return -1;
  int v = 0;
  if (sscanf(buf, "%d", &v) != 1)
    return -1;
  return v;
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
  j->vida = 100;
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

  // subir para o pai
  if (direcao == 2) {
    return obterNoPai(raiz, j);
  }

  int idx = j->atual->index;
  int nivel = j->atual->nivel;

  int inicio = 1 << nivel;
  int fim = (1 << (nivel + 1)) - 1;

  int novoIdx = idx + direcao;

  if (novoIdx < inicio || novoIdx > fim)
    return NULL;

  return arvoreBuscarPorIndice(raiz, novoIdx);
}

No *obterNoPai(No *raiz, Jogador *j) {
  if (!j || !j->atual)
    return NULL;
  if (j->atual->index == 1)
    return NULL; // já é raiz
  return arvoreEncontrarPai(raiz, j->atual);
}

int batalhaContraInimigo() {
  // Exemplo simples: 50% vitória, 50% derrota
  return rand() % 2;
}

void resolverEncontroComum(Jogador *j, No *destino) {
  if (!j || !destino)
    return;
  printf("Jogador %d encontrou um inimigo no no de batalha!\n", j->id);

  // determinar força do inimigo com base no nível do território
  int poderInimigo = 10 + destino->nivel * 10; // nível 0..3

  printf("Poder do inimigo: %d | Forca do jogador: %d\n", poderInimigo,
         j->forca);

  // Se o jogador não tem força suficiente, falha automaticamente
  if (j->forca < poderInimigo) {
    printf("Jogador %d NAO tem forca suficiente e falha na batalha!\n", j->id);
    printf("Jogador %d permanece em %s\n", j->id, j->atual->nome);
    return;
  }

  // Caso tenha força suficiente, resolve aleatoriamente com vantagem do jogador
  int resultado = batalhaContraInimigo();
  if (resultado) {
    printf("Jogador %d venceu o inimigo!\n", j->id);
    j->atual->ocupado = 0;
    destino->ocupado = j->id;
    j->atual = destino;
    jogadorVisitarNo(j, destino);
  } else {
    printf("Jogador %d perdeu a batalha mesmo com força suficiente!\n", j->id);
    printf("Jogador %d permanece em %s\n", j->id, j->atual->nome);
  }
}

// Altera a assinatura e adiciona logs
void jogadorMover(Jogador *j, Jogador *outro, No *raiz, int direcao, Fila* log) {
    char buffer[256]; // Buffer para formatar as mensagens

    // Regra de subir nível
    if (direcao == 2) {
        int nivel = j->atual ? j->atual->nivel : 0;
        int totalNosNoNivel = 1 << nivel;
        if (!j->chave && j->visitados[nivel] < totalNosNoNivel) {
            printf("Jogador %d NAO pode subir...\n", j->id);
            
            // LOG
            sprintf(buffer, "[FALHA] Jogador %d tentou subir mas nao tem chave.", j->id);
            filaEnfileirar(log, buffer);
            return;
        }
    }

    No *destino = obterNoDestino(raiz, j, direcao);

    if (!destino) {
        printf("Jogador %d nao pode mover nessa direcao.\n", j->id);
        return;
    }

    // LOG DE MOVIMENTO
    sprintf(buffer, "Jogador %d moveu-se para %s (Tipo: %d)", j->id, destino->nome, destino->tipo);
    filaEnfileirar(log, buffer);

    // Se nó está ocupado pelo outro jogador -> Duelo
    if (destino->ocupado == outro->id) {
        sprintf(buffer, "[DUELO] Jogador %d encontrou Jogador %d em %s!", j->id, outro->id, destino->nome);
        filaEnfileirar(log, buffer);
        
        resolverDuelo(j, outro, destino, raiz); // Se quiseres podes passar log para dentro do duelo também
        return;
    }

    // Se nó é recurso
    if (destino->tipo == RECURSO) {
        // ... (código existente de gerar item) ...
        // Quando ele pega o item:
        // sprintf(buffer, "Jogador %d coletou um item em %s", j->id, destino->nome);
        // filaEnfileirar(log, buffer);
        
        // ... (Mantém a tua lógica original de RECURSO, apenas adiciona logs onde achares fixe)
    }

    // Se nó é batalha
    if (destino->tipo == BATALHA) {
        sprintf(buffer, "[BATALHA] Jogador %d entrou em zona de perigo %s", j->id, destino->nome);
        filaEnfileirar(log, buffer);
        resolverEncontroComum(j, destino);
        return;
    }

    // Caminho livre
    if (destino->ocupado == 0) {
        j->atual->ocupado = 0;
        destino->ocupado = j->id;
        j->atual = destino;
        jogadorVisitarNo(j, destino);
        printf("Jogador %d se moveu para %s.\n", j->id, destino->nome);
    }
}

void resolverDuelo(Jogador *j1, Jogador *j2, No *destino, No *raiz) {
  printf("\n=== DUELO ===\n");
  printf("Jogador %d encontrou o Jogador %d no nó %s\n", j1->id, j2->id,
         destino->nome);

  // exemplo simples: 50% de chance de cada um vencer
  int vencedor = (rand() % 2) ? j1->id : j2->id;

  if (vencedor == j1->id) {
    printf("Jogador %d venceu o duelo!\n", j1->id);

    // Jogador 1 toma o nó
    j2->atual->ocupado = 0; // o perdedor sai do nó
    destino->ocupado = j1->id;
    j1->atual = destino;
    jogadorVisitarNo(j1, destino);

    // Jogador 2 é penalizado ↓↓↓
    if (j2->atual->nivel > 0) {
      // cair um nível
      int idx = j2->atual->index;
      int idxPai = idx / 2;
      No *novo = arvoreBuscarPorIndice(raiz, idxPai);
      if (novo) {
        j2->atual = novo;
        j2->atual->ocupado = j2->id;
        printf("Jogador %d caiu para o nível %d (nó %s)\n", j2->id, novo->nivel,
               novo->nome);
      }
    } else {
      // penalidade no nível 0 → manda para nó extremo
      No *novo = arvoreBuscarPorIndice(raiz, 15);
      j2->atual = novo;
      j2->atual->ocupado = j2->id;
      printf("Jogador %d perdeu e foi enviado para o nó %s\n", j2->id,
             novo->nome);
    }

  } else {
    printf("Jogador %d venceu o duelo!\n", j2->id);

    // Jogador 2 toma o nó
    j1->atual->ocupado = 0;
    destino->ocupado = j2->id;
    j2->atual = destino;
    jogadorVisitarNo(j2, destino);

    // Jogador 1 recebe penalidade ↓↓↓
    if (j1->atual->nivel > 0) {
      int idx = j1->atual->index;
      int idxPai = idx / 2;
      No *novo = arvoreBuscarPorIndice(raiz, idxPai);
      if (novo) {
        j1->atual = novo;
        j1->atual->ocupado = j1->id;
        printf("Jogador %d caiu para o nível %d (nó %s)\n", j1->id, novo->nivel,
               novo->nome);
      }
    } else {
      No *novo = arvoreBuscarPorIndice(raiz, 8);
      j1->atual = novo;
      j1->atual->ocupado = j1->id;
      printf("Jogador %d foi enviado para o nó %s\n", j1->id, novo->nome);
    }
  }

  printf("=== FIM DO DUELO ===\n\n");
}

void inventarioAplicarAoJogador(Item *it, Jogador *j) {
  if (!it || !j)
    return;
  if (it->tipo == ITEM_ARMADURA)
    j->defesa += it->valor;
  else if (it->tipo == ITEM_ARMA)
    j->forca += it->valor;
  else if (it->tipo == ITEM_AMULETO)
    j->vida += it->valor;
}
