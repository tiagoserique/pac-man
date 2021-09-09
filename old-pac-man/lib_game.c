#include "lib_game.h"


int initialSettings(){

    initscr();

    /* verifica se o terminal suporta cores */
    if ( !has_colors() ){
        endwin();
        printf("O terminal não suporta cores\n");
        return 0;
    }

    int maxRows, maxColumns;
    getmaxyx(stdscr, maxRows, maxColumns);
    
    /* verifica se a janela do terminal tem o tamanho minimo */ 
    if ( maxRows < MAX_ROW + 1 || maxColumns < MAX_COL + 33 ){
        endwin();
        printf("O terminal deve ter no minimo %d x %d \n", MAX_ROW + 2, MAX_COL + 2);
        return 0;
    }

    /* inicializa cores*/
    start_color();
    init_color(COLOR_BLACK,    0,   0,   0);
    init_color(COLOR_BLUE,   200, 250, 850);
    init_color(DOTS_COLOR, 700, 700, 700);
    init_color(PACMAN_COLOR,   850, 850,   0);
    init_color(GATE_COLOR,   850, 550, 850);
    
    /* Barreiras */
    init_pair(BARRIER_COLOR, COLOR_BLUE, COLOR_BLACK);
    /* Pacman */
    init_pair(PACMAN_COLOR, PACMAN_COLOR, COLOR_BLACK); 
    /* Pastilha Normal */
    init_pair(DOTS_COLOR, DOTS_COLOR, COLOR_BLACK);  
    /* Fantasma vermelho */
    init_pair(BLINKY_COLOR, COLOR_RED, COLOR_BLACK); 
    /* Fantasma amarelo */     
    init_pair(CLYDE_COLOR, COLOR_YELLOW, COLOR_BLACK);  
    /* Fantasma rosa */     
    init_pair(PINKY_COLOR, COLOR_MAGENTA, COLOR_BLACK);
    /* Fantasma azul */    
    init_pair(INKY_COLOR, COLOR_CYAN, COLOR_BLACK);    
    /* Pastilha especial */   
    init_pair(ENERGIZERS_COLOR, COLOR_WHITE, COLOR_BLACK);       
    /* Portao */   
    init_pair(GATE_COLOR, GATE_COLOR, COLOR_BLACK);       


    cbreak();               /* desabilita buffer na entrada          */
    noecho();               /* nao mostra o que foi digitado na tela */
    nodelay(stdscr, TRUE);  /* nao aguarda a digitacao               */
    keypad(stdscr, TRUE);   /* habilita as setas do teclado          */
    curs_set(FALSE);        /* nao mostra o cursor na tela           */

    return 1;
}


void endGame(struct game *game, struct pacman *pacman){

    free(pacman);
    free(game->maze->matrix);
    free(game);

    endwin();

    return;
}


struct maze *createMaze(){
   
    struct maze *temp;
    int row;

    temp = malloc(sizeof(struct maze));

    temp->numRow = MAX_ROW;
    temp->numCol = MAX_COL;

    /* inicializa o labrinto com o vazio */
    temp->matrix = calloc(temp->numRow, sizeof(int *));
    for (row = 0; row < temp->numRow; row++)
        temp->matrix[row] = calloc(temp->numCol, sizeof(int));

    /* adiciona elementos do labirinto  */
    addBarriers(temp);
    addDots(temp);

    return temp;
}


struct game *startGame(){

    struct game *temp;

    temp = malloc(sizeof(struct game));
    temp->points = 0;
    temp->level = 1;
    temp->maze = createMaze();

    return temp;
}


void addBarriers(struct maze *maze){

    /* 1 linha/coluna do jogo = 3 linhas/colunas da matriz */
    /*    As barreiras tem tamanho 3x3 */

/* ___________________barreiras inicio dos fantasmas_________________________ */

    createBarrier(maze, 19, 27, 34, 36);
    createBarrier(maze, 19, 21, 37, 39);
    createBarrier(maze, 19, 21, 43, 45);
    createBarrier(maze, 19, 27, 46, 48);
    createBarrier(maze, 25, 27, 37, 45);

    addGate(maze, 19, 40);

/* __________________barreiras da primeira e ultima linha____________________ */

    createBarrier(maze,           1,       3, 1, MAX_COL);
    createBarrier(maze, MAX_ROW - 2, MAX_ROW, 1, MAX_COL);

/* __________________barreiras da primeira e ultima coluna___________________ */

    createBarrier(maze,  1,      21,           1,       3);
    createBarrier(maze, 25, MAX_ROW,           1,       3);
    createBarrier(maze,  1,      21, MAX_COL - 2, MAX_COL);
    createBarrier(maze, 25, MAX_ROW, MAX_COL - 2, MAX_COL);

/* __________________________outras barreiras________________________________ */

    createBarrier(maze,   4,    6,  37,  45);
    
    createBarrier(maze,   7,   21,   7,   9);
    createBarrier(maze,  25,   39,   7,   9);
    createBarrier(maze,  37,   39,  10,  21);
    
    createBarrier(maze,   7,   21,  73,  75);
    createBarrier(maze,  25,   39,  73,  75);
    createBarrier(maze,  37,   39,  61,  72);

    createBarrier(maze,  37,   42,  25,  33);
    createBarrier(maze,  31,   39,  37,  45);
    createBarrier(maze,  37,   42,  49,  57);
    
    createBarrier(maze,  31,   33,  13,  33);
    createBarrier(maze,  19,   30,  25,  30);

    createBarrier(maze,  31,   33,  49,  69);
    createBarrier(maze,  19,   30,  52,  57);
    
    createBarrier(maze,   7,    9,  10,  12);
    createBarrier(maze,   7,    9,  16,  27);
    createBarrier(maze,  10,   15,  25,  27);

    createBarrier(maze,   7,    9,  31,  33);
    createBarrier(maze,  10,   15,  31,  39);

    createBarrier(maze,   7,    9,  49,  51);
    createBarrier(maze,  10,   15,  43,  51);
    
    createBarrier(maze,   7,    9,  55,  66);
    createBarrier(maze,  10,   15,  55,  57);
    createBarrier(maze,   7,    9,  70,  72);

    createBarrier(maze,  13,   18,  13,  15);
    createBarrier(maze,  13,   18,  19,  21);
    createBarrier(maze,  22,   27,  13,  15);
    createBarrier(maze,  22,   27,  19,  21);

    createBarrier(maze,  13,   18,  61,  63);
    createBarrier(maze,  13,   18,  67,  69);
    createBarrier(maze,  22,   27,  61,  63);
    createBarrier(maze,  22,   27,  67,  69);

    return;
} 


void createBarrier(struct maze *maze, int row, int numRows,
 int column, int numColumns){

    int x, y;

    /*  recebe valores comecando com 1 */
    /* mas faz a correcao para atribuir na matriz */
    for (x = convertPositions(row) ; x <= convertPositions(numRows) ; x++){
        for (y = convertPositions(column) ; y <= convertPositions(numColumns) ; y++){
            if ( maze->matrix[x][y] != BARRIER )
                maze->matrix[x][y] = BARRIER;
            else
                continue;
        }
    }

    return;
}


void showMaze(struct maze *maze){

    int row, column, attribute;

    /* colore os elementos do labirinto */
    for (row = 0; row < maze->numRow; row++){
        for (column = 0; column < maze->numCol; column++){
            
            if ( maze->matrix[row][column] == EMPTY ){

                attribute = COLOR_PAIR(EMPTY_COLOR);
                attron(attribute);
                mvprintw(row + 1, column + 1, " ");
                attroff(attribute);
            }
            else if ( maze->matrix[row][column] == DOTS ){

                attribute = A_REVERSE | COLOR_PAIR(DOTS_COLOR);
                attron(attribute);
                mvprintw(row + 1, column + 1, " ");
                attroff(attribute);
            }
            else if ( maze->matrix[row][column] == ENERGIZERS ){

                attribute = A_REVERSE | COLOR_PAIR(ENERGIZERS_COLOR);
                attron(attribute);
                mvprintw(row + 1, column + 1, " ");
                attroff(attribute);
            }
            else if ( maze->matrix[row][column] == BARRIER ){

                attribute = A_REVERSE | COLOR_PAIR(BARRIER_COLOR); 
                attron(attribute);
                mvprintw(row + 1, column + 1, " ");
                attroff(attribute);
            }
            else if ( maze->matrix[row][column] == GATE ){

                attribute = A_REVERSE | COLOR_PAIR(GATE_COLOR); 
                attron(attribute);
                mvprintw(row + 1, column + 1, " ");
                attroff(attribute);
            }
        }
    }

    return;
}


void showLayout(struct game *game, struct pacman *pacman){

/* ___________________________________JOGO____________________________________*/
    
    attron(COLOR_PAIR(1));

    move(0, 0); addch(ACS_ULCORNER);
    move(0, 1); hline(ACS_HLINE, MAX_COL);
    move(1, 0); vline(ACS_VLINE, MAX_ROW);
    move(0, MAX_COL + 1); addch(ACS_URCORNER);

    move(MAX_ROW + 1, 0); addch(ACS_LLCORNER);
    move(MAX_ROW + 1, 1); hline(ACS_HLINE, MAX_COL);
    move(1, MAX_COL + 1); vline(ACS_VLINE, MAX_ROW);
    move(MAX_ROW + 1, MAX_COL + 1); addch(ACS_LRCORNER);

/* ________________________________TELA LATERAL______________________________ */

    move(0, MAX_COL +  1); addch(ACS_TTEE);
    move(0, MAX_COL +  2); hline(ACS_HLINE, 31);
    move(0, MAX_COL + 33); addch(ACS_URCORNER );
    
    move(MAX_ROW + 1, MAX_COL +  1); addch(ACS_BTEE);
    move(MAX_ROW + 1, MAX_COL +  2); hline(ACS_HLINE, 31);
    move(MAX_ROW + 1, MAX_COL + 33); addch(ACS_LRCORNER );
    
    move(1, MAX_COL + 33); vline(ACS_VLINE, MAX_ROW);

/* ___________________________________SCORE__________________________________ */

    move(3, MAX_COL +  6); addch(ACS_ULCORNER );
    move(3, MAX_COL +  7); hline(ACS_HLINE, 20);
    move(4, MAX_COL +  6); vline(ACS_VLINE,  1);
    move(3, MAX_COL + 27); addch(ACS_URCORNER );

    move(5, MAX_COL +  6); addch(ACS_LLCORNER );
    move(5, MAX_COL +  7); hline(ACS_HLINE, 20);
    move(4, MAX_COL + 27); vline(ACS_VLINE,  1);
    move(5, MAX_COL + 27); addch(ACS_LRCORNER );

    mvprintw(4, MAX_COL + 7, "SCORE: %d", game->points);

/* ___________________________________NIVEL__________________________________ */

    mvprintw((MAX_ROW + 2)/2, MAX_COL + 13, "NIVEL %d", game->level); 

/* ___________________________________VIDAS__________________________________ */

    int temp;
    for (temp = 0; temp < pacman->lifes - 1 ; temp++){
        mvprintw(MAX_ROW - 7, MAX_COL + (temp * 7) + 6, " .--. " ); 
        mvprintw(MAX_ROW - 6, MAX_COL + (temp * 7) + 6, "/ _.-'" ); 
        mvprintw(MAX_ROW - 5, MAX_COL + (temp * 7) + 6, "\\  '-."); 
        mvprintw(MAX_ROW - 4, MAX_COL + (temp * 7) + 6, " '--' " ); 
    }

/* _________________________________COMANDOS_________________________________ */

    mvprintw(MAX_ROW - 2, MAX_COL + 5, "Aperte r para reiniciar"); 
    mvprintw(MAX_ROW - 1, MAX_COL + 8, "Aperte q para sair"); 
    attroff(COLOR_PAIR(1));

    return;
}


int getKey(){

    int key = getch();

    /* caso a tecla seja pressionada, retorna 1 */
    if ( key != ERR ) {
        /* resgata a tecla pressionada para a proxima chamada de getch() */
        ungetch(key);
        return 1;
    } 
    else {
        return 0;
    }
}


int checkCollision(struct game *game, int direction, struct pacman *pacman){

    int row, column, limit;

    /* determina os limites da checagem da colizao de acordo com direcao */
    switch ( direction ){

        case KEY_UP :
            row  = convertPositions(pacman->rowPosition - 2); 
            column = convertPositions(pacman->columnPosition - 1);
            limit = convertPositions(pacman->columnPosition + 1);
            break;

        case KEY_DOWN :
            row  = convertPositions(pacman->rowPosition + 2);
            column = convertPositions(pacman->columnPosition - 1);
            limit = convertPositions(pacman->columnPosition + 1);
            break;

        case KEY_LEFT :
            row  = convertPositions(pacman->rowPosition - 1);
            column = convertPositions(pacman->columnPosition - 2);
            limit = convertPositions(pacman->rowPosition + 1);
            break;

        case KEY_RIGHT :
            row  = convertPositions(pacman->rowPosition - 1);
            column = convertPositions(pacman->columnPosition + 2);
            limit = convertPositions(pacman->rowPosition + 1);
            break;
    }

    if ( direction == KEY_UP || direction == KEY_DOWN){
        
        for ( ; column <= limit ; column++){

            /* se acha barreira na checagem */
            if ( game->maze->matrix[row][column] == BARRIER
              || game->maze->matrix[row][column] == GATE )
                return 0;
            /* se acha pastilha normal na checagem */
            else if ( game->maze->matrix[row][column] == DOTS ){

                game->points += 10;
                game->maze->matrix[row][column] = EMPTY;
            }
            /* se acha pastilha especial na checagem */
            else if ( game->maze->matrix[row][column] == ENERGIZERS ){

                if ( direction == KEY_UP ){

                    game->maze->matrix[row][column]     = EMPTY;
                    game->maze->matrix[row - 1][column] = EMPTY;
                }
                else if ( direction == KEY_DOWN ){

                    game->maze->matrix[row][column]     = EMPTY;
                    game->maze->matrix[row + 1][column] = EMPTY;
                }

                game->points += 100;
            }
        }
    }
    else if ( direction == KEY_LEFT || direction == KEY_RIGHT){
        
        for ( ; row <= limit ; row++){

            /* se acha barreira na checagem */
            if ( game->maze->matrix[row][column] == BARRIER
              || game->maze->matrix[row][column] == GATE )
                return 0;
            /* se acha pastilha normal na checagem */
            else if ( game->maze->matrix[row][column] == DOTS ){

                game->points += 10;
                game->maze->matrix[row][column] = EMPTY;
            }
            /* se acha pastilha especial na checagem */
            else if ( game->maze->matrix[row][column] == ENERGIZERS ){

                if ( direction == KEY_LEFT ){

                    game->maze->matrix[row][column]     = EMPTY;
                    game->maze->matrix[row][column - 1] = EMPTY;
                }
                else if ( direction == KEY_RIGHT ){

                    game->maze->matrix[row][column]     = EMPTY;
                    game->maze->matrix[row][column + 1] = EMPTY;
                }

                game->points += 100;
            }
        }
    }

    return 1;
}


int convertPositions(int position){

/* por causa do layout, as colunas da matriz e do ncurses nao correspodem */
/* para melhorar as contas e a legibilidade do codigo, essa funcao foi criada */
    return position - 1; 
}


void addDots(struct maze *maze){

    int row, column, inicialPositionGhosts, tunnelPosition;

    for (row = 1; row <= maze->numRow - 2 ; row += 3){
        for (column = 1; column <= maze->numCol - 2 ; column += 3){

            inicialPositionGhosts = convertPositions(row) >= 18 
                && convertPositions(row)  <= 24 
                && convertPositions(column) >= 36 
                && convertPositions(column) <= 45;

            tunnelPosition = convertPositions(row) >= 21
                &&   convertPositions(row)    <= 23 
                && ( convertPositions(column)   <= 2 
                ||   convertPositions(column)   >= 78 );

            /* checa se a posicao eh valida para colocar pastilha */
            if ( !(inicialPositionGhosts) && !(tunnelPosition) ) 
                createDots(maze, row, column);
        }
    }

    /* adiciona as pastilhas especiais nas posicoes indicadas */
    createEnergizers(maze, 35, 11);
    createEnergizers(maze, 35, 71);
    createEnergizers(maze,  8, 14);
    createEnergizers(maze,  8, 68);

    return;
}


void createDots(struct maze *maze, int row, int column){

    int x, y, rowLimit, columnLimit, podeColocar;
    
    rowLimit  = convertPositions(row)  + 2;
    columnLimit = convertPositions(column) + 2;
    podeColocar  = 1;

    for (y = convertPositions(row); y <= rowLimit ; y++){
        for (x = convertPositions(column) ; x <= columnLimit ; x++){
            /* se tiver barreira ou for a posicao incial do pacman */
            if ( maze->matrix[y][x] == BARRIER
            || ( y == INITIAL_ROW_POSITION && x == INITIAL_COLUMN_POSITION ) ){

                podeColocar = 0;
                break;
            }
        }
    }

    if ( podeColocar )
        maze->matrix[rowLimit - 1][columnLimit - 1] = DOTS;

    return;
}


void createEnergizers(struct maze *maze, int row, int column){

    row = convertPositions(row);
    column = convertPositions(column);

    /* acrescenta a pastilha na matriz */
    maze->matrix[row][column]         = ENERGIZERS;
    maze->matrix[row - 1][column]     = ENERGIZERS;
    maze->matrix[row][column + 1]     = ENERGIZERS;
    maze->matrix[row - 1][column + 1] = ENERGIZERS;

    return;
}


int hasDots(struct maze *maze){
    
    int row, column;

    for (row = 0; row < maze->numRow ; row ++){
        for (column = 0; column < maze->numCol ; column ++){
            /* se tiver alguma pastilha */
            if ( maze->matrix[row][column] == DOTS
              || maze->matrix[row][column] == ENERGIZERS )
                return 1;
        }
    }

    return 0;
}


void restartGame(struct game *game, struct pacman *pacman, int *direction,
 int *previousDirection, int *successfullyMove){
    
    /* coloca o pacman na posicao inicial */
    pacman->rowPosition = INITIAL_ROW_POSITION;
    pacman->columnPosition = INITIAL_COLUMN_POSITION;

    /* aloca um novo labirinto */
    free(game->maze->matrix);
    free(game->maze);
    game->maze = createMaze();

    /* ajusta a movimentacao */
    *direction = *previousDirection = KEY_LEFT;
    *successfullyMove = 1;

    /* limpa o labirinto anterior e imprime o novo */
    clear();
    showMaze(game->maze);
    showLayout(game, pacman);
    showPacman(pacman);
    refresh();

    return;
}


void addGate(struct maze *maze, int row, int column){

    int x, y;
    int numRows = convertPositions(row) + 1;
    int numColumns = convertPositions(column) + 2;

    for (x = convertPositions(row) ; x <= numRows ; x++){
        for (y = convertPositions(column) ; y <= numColumns ; y++){
            if ( maze->matrix[x][y] != BARRIER )
                maze->matrix[x][y] = GATE;
            else
                continue;
        }
    }
    return;
}

