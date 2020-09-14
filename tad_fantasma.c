#include "tad_fantasma.h"


struct fantasma *criaBlinky(){

    struct fantasma *temp;

    temp = malloc(sizeof(struct fantasma));
    
    temp->id      = BLINKY;    
    temp->posiLin = 17;
    temp->posiCol = 41;
    temp->fugir   = 0;

    return temp;
}


struct fantasma *criaPinky(){

    struct fantasma *temp;

    temp = malloc(sizeof(struct fantasma));
    
    temp->id      = PINKY;    
    temp->posiLin = 23;
    temp->posiCol = 41;
    temp->fugir   = 0;

    return temp;
}


struct fantasma *criaInky(){

    struct fantasma *temp;

    temp = malloc(sizeof(struct fantasma));
    
    temp->id      = INKY;    
    temp->posiLin = 23;
    temp->posiCol = 38;
    temp->fugir   = 0;

    return temp;
}


struct fantasma *criaClyde(){
    
    struct fantasma *temp;

    temp = malloc(sizeof(struct fantasma));

    temp->id      = CLYDE;    
    temp->posiLin = 23;
    temp->posiCol = 44;
    temp->fugir   = 0;

    return temp;
}


void mostraFantasma(struct fantasma *fantasma){
    
    int x, y, atributo;

    if ( fantasma->id == BLINKY )
        atributo = A_REVERSE | COLOR_PAIR(COR_BLINKY);
    else if ( fantasma->id == PINKY )
        atributo = A_REVERSE | COLOR_PAIR(COR_PINKY);
    else if ( fantasma->id == INKY )
        atributo = A_REVERSE | COLOR_PAIR(COR_INKY);
    else if ( fantasma->id == CLYDE )
        atributo = A_REVERSE | COLOR_PAIR(COR_CLYDE);

    /* mostra o fantasma inteiro caso esteja entre essas posicoes */
    if ( fantasma->posiCol >= 2 && fantasma->posiCol <= 80 ){

        for (y = fantasma->posiLin - 1; y <= fantasma->posiLin + 1 ; y++){
            for (x = fantasma->posiCol - 1; x <= fantasma->posiCol + 1 ; x++){
                attron(atributo);
                mvprintw(y, x, " ");
                attroff(atributo);
            }
        }
    }
    else
        /* caso nao esteja, ele atravessa o mapa */
        fantasmaAtravessaMapa(fantasma, atributo);

    /*mvprintw(y, x, "%d %d", fantasma->posiLin, fantasma->posiCol);*/

    return;
}


void fantasmaAtravessaMapa(struct fantasma *fantasma, int atributo){

    int x, y, temp;

    attron(atributo);

    /* faz o desenho das partes do pacman quando passa dos limites */
    if ( fantasma->posiCol == 81 || fantasma->posiCol == 0 ){

        temp = 1;
        if ( fantasma->posiCol == 0 )
            fantasma->posiCol = 81;

        for (y = fantasma->posiLin - 1; y <= fantasma->posiLin + 1; y++){
            for (x = fantasma->posiCol - 1; x <= fantasma->posiCol ; x++){
                mvprintw(y, x, " ");
            }

            mvprintw(y, temp, " ");
        }
    }
    else if ( fantasma->posiCol == 1 || fantasma->posiCol == 82 ){

        temp = 81;
        if ( fantasma->posiCol == 82 )
            fantasma->posiCol = 1;

        for (y = fantasma->posiLin - 1; y <= fantasma->posiLin + 1; y++){
            for (x = fantasma->posiCol; x <= fantasma->posiCol + 1 ; x++){
                mvprintw(y, x, " ");
            }

            mvprintw(y, temp, " ");
        }
    }

    attroff(atributo);

    return;
}



/*
void destroiPacman(struct pacman *pacman){

    free(pacman);
    return;
}

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

*/
