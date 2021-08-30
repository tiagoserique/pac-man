#include "lib_telas.h"


int telaDeFimDeJogo(){

    int posiLin, posiCol, temp; 

    getmaxyx(stdscr, posiLin, posiCol);

    posiLin /= 2;
    posiCol = (posiCol / 2) - 20;

    attron(A_REVERSE | COLOR_PAIR(4));

    mvprintw(posiLin - 9, posiCol - 25, "  _______   _______   __   __   _______      _______   __   __   _______   ______   ");
    mvprintw(posiLin - 8, posiCol - 25, " |    ___| |   _   | |  | |  | |    ___|    |   _   | |  | |  | |    ___| |   _  |   ");
    mvprintw(posiLin - 7, posiCol - 25, " |   | __  |  | |  | |  |_|  | |   |___     |  | |  | |  | |  | |   |___  |  |_| |   ");
    mvprintw(posiLin - 6, posiCol - 25, " |   ||  | |  |_|  | |       | |    ___|    |  | |  | |  |_|  | |    ___| |   __ \\   "); 
    mvprintw(posiLin - 5, posiCol - 25, " |   |_| | |   _   | | ||_|| | |   |___     |  |_|  |  |     |  |   |___  |  |  \\ \\  ");
    mvprintw(posiLin - 4, posiCol - 25, " |_______| |__| |__| |_|   |_| |_______|    |_______|   |___|   |_______| |__|   \\_\\ ");
    mvprintw(posiLin - 3, posiCol - 25, "                                                                                    ");
    
    mvprintw(posiLin + 5, posiCol - 1, " Aperte r para recomeçar "); 
    mvprintw(posiLin + 7, posiCol + 5, " Aperte q para sair "); 

    attroff(A_REVERSE | COLOR_PAIR(4));

    refresh();

    do {

        temp = getch();
    } while ( temp == 'r' && temp == 'q' );

    if ( temp == 'r' )
        return 1;
    return 0;

}


int telaDeNovoNivel(){

    clear();
    int posiLin, posiCol, temp; 

    getmaxyx(stdscr, posiLin, posiCol);

    posiLin /= 2;
    posiCol = (posiCol / 2) - 20;
    
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

