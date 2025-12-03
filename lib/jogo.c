#include "jogo.h"

// jogador
void jogadorInicializar(Jogador* j, int id, No* inicio) {
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

    // Marca o primeiro nó como visitado
    jogadorVisitarNo(j, inicio);
}

void jogadorVisitarNo(Jogador* j, No* no) {
    if (!no) return;

    int nivel = no->nivel;
    j->visitados[nivel] += 1;

    // coloca no histórico
    pilhaPush(&j->historico, no);
}

No* obterNoDestino(No* raiz, Jogador* j, int direcao) {
    int idx = j->atual->index;
    int nivel = j->atual->nivel;

    int inicio = 1 << nivel;
    int fim = (1 << (nivel + 1)) - 1;

    int novoIdx = idx + direcao;

    if (novoIdx < inicio || novoIdx > fim)
        return NULL;

    return arvoreBuscarPorIndice(raiz, novoIdx);
}

int batalhaContraInimigo() {
    // Exemplo simples: 50% vitória, 50% derrota
    return rand() % 2;
}

void resolverEncontroComum(Jogador* j, No* destino) {
    printf("Jogador %d encontrou um inimigo no território de batalha!\n", j->id);

    if (batalhaContraInimigo()) {
        printf("Jogador %d venceu o inimigo!\n", j->id);

        j->atual->ocupado = 0;
        destino->ocupado = j->id;
        j->atual = destino;
        jogadorVisitarNo(j, destino);

    } else {
        printf("Jogador %d perdeu a batalha!\n", j->id);

        // Volta ao nó anterior
        No* anterior = pilhaPop(&j->historico);
        if (anterior) {
            j->atual = anterior;
        }
    }
}

void jogadorMover(Jogador* j, Jogador* outro, No* raiz, int direcao) {
    No* destino = obterNoDestino(raiz, j, direcao);

    if (!destino) {
        printf("Jogador %d não pode mover nessa direção.\n", j->id);
        return;
    }

    // Se nó está ocupado pelo outro jogador → duelo
    if (destino->ocupado == outro->id) {
        resolverDuelo(j, outro, destino, raiz);
        return;
    }

    // Se nó é batalha → inimigo comum
    if (destino->tipo == BATALHA) {
        resolverEncontroComum(j, destino);
        return;
    }

    // Caminho livre — movimento simples
    if (destino->ocupado == 0) {
        j->atual->ocupado = 0;
        destino->ocupado = j->id;
        j->atual = destino;
        jogadorVisitarNo(j, destino);
        printf("Jogador %d se moveu para %s.\n", j->id, destino->nome);
    }
}

void resolverDuelo(Jogador* j1, Jogador* j2, No* destino, No* raiz) {
    printf("\n=== DUELO ===\n");
    printf("Jogador %d encontrou o Jogador %d no nó %s\n",
           j1->id, j2->id, destino->nome);

    // exemplo simples: 50% de chance de cada um vencer
    int vencedor = (rand() % 2) ? j1->id : j2->id;

    if (vencedor == j1->id) {
        printf("Jogador %d venceu o duelo!\n", j1->id);

        // Jogador 1 toma o nó
        j2->atual->ocupado = 0;     // o perdedor sai do nó
        destino->ocupado = j1->id;
        j1->atual = destino;
        jogadorVisitarNo(j1, destino);

        // Jogador 2 é penalizado ↓↓↓
        if (j2->atual->nivel > 0) {
            // cair um nível
            int idx = j2->atual->index;
            int idxPai = idx / 2;
            No* novo = arvoreBuscarPorIndice(raiz, idxPai);
            if (novo) {
                j2->atual = novo;
                j2->atual->ocupado = j2->id;
                printf("Jogador %d caiu para o nível %d (nó %s)\n",
                       j2->id, novo->nivel, novo->nome);
            }
        } else {
            // penalidade no nível 0 → manda para nó extremo
            No* novo = arvoreBuscarPorIndice(raiz, 15);
            j2->atual = novo;
            j2->atual->ocupado = j2->id;
            printf("Jogador %d perdeu e foi enviado para o nó %s\n",
                   j2->id, novo->nome);
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
            No* novo = arvoreBuscarPorIndice(raiz, idxPai);
            if (novo) {
                j1->atual = novo;
                j1->atual->ocupado = j1->id;
                printf("Jogador %d caiu para o nível %d (nó %s)\n",
                       j1->id, novo->nivel, novo->nome);
            }
        } else {
            No* novo = arvoreBuscarPorIndice(raiz, 8);
            j1->atual = novo;
            j1->atual->ocupado = j1->id;
            printf("Jogador %d foi enviado para o nó %s\n",
                   j1->id, novo->nome);
        }
    }

    printf("=== FIM DO DUELO ===\n\n");
}
