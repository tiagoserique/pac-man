#include "lib_telas.h"


int telaDeFimDeJogo(){
    
    clear();
    
    int posiLin, posiCol, temp; 

    getmaxyx(stdscr, posiLin, posiCol);

    posiLin /= 2;
    posiCol = (posiCol / 2) - 20;

    attron(A_REVERSE | COLOR_PAIR(1));

    mvprintw(posiLin - 9, posiCol - 25, "  _______   _______   __   __   _______      _______   __   __   _______   ______    ");
    mvprintw(posiLin - 8, posiCol - 25, " |    ___| |   _   | |  | |  | |    ___|    |   _   | |  | |  | |    ___| |   _  |   ");
    mvprintw(posiLin - 7, posiCol - 25, " |   | __  |  | |  | |  |_|  | |   |___     |  | |  | |  | |  | |   |___  |  |_| |   ");
    mvprintw(posiLin - 6, posiCol - 25, " |   ||  | |  |_|  | |       | |    ___|    |  | |  | |  |_|  | |    ___| |   __ \\   "); 
    mvprintw(posiLin - 5, posiCol - 25, " |   |_| | |   _   | | ||_|| | |   |___     |  |_|  |  |     |  |   |___  |  |  \\ \\  ");
    mvprintw(posiLin - 4, posiCol - 25, " |_______| |__| |__| |_|   |_| |_______|    |_______|   |___|   |_______| |__|   \\_\\ ");
    mvprintw(posiLin - 3, posiCol - 25, "                                                                                     ");
    
    mvprintw(posiLin + 5, posiCol + 3, " Aperte r para recomeçar "); 
    mvprintw(posiLin + 7, posiCol + 5, " Aperte q para sair "); 

    attroff(A_REVERSE | COLOR_PAIR(1));

    refresh();

    do {
        temp = getch();
    } while ( temp != 'r' && temp != 'q' );

    if ( temp == 'r' )
        return 1;
    return 0;

}


int telaDeNovoNivel(){

    clear();
    int posiLin, posiCol, temp; 

    getmaxyx(stdscr, posiLin, posiCol);

    posiLin /= 2;
    posiCol  = (posiCol / 2) - 20;
    
    attron(COLOR_PAIR(2));

    mvprintw(posiLin - 9, posiCol - 15, "  _______   _______   _______   _______   _______   __   __  ");
    mvprintw(posiLin - 8, posiCol - 15, " |    _  | |   _   | |  _____| |  _____| |   _   | |  | |  | ");
    mvprintw(posiLin - 7, posiCol - 15, " |   |_| | |  | |  | | |_____  | |_____  |  | |  | |  | |  | ");
    mvprintw(posiLin - 6, posiCol - 15, " |    ___| |  |_|  | |_____  | |_____  | |  | |  | |  | |  | "); 
    mvprintw(posiLin - 5, posiCol - 15, " |   |     |   _   |  _____| |  _____| | |  |_|  | |  |_|  | ");
    mvprintw(posiLin - 4, posiCol - 15, " |___|     |__| |__| |_______| |_______| |_______| |_______| ");
    mvprintw(posiLin - 3, posiCol - 15, "                                                             ");

    mvprintw(posiLin    , posiCol, "  .--.       .-----.        ");
    mvprintw(posiLin + 1, posiCol, " |  OO|     /      .'  .--. ");
    mvprintw(posiLin + 2, posiCol, " |    |     |    .'    '  ' ");
    mvprintw(posiLin + 3, posiCol, " |    |     \\     '-.  '--' ");
    mvprintw(posiLin + 4, posiCol, " '^^^^'      '-...-'        ");
    
    mvprintw(posiLin +  8, posiCol - 1, " Aperte p para o proximo nivel "); 
    mvprintw(posiLin + 10, posiCol + 5, " Aperte q para sair "); 

    attroff(COLOR_PAIR(2));

    refresh();

    do {
        temp = getch();
    } while ( temp != 'q' && temp != 'p' );

    if ( temp == 'p' ) 
        return 1;
    return 0;
}


void mostraLayout(int pontos, int nivel, int vidas){

/* ___________________________________JOGO____________________________________*/
    
    attron(COLOR_PAIR(COR_BARREIRA));

    move(0, 0); addch(ACS_ULCORNER);
    move(0, 1); hline(ACS_HLINE, MAX_COL);
    move(1, 0); vline(ACS_VLINE, MAX_LIN);
    move(0, MAX_COL + 1); addch(ACS_URCORNER);

    move(MAX_LIN + 1, 0); addch(ACS_LLCORNER);
    move(MAX_LIN + 1, 1); hline(ACS_HLINE, MAX_COL);
    move(1, MAX_COL + 1); vline(ACS_VLINE, MAX_LIN);
    move(MAX_LIN + 1, MAX_COL + 1); addch(ACS_LRCORNER);

/* ________________________________TELA LATERAL______________________________ */

    move(0, MAX_COL +  1); addch(ACS_TTEE);
    move(0, MAX_COL +  2); hline(ACS_HLINE, 31);
    move(0, MAX_COL + 33); addch(ACS_URCORNER );
    
    move(MAX_LIN + 1, MAX_COL +  1); addch(ACS_BTEE);
    move(MAX_LIN + 1, MAX_COL +  2); hline(ACS_HLINE, 31);
    move(MAX_LIN + 1, MAX_COL + 33); addch(ACS_LRCORNER );
    
    move(1, MAX_COL + 33); vline(ACS_VLINE, MAX_LIN);

/* ___________________________________SCORE__________________________________ */

    move(3, MAX_COL +  6); addch(ACS_ULCORNER );
    move(3, MAX_COL +  7); hline(ACS_HLINE, 20);
    move(4, MAX_COL +  6); vline(ACS_VLINE,  1);
    move(3, MAX_COL + 27); addch(ACS_URCORNER );

    move(5, MAX_COL +  6); addch(ACS_LLCORNER );
    move(5, MAX_COL +  7); hline(ACS_HLINE, 20);
    move(4, MAX_COL + 27); vline(ACS_VLINE,  1);
    move(5, MAX_COL + 27); addch(ACS_LRCORNER );

    mvprintw(4, MAX_COL + 7, "SCORE: %d", pontos);

/* ___________________________________NIVEL__________________________________ */

    mvprintw((MAX_LIN + 2)/2, MAX_COL + 13, "NIVEL %d", nivel); 

/* ___________________________________VIDAS__________________________________ */

    int temp;
    for (temp = 0; temp < vidas - 1 ; temp++){
        mvprintw(MAX_LIN - 7, MAX_COL + (temp * 7) + 6, " .--. " ); 
        mvprintw(MAX_LIN - 6, MAX_COL + (temp * 7) + 6, "/ _.-'" ); 
        mvprintw(MAX_LIN - 5, MAX_COL + (temp * 7) + 6, "\\  '-."); 
        mvprintw(MAX_LIN - 4, MAX_COL + (temp * 7) + 6, " '--' " ); 
    }

/* _________________________________COMANDOS_________________________________ */

    mvprintw(MAX_LIN - 2, MAX_COL + 5, "Aperte r para reiniciar"); 
    mvprintw(MAX_LIN - 1, MAX_COL + 8, "Aperte q para sair"); 
    attroff(COLOR_PAIR(COR_BARREIRA));

    return;
}


void exibeTudo(struct jogo *jogo, struct pacman *pacman, struct fantasma *blinky,
struct fantasma *pinky, struct fantasma *inky, struct fantasma *clyde,
 int versaoFantasma){

    mostraLabirinto(jogo->labirinto);
    mostraLayout(jogo->pontos, jogo->nivel, pacman->vidas);
    mostraPacman(pacman);
    mostraFantasma(blinky, versaoFantasma);
    mostraFantasma(pinky,  versaoFantasma);
    mostraFantasma(inky,   versaoFantasma);
    mostraFantasma(clyde,  versaoFantasma);
    return;
}