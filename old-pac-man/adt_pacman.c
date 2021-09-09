#include "adt_pacman.h"


void movePacman(int direction, struct pacman *pacman){

    switch ( direction ){
        case KEY_UP :
            pacman->rowPosition -= 1;
            break;

        case KEY_DOWN :
            pacman->rowPosition += 1;
            break;
        
        case KEY_LEFT :
            pacman->columnPosition -= 1;
            break;
        
        case KEY_RIGHT :
            pacman->columnPosition += 1;
            break;
    }

    return;
}


void showPacman(struct pacman *pacman){
    
    int x, y;

    /* mostra o pacman inteiro caso esteja entre essas posicoes */
    if ( pacman->columnPosition >= 2 && pacman->columnPosition <= 80 ){

        for (y = pacman->rowPosition - 1; y <= pacman->rowPosition + 1 ; y++){
            for (x = pacman->columnPosition - 1; x <= pacman->columnPosition + 1 ; x++){
                attron( A_REVERSE | COLOR_PAIR(2));
                mvprintw(y, x, " ");
                attroff(COLOR_PAIR(2));
            }
        }
    }
    else{
        /* caso nao esteja, ele atravessa o mapa */
        pacmanThroughTheMap(pacman);
    }
    
    return;
}


struct pacman *createPacman(){

    struct pacman *temp;

    temp = malloc(sizeof(struct pacman));
    temp->size = SIZE_PACMAN;
    temp->lifes = LIFES;
    temp->alive = 1;

    return temp;
}


void pacmanThroughTheMap(struct pacman *pacman){

    int x, y, temp;

    attron( A_REVERSE | COLOR_PAIR(2));

    /* faz o desenho das partes do pacman quando passa dos limites */
    if ( pacman->columnPosition == 81 || pacman->columnPosition == 0 ){

        temp = 1;
        if ( pacman->columnPosition == 0 )
            pacman->columnPosition = 81;

        for (y = pacman->rowPosition - 1; y <= pacman->rowPosition + 1; y++){
            for (x = pacman->columnPosition - 1; x <= pacman->columnPosition ; x++){
                mvprintw(y, x, " ");
            }

            mvprintw(y, temp, " ");
        }
    }
    else if ( pacman->columnPosition == 1 || pacman->columnPosition == 82 ){

        temp = 81;
        if ( pacman->columnPosition == 82 )
            pacman->columnPosition = 1;

        for (y = pacman->rowPosition - 1; y <= pacman->rowPosition + 1; y++){
            for (x = pacman->columnPosition; x <= pacman->columnPosition + 1 ; x++){
                mvprintw(y, x, " ");
            }

            mvprintw(y, temp, " ");
        }
    }

    attroff(COLOR_PAIR(2));

    return;
}
