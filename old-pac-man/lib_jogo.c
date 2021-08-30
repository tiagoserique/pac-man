#include "lib_jogo.h"


int configuracoesIniciais(){

    initscr();

    /* verifica se o terminal suporta cores */
    if ( !has_colors() ){
        endwin();
        printf("O terminal não suporta cores\n");
        return 0;
    }

    int maxLinhas, maxColunas;
    getmaxyx(stdscr, maxLinhas, maxColunas);
    
    /* verifica se a janela do terminal tem o tamanho minimo */ 
    if ( maxLinhas < MAX_LIN + 1 || maxColunas < MAX_COL + 33 ){
        endwin();
        printf("O terminal deve ter no minimo %d x %d \n", MAX_LIN + 2, MAX_COL + 2);
        return 0;
    }

    /* inicializa cores*/
    start_color();
    init_color(COLOR_BLACK,    0,   0,   0);
    init_color(COLOR_BLUE,   200, 250, 850);
    init_color(COR_PASTILHA, 700, 700, 700);
    init_color(COR_PACMAN,   850, 850,   0);
    init_color(COR_PORTAO,   850, 550, 850);
    
    /* Barreiras */
    init_pair(COR_BARREIRA, COLOR_BLUE, COLOR_BLACK);
    /* Pacman */
    init_pair(COR_PACMAN, COR_PACMAN, COLOR_BLACK); 
    /* Pastilha Normal */
    init_pair(COR_PASTILHA, COR_PASTILHA, COLOR_BLACK);  
    /* Fantasma vermelho */
    init_pair(COR_BLINKY, COLOR_RED, COLOR_BLACK); 
    /* Fantasma amarelo */     
    init_pair(COR_CLYDE, COLOR_YELLOW, COLOR_BLACK);  
    /* Fantasma rosa */     
    init_pair(COR_ROSA, COLOR_MAGENTA, COLOR_BLACK);
    /* Fantasma azul */    
    init_pair(COR_INKY, COLOR_CYAN, COLOR_BLACK);    
    /* Pastilha especial */   
    init_pair(COR_PASTILHA_ESPECIAL, COLOR_WHITE, COLOR_BLACK);       
    /* Portao */   
    init_pair(COR_PORTAO, COR_PORTAO, COLOR_BLACK);       


    cbreak();               /* desabilita buffer na entrada          */
    noecho();               /* nao mostra o que foi digitado na tela */
    nodelay(stdscr, TRUE);  /* nao aguarda a digitacao               */
    keypad(stdscr, TRUE);   /* habilita as setas do teclado          */
    curs_set(FALSE);        /* nao mostra o cursor na tela           */

    return 1;
}


void finalizaJogo(struct jogo *jogo, struct pacman *pacman){

    free(pacman);
    free(jogo->labirinto->matriz);
    free(jogo);

    endwin();

    return;
}


struct labirinto *criaLabirinto(){
   
    struct labirinto *temp;
    int linha;

    temp = malloc(sizeof(struct labirinto));

    temp->qtdLin = MAX_LIN;
    temp->qtdCol = MAX_COL;

    /* inicializa o labrinto com o vazio */
    temp->matriz = calloc(temp->qtdLin, sizeof(int *));
    for (linha = 0; linha < temp->qtdLin; linha++)
        temp->matriz[linha] = calloc(temp->qtdCol, sizeof(int));

    /* adiciona elementos do labirinto  */
    adicionaBarreiras(temp);
    adicionaPastilhas(temp);

    return temp;
}


struct jogo *inicializaJogo(){

    struct jogo * temp;

    temp = malloc(sizeof(struct jogo));
    temp->pontos = 0;
    temp->nivel = 1;
    temp->labirinto = criaLabirinto();

    return temp;
}


void adicionaBarreiras(struct labirinto *labirinto){

    /* 1 linha/coluna do jogo = 3 linhas/colunas da matriz */
    /*    As barreiras tem tamanho 3x3 */

/* ___________________barreiras inicio dos fantasmas_________________________ */

    criaBarreira(labirinto, 19, 27, 34, 36);
    criaBarreira(labirinto, 19, 21, 37, 39);
    criaBarreira(labirinto, 19, 21, 43, 45);
    criaBarreira(labirinto, 19, 27, 46, 48);
    criaBarreira(labirinto, 25, 27, 37, 45);

    adicionaPortao(labirinto, 19, 40);

/* __________________barreiras da primeira e ultima linha____________________ */

    criaBarreira(labirinto,           1,       3, 1, MAX_COL);
    criaBarreira(labirinto, MAX_LIN - 2, MAX_LIN, 1, MAX_COL);

/* __________________barreiras da primeira e ultima coluna___________________ */

    criaBarreira(labirinto,  1,      21,           1,       3);
    criaBarreira(labirinto, 25, MAX_LIN,           1,       3);
    criaBarreira(labirinto,  1,      21, MAX_COL - 2, MAX_COL);
    criaBarreira(labirinto, 25, MAX_LIN, MAX_COL - 2, MAX_COL);

/* __________________________outras barreiras________________________________ */

    criaBarreira(labirinto,   4,    6,  37,  45);
    
    criaBarreira(labirinto,   7,   21,   7,   9);
    criaBarreira(labirinto,  25,   39,   7,   9);
    criaBarreira(labirinto,  37,   39,  10,  21);
    
    criaBarreira(labirinto,   7,   21,  73,  75);
    criaBarreira(labirinto,  25,   39,  73,  75);
    criaBarreira(labirinto,  37,   39,  61,  72);

    criaBarreira(labirinto,  37,   42,  25,  33);
    criaBarreira(labirinto,  31,   39,  37,  45);
    criaBarreira(labirinto,  37,   42,  49,  57);
    
    criaBarreira(labirinto,  31,   33,  13,  33);
    criaBarreira(labirinto,  19,   30,  25,  30);

    criaBarreira(labirinto,  31,   33,  49,  69);
    criaBarreira(labirinto,  19,   30,  52,  57);
    
    criaBarreira(labirinto,   7,    9,  10,  12);
    criaBarreira(labirinto,   7,    9,  16,  27);
    criaBarreira(labirinto,  10,   15,  25,  27);

    criaBarreira(labirinto,   7,    9,  31,  33);
    criaBarreira(labirinto,  10,   15,  31,  39);

    criaBarreira(labirinto,   7,    9,  49,  51);
    criaBarreira(labirinto,  10,   15,  43,  51);
    
    criaBarreira(labirinto,   7,    9,  55,  66);
    criaBarreira(labirinto,  10,   15,  55,  57);
    criaBarreira(labirinto,   7,    9,  70,  72);

    criaBarreira(labirinto,  13,   18,  13,  15);
    criaBarreira(labirinto,  13,   18,  19,  21);
    criaBarreira(labirinto,  22,   27,  13,  15);
    criaBarreira(labirinto,  22,   27,  19,  21);

    criaBarreira(labirinto,  13,   18,  61,  63);
    criaBarreira(labirinto,  13,   18,  67,  69);
    criaBarreira(labirinto,  22,   27,  61,  63);
    criaBarreira(labirinto,  22,   27,  67,  69);

    return;
} 


void criaBarreira(struct labirinto *labirinto, int linha, int qtdLinhas,
 int coluna, int qtdColunas){

    int x, y;

    /*  recebe valores comecando com 1 */
    /* mas faz a correcao para atribuir na matriz */
    for (x = convertePosicoes(linha) ; x <= convertePosicoes(qtdLinhas) ; x++){
        for (y = convertePosicoes(coluna) ; y <= convertePosicoes(qtdColunas) ; y++){
            if ( labirinto->matriz[x][y] != BARREIRA )
                labirinto->matriz[x][y] = BARREIRA;
            else
                continue;
        }
    }

    return;
}


void mostraLabirinto(struct labirinto *labirinto){

    int linha, coluna, atributo;

    /* colore os elementos do labirinto */
    for (linha = 0; linha < labirinto->qtdLin; linha++){
        for (coluna = 0; coluna < labirinto->qtdCol; coluna++){
            
            if ( labirinto->matriz[linha][coluna] == VAZIO ){

                atributo = COLOR_PAIR(COR_VAZIO);
                attron(atributo);
                mvprintw(linha + 1, coluna + 1, " ");
                attroff(atributo);
            }
            else if ( labirinto->matriz[linha][coluna] == PASTILHA_NORMAL ){

                atributo = A_REVERSE | COLOR_PAIR(COR_PASTILHA);
                attron(atributo);
                mvprintw(linha + 1, coluna + 1, " ");
                attroff(atributo);
            }
            else if ( labirinto->matriz[linha][coluna] == PASTILHA_ESPECIAL ){

                atributo = A_REVERSE | COLOR_PAIR(COR_PASTILHA_ESPECIAL);
                attron(atributo);
                mvprintw(linha + 1, coluna + 1, " ");
                attroff(atributo);
            }
            else if ( labirinto->matriz[linha][coluna] == BARREIRA ){

                atributo = A_REVERSE | COLOR_PAIR(COR_BARREIRA); 
                attron(atributo);
                mvprintw(linha + 1, coluna + 1, " ");
                attroff(atributo);
            }
            else if ( labirinto->matriz[linha][coluna] == PORTAO ){

                atributo = A_REVERSE | COLOR_PAIR(COR_PORTAO); 
                attron(atributo);
                mvprintw(linha + 1, coluna + 1, " ");
                attroff(atributo);
            }
        }
    }

    return;
}


void mostraLayout(struct jogo *jogo, struct pacman *pacman){

/* ___________________________________JOGO____________________________________*/
    
    attron(COLOR_PAIR(1));

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

    mvprintw(4, MAX_COL + 7, "SCORE: %d", jogo->pontos);

/* ___________________________________NIVEL__________________________________ */

    mvprintw((MAX_LIN + 2)/2, MAX_COL + 13, "NIVEL %d", jogo->nivel); 

/* ___________________________________VIDAS__________________________________ */

    int temp;
    for (temp = 0; temp < pacman->vidas - 1 ; temp++){
        mvprintw(MAX_LIN - 7, MAX_COL + (temp * 7) + 6, " .--. " ); 
        mvprintw(MAX_LIN - 6, MAX_COL + (temp * 7) + 6, "/ _.-'" ); 
        mvprintw(MAX_LIN - 5, MAX_COL + (temp * 7) + 6, "\\  '-."); 
        mvprintw(MAX_LIN - 4, MAX_COL + (temp * 7) + 6, " '--' " ); 
    }

/* _________________________________COMANDOS_________________________________ */

    mvprintw(MAX_LIN - 2, MAX_COL + 5, "Aperte r para reiniciar"); 
    mvprintw(MAX_LIN - 1, MAX_COL + 8, "Aperte q para sair"); 
    attroff(COLOR_PAIR(1));

    return;
}


int pegaTecla(){

    int tecla = getch();

    /* caso a tecla seja pressionada, retorna 1 */
    if ( tecla != ERR ) {
        /* resgata a tecla pressionada para a proxima chamada de getch() */
        ungetch(tecla);
        return 1;
    } 
    else {
        return 0;
    }
}


int checaColizao(struct jogo *jogo, int direcao, struct pacman *pacman){

    int linha, coluna, limite;

    /* determina os limites da checagem da colizao de acordo com direcao */
    switch ( direcao ){

        case KEY_UP :
            linha  = convertePosicoes(pacman->posiLin - 2); 
            coluna = convertePosicoes(pacman->posiCol - 1);
            limite = convertePosicoes(pacman->posiCol + 1);
            break;

        case KEY_DOWN :
            linha  = convertePosicoes(pacman->posiLin + 2);
            coluna = convertePosicoes(pacman->posiCol - 1);
            limite = convertePosicoes(pacman->posiCol + 1);
            break;

        case KEY_LEFT :
            linha  = convertePosicoes(pacman->posiLin - 1);
            coluna = convertePosicoes(pacman->posiCol - 2);
            limite = convertePosicoes(pacman->posiLin + 1);
            break;

        case KEY_RIGHT :
            linha  = convertePosicoes(pacman->posiLin - 1);
            coluna = convertePosicoes(pacman->posiCol + 2);
            limite = convertePosicoes(pacman->posiLin + 1);
            break;
    }

    if ( direcao == KEY_UP || direcao == KEY_DOWN){
        
        for ( ; coluna <= limite ; coluna++){

            /* se acha barreira na checagem */
            if ( jogo->labirinto->matriz[linha][coluna] == BARREIRA
              || jogo->labirinto->matriz[linha][coluna] == PORTAO )
                return 0;
            /* se acha pastilha normal na checagem */
            else if ( jogo->labirinto->matriz[linha][coluna] == PASTILHA_NORMAL ){

                jogo->pontos += 10;
                jogo->labirinto->matriz[linha][coluna] = VAZIO;
            }
            /* se acha pastilha especial na checagem */
            else if ( jogo->labirinto->matriz[linha][coluna] == PASTILHA_ESPECIAL ){

                if ( direcao == KEY_UP ){

                    jogo->labirinto->matriz[linha][coluna]     = VAZIO;
                    jogo->labirinto->matriz[linha - 1][coluna] = VAZIO;
                }
                else if ( direcao == KEY_DOWN ){

                    jogo->labirinto->matriz[linha][coluna]     = VAZIO;
                    jogo->labirinto->matriz[linha + 1][coluna] = VAZIO;
                }

                jogo->pontos += 100;
            }
        }
    }
    else if ( direcao == KEY_LEFT || direcao == KEY_RIGHT){
        
        for ( ; linha <= limite ; linha++){

            /* se acha barreira na checagem */
            if ( jogo->labirinto->matriz[linha][coluna] == BARREIRA
              || jogo->labirinto->matriz[linha][coluna] == PORTAO )
                return 0;
            /* se acha pastilha normal na checagem */
            else if ( jogo->labirinto->matriz[linha][coluna] == PASTILHA_NORMAL ){

                jogo->pontos += 10;
                jogo->labirinto->matriz[linha][coluna] = VAZIO;
            }
            /* se acha pastilha especial na checagem */
            else if ( jogo->labirinto->matriz[linha][coluna] == PASTILHA_ESPECIAL ){

                if ( direcao == KEY_LEFT ){

                    jogo->labirinto->matriz[linha][coluna]     = VAZIO;
                    jogo->labirinto->matriz[linha][coluna - 1] = VAZIO;
                }
                else if ( direcao == KEY_RIGHT ){

                    jogo->labirinto->matriz[linha][coluna]     = VAZIO;
                    jogo->labirinto->matriz[linha][coluna + 1] = VAZIO;
                }

                jogo->pontos += 100;
            }
        }
    }

    return 1;
}


int convertePosicoes(int posicao){

/* por causa do layout, as colunas da matriz e do ncurses nao correspodem */
/* para melhorar as contas e a legibilidade do codigo, essa funcao foi criada */
    return posicao - 1; 
}


void adicionaPastilhas(struct labirinto *labirinto){

    int linha, coluna, posiInicialFantasmas, posiTunel;

    for (linha = 1; linha <= labirinto->qtdLin - 2 ; linha += 3){
        for (coluna = 1; coluna <= labirinto->qtdCol - 2 ; coluna += 3){

            posiInicialFantasmas = convertePosicoes(linha) >= 18 
                && convertePosicoes(linha)  <= 24 
                && convertePosicoes(coluna) >= 36 
                && convertePosicoes(coluna) <= 45;

            posiTunel = convertePosicoes(linha) >= 21
                &&   convertePosicoes(linha)    <= 23 
                && ( convertePosicoes(coluna)   <= 2 
                ||   convertePosicoes(coluna)   >= 78 );

            /* checa se a posicao eh valida para colocar pastilha */
            if ( !(posiInicialFantasmas) && !(posiTunel) ) 
                criaPastilhaNormal(labirinto, linha, coluna);
        }
    }

    /* adiciona as pastilhas especiais nas posicoes indicadas */
    criaPastilhaEspecial(labirinto, 35, 11);
    criaPastilhaEspecial(labirinto, 35, 71);
    criaPastilhaEspecial(labirinto,  8, 14);
    criaPastilhaEspecial(labirinto,  8, 68);

    return;
}


void criaPastilhaNormal(struct labirinto *labirinto, int linha, int coluna){

    int x, y, limiteLinha, limiteColuna, podeColocar;
    
    limiteLinha  = convertePosicoes(linha)  + 2;
    limiteColuna = convertePosicoes(coluna) + 2;
    podeColocar  = 1;

    for (y = convertePosicoes(linha); y <= limiteLinha ; y++){
        for (x = convertePosicoes(coluna) ; x <= limiteColuna ; x++){
            /* se tiver barreira ou for a posicao incial do pacman */
            if ( labirinto->matriz[y][x] == BARREIRA
            || ( y == POSI_LIN_INICIAL && x == POSI_COL_INICIAL ) ){

                podeColocar = 0;
                break;
            }
        }
    }

    if ( podeColocar )
        labirinto->matriz[limiteLinha - 1][limiteColuna - 1] = PASTILHA_NORMAL;

    return;
}


void criaPastilhaEspecial(struct labirinto *labirinto, int linha, int coluna){

    linha = convertePosicoes(linha);
    coluna = convertePosicoes(coluna);

    /* acrescenta a pastilha na matriz */
    labirinto->matriz[linha][coluna]         = PASTILHA_ESPECIAL;
    labirinto->matriz[linha - 1][coluna]     = PASTILHA_ESPECIAL;
    labirinto->matriz[linha][coluna + 1]     = PASTILHA_ESPECIAL;
    labirinto->matriz[linha - 1][coluna + 1] = PASTILHA_ESPECIAL;

    return;
}


int temPastilha(struct labirinto *labirinto){
    
    int linha, coluna;

    for (linha = 0; linha < labirinto->qtdLin ; linha ++){
        for (coluna = 0; coluna < labirinto->qtdCol ; coluna ++){
            /* se tiver alguma pastilha */
            if ( labirinto->matriz[linha][coluna] == PASTILHA_NORMAL
              || labirinto->matriz[linha][coluna] == PASTILHA_ESPECIAL )
                return 1;
        }
    }

    return 0;
}


void reiniciaJogo(struct jogo *jogo, struct pacman *pacman, int *direcao,
 int *direcaoAnterior, int *sucessoAoMover){
    
    /* coloca o pacman na posicao inicial */
    pacman->posiLin = POSI_LIN_INICIAL;
    pacman->posiCol = POSI_COL_INICIAL;

    /* aloca um novo labirinto */
    free(jogo->labirinto->matriz);
    free(jogo->labirinto);
    jogo->labirinto = criaLabirinto();

    /* ajusta a movimentacao */
    *direcao = *direcaoAnterior = KEY_LEFT;
    *sucessoAoMover = 1;

    /* limpa o labirinto anterior e imprime o novo */
    clear();
    mostraLabirinto(jogo->labirinto);
    mostraLayout(jogo, pacman);
    mostraPacman(pacman);
    refresh();

    return;
}


void adicionaPortao(struct labirinto *labirinto, int linha, int coluna){

    int x, y;
    int qtdLinhas = convertePosicoes(linha) + 1;
    int qtdColunas = convertePosicoes(coluna) + 2;

    for (x = convertePosicoes(linha) ; x <= qtdLinhas ; x++){
        for (y = convertePosicoes(coluna) ; y <= qtdColunas ; y++){
            if ( labirinto->matriz[x][y] != BARREIRA )
                labirinto->matriz[x][y] = PORTAO;
            else
                continue;
        }
    }
    return;
}

