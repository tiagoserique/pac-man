#include "tad_pacman.h"


void movePacman(int direcao, struct pacman *pacman){

    switch ( direcao ){
        case KEY_UP :
            pacman->posiLin -= 1;
            break;

        case KEY_DOWN :
            pacman->posiLin += 1;
            break;
        
        case KEY_LEFT :
            pacman->posiCol -= 1;
            break;
        
        case KEY_RIGHT :
            pacman->posiCol += 1;
            break;
    }

    return;
}


void mostraPacman(struct pacman *pacman){
    
    int x, y;

    /* mostra o pacman inteiro caso esteja entre essas posicoes */
    if ( pacman->posiCol >= 2 && pacman->posiCol <= 80 ){

        for (y = pacman->posiLin - 1; y <= pacman->posiLin + 1 ; y++){
            for (x = pacman->posiCol - 1; x <= pacman->posiCol + 1 ; x++){
                attron( A_REVERSE | COLOR_PAIR(2));
                mvprintw(y, x, " ");
                attroff(COLOR_PAIR(2));
            }
        }
    }
    else
        /* caso nao esteja, ele atravessa o mapa */
        pacmanAtravessaMapa(pacman);

    return;
}


struct pacman *criaPacman(){

    struct pacman *temp;

    temp = malloc(sizeof(struct pacman));
    temp->tamanho = TAM_PACMAN;
    temp->vidas = VIDAS;
    temp->vivo = 1;

    return temp;
}


void pacmanAtravessaMapa(struct pacman *pacman){

    int x, y, temp;

    attron( A_REVERSE | COLOR_PAIR(2));

    /* faz o desenho das partes do pacman quando passa dos limites */
    if ( pacman->posiCol == 81 || pacman->posiCol == 0 ){

        temp = 1;
        if ( pacman->posiCol == 0 )
            pacman->posiCol = 81;

        for (y = pacman->posiLin - 1; y <= pacman->posiLin + 1; y++){
            for (x = pacman->posiCol - 1; x <= pacman->posiCol ; x++){
                mvprintw(y, x, " ");
            }

            mvprintw(y, temp, " ");
        }
    }
    else if ( pacman->posiCol == 1 || pacman->posiCol == 82 ){

        temp = 81;
        if ( pacman->posiCol == 82 )
            pacman->posiCol = 1;

        for (y = pacman->posiLin - 1; y <= pacman->posiLin + 1; y++){
            for (x = pacman->posiCol; x <= pacman->posiCol + 1 ; x++){
                mvprintw(y, x, " ");
            }

            mvprintw(y, temp, " ");
        }
    }

    attroff(COLOR_PAIR(2));

    return;
}
