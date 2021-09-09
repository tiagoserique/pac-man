#include <stdlib.h>
#include <ncurses.h>

#define PACMAN 0100
#define SIZE_PACMAN 3
#define LIFES 4

struct pacman {
    int size; 
    int columnPosition; /* valor da posicao referente ao ncurses */
    int rowPosition; /* valor da posicao referente ao ncurses */
    int lifes;
    int alive;
};


/* faz a movimentacao do pacman */
void movePacman(int direction, struct pacman *pacman);

/* mostra o pacman */
void showPacman(struct pacman *pacman);

/* cria pacman */
struct pacman *createPacman();

/* contem a logica para atravessar o mapa */
void pacmanThroughTheMap(struct pacman *pacman);
