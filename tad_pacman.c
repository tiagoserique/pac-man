#include "tad_pacman.h"


struct coord *criaCoord(int linha, int coluna){
    struct coord *temp;

    temp = malloc(sizeof(struct coord));
    temp->linha  = linha;
    temp->coluna = coluna;

    return temp;
}


struct pacman *criaPacman(){

    struct pacman *temp;

    temp = malloc(sizeof(struct pacman));
    temp->vidas = VIDAS;
    temp->vivo = 1;
    temp->energizado = 0;
    temp->posicao = criaCoord(LIN_INICIAL, COL_INICIAL);

    return temp;
}


void movePacman(int direcao, struct pacman *pacman){

    switch ( direcao ){
        case KEY_UP :
            pacman->posicao->linha -= 1;
            break;


        case KEY_DOWN :
            pacman->posicao->linha += 1;
            break;
        

        case KEY_LEFT :
            pacman->posicao->coluna -= 1;
            break;
        

        case KEY_RIGHT :
            pacman->posicao->coluna += 1;
            break;
    }

    return;
}


void mostraPacman(struct pacman *pacman){
    
    int x, y;

    /* mostra o pacman inteiro caso esteja entre essas posicoes */
    if ( pacman->posicao->coluna >= 2 && pacman->posicao->coluna <= 80 ){
        for (y = pacman->posicao->linha - 1; y <= pacman->posicao->linha + 1 ; y++){
            for (x = pacman->posicao->coluna - 1; x <= pacman->posicao->coluna + 1 ; x++){
                attron( A_REVERSE | COLOR_PAIR(COR_PACMAN));
                mvprintw(y, x, " ");
                attroff(COLOR_PAIR(COR_PACMAN));
            }
        }
    }
    else
        /* caso nao esteja, ele atravessa o mapa */
        pacmanAtravessaMapa(pacman);

    return;
}


void pacmanAtravessaMapa(struct pacman *pacman){

    int x, y, temp;

    attron( A_REVERSE | COLOR_PAIR(2));

    /* faz o desenho das partes do pacman quando passa dos limites */
    if ( pacman->posicao->coluna == 81 || pacman->posicao->coluna == 0 ){
        temp = 1;
        if ( pacman->posicao->coluna == 0 )
            pacman->posicao->coluna = 81;

        for (y = pacman->posicao->linha - 1; y <= pacman->posicao->linha + 1; y++){
            for (x = pacman->posicao->coluna - 1; x <= pacman->posicao->coluna ; x++){
                mvprintw(y, x, " ");
            }

            mvprintw(y, temp, " ");
        }
    }
    else if ( pacman->posicao->coluna == 1 || pacman->posicao->coluna == 82 ){
        temp = 81;
        if ( pacman->posicao->coluna == 82 )
            pacman->posicao->coluna = 1;

        for (y = pacman->posicao->linha - 1; y <= pacman->posicao->linha + 1; y++){
            for (x = pacman->posicao->coluna; x <= pacman->posicao->coluna + 1 ; x++){
                mvprintw(y, x, " ");
            }

            mvprintw(y, temp, " ");
        }
    }

    attroff(COLOR_PAIR(2));

    return;
}


void destroiPacman(struct pacman *pacman){

    free(pacman->posicao);
    free(pacman);
    return;
}
