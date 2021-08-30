#include <stdlib.h>
#include <ncurses.h>

#define PACMAN 0100
#define TAM_PACMAN 3
#define VIDAS 4

struct pacman {

    int tamanho; 
    int posiCol; /* valor da posicao referente ao ncurses */
    int posiLin; /* valor da posicao referente ao ncurses */
    int vidas;
    int vivo;
};


/* faz a movimentacao do pacman */
void movePacman(int direcao, struct pacman *pacman);

/* mostra o pacman */
void mostraPacman(struct pacman *pacman);

/* cria pacman */
struct pacman *criaPacman();

/* contem a logica para atravessar o mapa */
void pacmanAtravessaMapa(struct pacman *pacman);
