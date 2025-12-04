# CodeBattle

**CodeBattle** é um jogo de estratégia por turnos para dois jogadores (local), desenvolvido em **Linguagem C**. O jogo decorre num mapa estruturado como uma **Árvore Binária**, onde os jogadores devem explorar nós, combater inimigos, recolher recursos e competir para conquistar o "Núcleo-X".

Este projeto foi desenhado para demonstrar a aplicação prática de várias Estruturas de Dados fundamentais proposto como Projeto do 3° Crédito da matéria **Estrutura de Dados 2025.2** no curso de Ciência da Computação da Universidade Estadual de Santa Cruz (UESC).

## Funcionalidades e Mecânicas

* **Mapa em Árvore:** O mundo do jogo é gerado como uma árvore binária de 3 níveis.
* **Multijogador Local:** Dois jogadores alternam turnos no mesmo terminal.
* **Sistema de Combate (PvE):** Batalhas contra inimigos gerados aleatoriamente em nós do tipo "Batalha".
* **Sistema de Loot:** Recolha de itens (Armas, Armaduras, Poções, Amuletos) em nós de "Recurso" para melhorar os atributos (Força, Defesa, Vida).
* **Duelo Final (PvP):** Se ambos os jogadores se encontrarem no Núcleo-X, inicia-se um duelo final.
* **Log de Eventos:** Registo de todas as ações importantes num ficheiro de texto (`logEventos.txt`) utilizando uma Fila.

## Estruturas de Dados Utilizadas

O núcleo do projeto baseia-se na manipulação eficiente das seguintes estruturas:

1.  **Árvore Binária (`lib/arvore.c`):** Representa o mapa do jogo. Cada nó é uma área que pode ser explorada.
2.  **Fila (`lib/fila.c`):** Utilizada para gerir o sistema de logs. As mensagens são enfileiradas durante o jogo e gravadas em ficheiro no final.
3.  **Pilha (`lib/pilha.c`):** Utilizada para armazenar o histórico de movimentos de cada jogador (caminho percorrido).
4.  **Lista Ligada (`lib/lista.c`):** Implementa o inventário dinâmico dos jogadores, permitindo adicionar e remover itens ilimitados.

## Como Compilar e Executar

O projeto inclui um `Makefile` para automatizar o processo de build. Certifique-se de que tem o `gcc` e o `make` instalados.

### Comandos Principais

* **Compilar o projeto:**
    ```bash
    make
    ```
    Isto irá gerar os objetos na pasta `obj/` e o executável `bin/jogo`.

* **Executar o jogo:**
    ```bash
    make run
    ```
    Este comando compila (se necessário) e inicia o jogo imediatamente.

* **Limpar ficheiros temporários:**
    ```bash
    make clean
    ```
    Remove as pastas `obj/`, `bin/` e ficheiros de log antigos.

## Como Jogar

### Objetivo
O objetivo principal é alcançar e defender o **Núcleo-X** (a raiz da árvore).

### Regras
1.  **Início:** Os jogadores começam nas "folhas" da árvore (Nível 3).
2.  **Requisito de Entrada:** Para aceder ao Núcleo-X, o jogador deve ter explorado pelo menos **4 áreas distintas** do mapa.
3.  **Movimento:**
    * **Subir ao Pai:** Move-se em direção à raiz.
    * **Descer (Esq/Dir):** Move-se para os filhos do nó atual.
4.  **Vencer o Jogo:** Existem duas formas de vencer:
    * Chegar ao Núcleo-X primeiro e, no turno seguinte, não ser desafiado (vitória por defesa).
    * Vencer o duelo contra o outro jogador caso ambos se encontrem no Núcleo-X.

### Controlos
Durante o turno, utilize os números apresentados no menu:
* `1`: Mover para cima (Pai)
* `2`: Mover para a esquerda (Filho)
* `3`: Mover para a direita (Filho)
* `4`: Ver inventário
* `5`: Usar Poção de Vida
* `0`: Sair do jogo

## Estrutura de Ficheiros

```text
.
├── Makefile           # Script de compilação
├── README.md          # Documentação do projeto
├── bin/               # Executável gerado
├── lib/               # Implementação das Estruturas de Dados (ADT)
│   ├── arvore.c/h
│   ├── fila.c/h
│   ├── jogo.c/h       # Lógica principal do jogo
│   ├── lista.c/h
│   └── pilha.c/h
├── obj/               # Ficheiros objeto (.o)
└── src/               # Código fonte principal
    └── main.c         # Loop principal e menus
```
## Desenvolvido por
- [Arthur Ramos Vieira](https://github.com/arthun01)
- [Rafael Cardoso Silva Santos](https://github.com/raffscardoso)
- [Pedro Sergio Martins Lima](https://github.com/PedroNTC1)
