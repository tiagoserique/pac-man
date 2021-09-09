#include "lib_screen.h"


int endGameScreen(){

    int rowPosition, columnPosition, temp; 

    getmaxyx(stdscr, rowPosition, columnPosition);

    rowPosition /= 2;
    columnPosition = (columnPosition / 2) - 20;

    attron(A_REVERSE | COLOR_PAIR(4));

    mvprintw(rowPosition - 9, columnPosition - 25, "  _______   _______   __   __   _______      _______   __   __   _______   ______   ");
    mvprintw(rowPosition - 8, columnPosition - 25, " |    ___| |   _   | |  | |  | |    ___|    |   _   | |  | |  | |    ___| |   _  |   ");
    mvprintw(rowPosition - 7, columnPosition - 25, " |   | __  |  | |  | |  |_|  | |   |___     |  | |  | |  | |  | |   |___  |  |_| |   ");
    mvprintw(rowPosition - 6, columnPosition - 25, " |   ||  | |  |_|  | |       | |    ___|    |  | |  | |  |_|  | |    ___| |   __ \\   "); 
    mvprintw(rowPosition - 5, columnPosition - 25, " |   |_| | |   _   | | ||_|| | |   |___     |  |_|  |  |     |  |   |___  |  |  \\ \\  ");
    mvprintw(rowPosition - 4, columnPosition - 25, " |_______| |__| |__| |_|   |_| |_______|    |_______|   |___|   |_______| |__|   \\_\\ ");
    mvprintw(rowPosition - 3, columnPosition - 25, "                                                                                    ");
    
    mvprintw(rowPosition + 5, columnPosition - 1, " Aperte r para recomeçar "); 
    mvprintw(rowPosition + 7, columnPosition + 5, " Aperte q para sair "); 

    attroff(A_REVERSE | COLOR_PAIR(4));

    refresh();

    do {

        temp = getch();
    } while ( temp == 'r' && temp == 'q' );

    if ( temp == 'r' )
        return 1;
    return 0;

}


int newLevelScreen(){

    clear();
    int rowPosition, columnPosition, temp; 

    getmaxyx(stdscr, rowPosition, columnPosition);

    rowPosition /= 2;
    columnPosition = (columnPosition / 2) - 20;
    
    attron(COLOR_PAIR(2));

    mvprintw(rowPosition - 9, columnPosition - 15, "  _______   _______   _______   _______   _______   __   __  ");
    mvprintw(rowPosition - 8, columnPosition - 15, " |    _  | |   _   | |  _____| |  _____| |   _   | |  | |  | ");
    mvprintw(rowPosition - 7, columnPosition - 15, " |   |_| | |  | |  | | |_____  | |_____  |  | |  | |  | |  | ");
    mvprintw(rowPosition - 6, columnPosition - 15, " |    ___| |  |_|  | |_____  | |_____  | |  | |  | |  | |  | "); 
    mvprintw(rowPosition - 5, columnPosition - 15, " |   |     |   _   |  _____| |  _____| | |  |_|  | |  |_|  | ");
    mvprintw(rowPosition - 4, columnPosition - 15, " |___|     |__| |__| |_______| |_______| |_______| |_______| ");
    mvprintw(rowPosition - 3, columnPosition - 15, "                                                             ");

    mvprintw(rowPosition    , columnPosition, "  .--.       .-----.        ");
    mvprintw(rowPosition + 1, columnPosition, " |  OO|     /      .'  .--. ");
    mvprintw(rowPosition + 2, columnPosition, " |    |     |    .'    '  ' ");
    mvprintw(rowPosition + 3, columnPosition, " |    |     \\     '-.  '--' ");
    mvprintw(rowPosition + 4, columnPosition, " '^^^^'      '-...-'        ");
    
    mvprintw(rowPosition +  8, columnPosition - 1, " Aperte p para o proximo nivel "); 
    mvprintw(rowPosition + 10, columnPosition + 5, " Aperte q para sair "); 

    attroff(COLOR_PAIR(2));

    refresh();

    do {

        temp = getch();
    } while ( temp != 'q' && temp != 'p' );

    if ( temp == 'p' ) 
        return 1;
    return 0;
}

