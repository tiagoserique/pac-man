#include <stdlib.h>
#include <ncurses.h>
#include "tad_pacman.h"

#define BLINKY 010
#define PINKY  020
#define INKY   030
#define CLYDE  040

#define COR_BLINKY 1
#define COR_CLYDE  3
#define COR_PINKY  8
#define COR_INKY   6

struct fantasma {

    int posiLin; /* valor da posicao referente ao ncurses           */
    int posiCol; /* valor da posicao referente ao ncurses           */
    int fugir;   /* 1 se estiver fugindo, 0 se estiver perseguindo  */
    int id;      /* identifica qual eh o fantasma                   */
};

/* cria fantasma vermelho */
struct fantasma *criaBlinky();

/* cria fantasma rosa */
struct fantasma *criaPinky();

/* cria fantasma azul */
struct fantasma *criaInky();

/* cria fantasma amarelo */
struct fantasma *criaClyde();

/* exibe o fantasma na tela */
void mostraFantasma(struct fantasma *fantasma);

/* faz o fantasma atravessar o mapa */
void fantasmaAtravessaMapa(struct fantasma *fantasma, int atributo);

/* posiciona fantasmas */