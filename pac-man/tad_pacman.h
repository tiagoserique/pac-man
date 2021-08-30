#include <stdlib.h>
#include <ncurses.h>


/* delay de velocidade do pacman */
#define DELAY_PACMAN 8
#define LIMITE_DELAY_PACMAN 3
#define DELAY_ENERGIZADO 990

/* definem a posicao inicial do pacman no ncurses */
#define LIN_INICIAL 41 
#define COL_INICIAL 41

#define COR_PACMAN 2
#define VIDAS 4

struct coord {

    int linha;
    int coluna;
};

struct pacman {

    struct coord *posicao; /* valor da posicao referente ao ncurses     */
    int vidas;             /* armazena quantidade de vidas do jogador   */
    int vivo;              /* 1 se vivo e 0 se fantasma tocar no pacman */
    int energizado;        /* 1 se energizado e 0 se estiver normal     */
    int tempoEnergizado;
};


/* aloca memoria para o tipo coord*/
struct coord *criaCoord(int linha, int coluna);

/* cria pacman */
struct pacman *criaPacman();

/* faz a movimentacao do pacman */
void movePacman(int direcao, struct pacman *pacman);

/* mostra o pacman */
void mostraPacman(struct pacman *pacman);

/* contem a logica para atravessar o mapa */
void pacmanAtravessaMapa(struct pacman *pacman);

/* desaloca a memoria alocada para o pacman */
void destroiPacman(struct pacman *pacman);
