#include <time.h>
#include <unistd.h>
#include "tad_pacman.h"
#include "tad_lde.h"

#define BLINKY 010
#define PINKY  020
#define INKY   030
#define CLYDE  040

#define COR_BLINKY 1
#define COR_CLYDE  3
#define COR_PINKY  8
#define COR_INKY   6

#define DELAY_FANTASMAS 9
#define LIMITE_DELAY_FANTASMAS 3

struct fantasma {

    int id;                   /* identifica qual eh o fantasma */

    struct coord *alvo;       /* valor da posicao do alvo referente ao ncurses */
    struct coord *posicao;    /* valor da posicao do fantasma referente ao ncurses */

    int fugir;                /* 1 se estiver fugindo, 0 se estiver perseguindo */
    int comido;               /* 1 se foi comido, 0 se nao */

    struct lista *direcoesDisponiveis; /* lista uasda para as posicoes disponiveis */
    int dirAtual;             /* direcao em que ele estava seguindo */
};

/* cria fantasma */
struct fantasma *criaFantasma(int id, int linhaInicial, int colunaInicial);

/* exibe o fantasma na tela */
void mostraFantasma(struct fantasma *fantasma);

/* faz o fantasma atravessar o mapa */
void fantasmaAtravessaMapa(struct fantasma *fantasma, int atributo);

/* define o alvo de cada fantasma */
void defineAlvos(struct fantasma *fantasma, struct pacman *pacman, 
int direcaoPacman);

/* faz a escolha de que direcao seguir */
int escolheDirecao(struct fantasma *fantasma, struct pacman *pacman, 
int direcaoPacman);

/* retorna a direcao com a menor distancia ate o alvo*/
int direcaoComMenorDistancia(struct fantasma *fantasma);

/* calcula a distancia entre a proxima posicao do fantasma e o alvo */
int calculaDistancia(int linha, int coluna, int linhaAlvo, int colunaAlvo);

/* faz a movimentacao do fantasma */
void moveFantasma(struct fantasma *fantasma, int direcao);

/* reinicia posicao dos fantasmas */
void reiniciaPosicaoFantasma(struct fantasma *fantasma);

/* verifica e faz as alteracoes necessarias quando o fantasma foi comido */
int foiComido(struct fantasma *fantasma);

/* define o comportamento dos fantasmas */
void fogeOuPersegue(struct fantasma *fantasma, struct pacman *pacman);

/* destroi fantasma */
void destroiFantasma(struct fantasma *fantasma);
