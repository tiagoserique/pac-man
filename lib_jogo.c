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
    init_color(COR_PINKY,   850, 550, 850);
    
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
    init_pair(COR_PINKY, COR_PINKY, COLOR_BLACK);
    /* Fantasma azul */    
    init_pair(COR_INKY, COLOR_CYAN, COLOR_BLACK);    
    /* Pastilha especial */   
    init_pair(COR_PASTILHA_ESPECIAL, COLOR_WHITE, COLOR_BLACK);       
    /* Portao */   
    init_pair(COR_PORTAO, COLOR_MAGENTA, COLOR_BLACK);       


    cbreak();               /* desabilita buffer na entrada          */
    noecho();               /* nao mostra o que foi digitado na tela */
    nodelay(stdscr, TRUE);  /* nao aguarda a digitacao               */
    keypad(stdscr, TRUE);   /* habilita as setas do teclado          */
    curs_set(FALSE);        /* nao mostra o cursor na tela           */

    return 1;
}


void finalizaJogo(struct jogo *jogo){

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

    criaBarreira(labirinto,   4,    6,  31,  51);
    
    criaBarreira(labirinto,  13,   21,   7,   9);
    criaBarreira(labirinto,  25,   33,   7,   9);
    criaBarreira(labirinto,  37,   39,   7,  21);
    
    criaBarreira(labirinto,  13,   21,  73,  75);
    criaBarreira(labirinto,  25,   33,  73,  75);
    criaBarreira(labirinto,  37,   39,  61,  75);

    criaBarreira(labirinto,  37,   39,  25,  33);
    criaBarreira(labirinto,  31,   39,  37,  45);
    criaBarreira(labirinto,  37,   39,  49,  57);
    
    criaBarreira(labirinto,  31,   33,  13,  33);
    criaBarreira(labirinto,  19,   27,  25,  30);

    criaBarreira(labirinto,  31,   33,  49,  69);
    criaBarreira(labirinto,  19,   27,  52,  57);
    
    criaBarreira(labirinto,   7,    9,   7,  12);
    criaBarreira(labirinto,   7,    9,  16,  27);
    criaBarreira(labirinto,  13,   15,  25,  27);

    criaBarreira(labirinto,  10,   15,  31,  39);

    criaBarreira(labirinto,  10,   15,  43,  51);
    
    criaBarreira(labirinto,   7,    9,  55,  66);
    criaBarreira(labirinto,  13,   15,  55,  57);
    criaBarreira(labirinto,   7,    9,  70,  75);

    criaBarreira(labirinto,  13,   18,  13,  21);
    criaBarreira(labirinto,  22,   27,  13,  15);
    criaBarreira(labirinto,  22,   27,  19,  21);

    criaBarreira(labirinto,  13,   18,  61,  69);
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


int colisaoPacman(struct jogo *jogo, int direcao, struct pacman *pacman){

    int linha, coluna, limite;

    /* determina os limites da checagem da colizao de acordo com direcao */
    switch ( direcao ){

        case KEY_UP :
            linha  = convertePosicoes(pacman->posicao->linha  - 2); 
            coluna = convertePosicoes(pacman->posicao->coluna - 1);
            limite = convertePosicoes(pacman->posicao->coluna + 1);
            break;

        case KEY_DOWN :
            linha  = convertePosicoes(pacman->posicao->linha  + 2);
            coluna = convertePosicoes(pacman->posicao->coluna - 1);
            limite = convertePosicoes(pacman->posicao->coluna + 1);
            break;

        case KEY_LEFT :
            linha  = convertePosicoes(pacman->posicao->linha  - 1);
            coluna = convertePosicoes(pacman->posicao->coluna - 2);
            limite = convertePosicoes(pacman->posicao->linha  + 1);
            break;

        case KEY_RIGHT :
            linha  = convertePosicoes(pacman->posicao->linha  - 1);
            coluna = convertePosicoes(pacman->posicao->coluna + 2);
            limite = convertePosicoes(pacman->posicao->linha  + 1);
            break;
    }

    if ( direcao == KEY_UP || direcao == KEY_DOWN){
        
        for ( ; coluna <= limite ; coluna++){

            /* se acha barreira na checagem */
            if ( jogo->labirinto->matriz[linha][coluna] == BARREIRA
              || jogo->labirinto->matriz[linha][coluna] == PORTAO ){
                return 0;
            }
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
                pacman->energizado = 1;
            }
        }
    }
    else if ( direcao == KEY_LEFT || direcao == KEY_RIGHT){
        
        for ( ; linha <= limite ; linha++){

            /* se acha barreira na checagem */
            if ( jogo->labirinto->matriz[linha][coluna] == BARREIRA ){
                return 0;
            }
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
                pacman->energizado = 1;
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

    int linha, coluna, casaDosFantasmas, posiTunel;

    for (linha = 1; linha <= labirinto->qtdLin - 2 ; linha += 3){
        for (coluna = 1; coluna <= labirinto->qtdCol - 2 ; coluna += 3){

            casaDosFantasmas = convertePosicoes(linha) >= 18 
                && convertePosicoes(linha)  <= 24 
                && convertePosicoes(coluna) >= 36 
                && convertePosicoes(coluna) <= 45;

            posiTunel = convertePosicoes(linha) >= 21
                &&   convertePosicoes(linha)    <= 23 
                && ( convertePosicoes(coluna)   <= 2 
                ||   convertePosicoes(coluna)   >= 78 );

            /* checa se a posicao eh valida para colocar pastilha */
            if ( !(casaDosFantasmas) && !(posiTunel) ) 
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
            || ( y == LIN_INICIAL && x == COL_INICIAL ) ){

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
    pacman->posicao->linha = LIN_INICIAL;
    pacman->posicao->coluna = COL_INICIAL;

    /* aloca um novo labirinto */
    free(jogo->labirinto->matriz);
    free(jogo->labirinto);
    jogo->labirinto = criaLabirinto();

    /* ajusta a movimentacao */
    *direcao = *direcaoAnterior = KEY_LEFT;
    *sucessoAoMover = 1;

    return;
}


void adicionaPortao(struct labirinto *labirinto, int linha, int coluna){

    int x, y;
    int qtdColunas = convertePosicoes(coluna) + 2;

    x = convertePosicoes(linha);
    for (y = convertePosicoes(coluna) ; y <= qtdColunas ; y++){
        if ( labirinto->matriz[x][y] != BARREIRA )
            labirinto->matriz[x][y] = PORTAO;
        else
            continue;
    }
    return;
}


void colisaoFantasmas(struct jogo *jogo, struct fantasma *fantasma, 
struct pacman *pacman){

    int linha, coluna, limite, coloca;

/* _______________________________BARREIRAS__________________________________ */

    /* cima */
    linha  = convertePosicoes(fantasma->posicao->linha  - 2); 
    coluna = convertePosicoes(fantasma->posicao->coluna - 1);
    limite = convertePosicoes(fantasma->posicao->coluna + 1);
    coloca = 1;

    for ( ; coluna <= limite ; coluna++){
        /* se acha barreira na checagem */
        if ( jogo->labirinto->matriz[linha][coluna] == BARREIRA ){
            coloca = 0;
            break;
        }
    }

    if ( coloca ){
        insereElemento(fantasma->direcoesDisponiveis, KEY_UP);
    }
    else {
        removeElemento(fantasma->direcoesDisponiveis, KEY_UP);
    }

    /* baixo */
    linha  = convertePosicoes(fantasma->posicao->linha  + 2);
    coluna = convertePosicoes(fantasma->posicao->coluna - 1);
    limite = convertePosicoes(fantasma->posicao->coluna + 1);
    coloca = 1;

    for ( ; coluna <= limite ; coluna++){
        /* se acha barreira na checagem */
        if ( jogo->labirinto->matriz[linha][coluna] == BARREIRA
        || jogo->labirinto->matriz[linha][coluna] == PORTAO ){
            coloca = 0;
            break;
        }
    }

    if ( coloca ){
        insereElemento(fantasma->direcoesDisponiveis, KEY_DOWN);
    }
    else {
        removeElemento(fantasma->direcoesDisponiveis, KEY_DOWN);
    }


    /* esquerda */
    linha  = convertePosicoes(fantasma->posicao->linha  - 1);
    coluna = convertePosicoes(fantasma->posicao->coluna - 2);
    limite = convertePosicoes(fantasma->posicao->linha  + 1);
    coloca = 1;

    for ( ; linha <= limite ; linha++){
        /* se acha barreira na checagem */
        if ( jogo->labirinto->matriz[linha][coluna] == BARREIRA ){
            coloca = 0;
            break;
        }
    }

    if ( coloca ){
        insereElemento(fantasma->direcoesDisponiveis, KEY_LEFT);
    }
    else {
        removeElemento(fantasma->direcoesDisponiveis, KEY_LEFT);
    }
    

    /* direita */
    linha  = convertePosicoes(fantasma->posicao->linha  - 1);
    coluna = convertePosicoes(fantasma->posicao->coluna + 2);
    limite = convertePosicoes(fantasma->posicao->linha  + 1);
    coloca = 1;

    for ( ; linha <= limite ; linha++){
        /* se acha barreira na checagem */
        if ( jogo->labirinto->matriz[linha][coluna] == BARREIRA ){
            coloca = 0;
            break;
        }
    }

    if ( coloca ){
        insereElemento(fantasma->direcoesDisponiveis, KEY_RIGHT);
    }
    else {
        removeElemento(fantasma->direcoesDisponiveis, KEY_RIGHT);
    }

/* __________________________COLISAO COM PACMAN______________________________ */

    int cima, baixo, esquerda, direita;

    cima     = (fantasma->posicao->linha - 1 == pacman->posicao->linha
            || fantasma->posicao->linha - 1 == pacman->posicao->linha + 1)
            && (fantasma->posicao->coluna - 1 == pacman->posicao->coluna - 1
            || fantasma->posicao->coluna + 1 == pacman->posicao->coluna + 1);


    baixo    = (fantasma->posicao->linha + 1 == pacman->posicao->linha
            || fantasma->posicao->linha + 1 == pacman->posicao->linha - 1)
            && (fantasma->posicao->coluna - 1 == pacman->posicao->coluna - 1
            || fantasma->posicao->coluna + 1 == pacman->posicao->coluna + 1);


    esquerda = (fantasma->posicao->coluna - 1 == pacman->posicao->coluna
            || fantasma->posicao->coluna - 1 == pacman->posicao->coluna + 1)
            && (fantasma->posicao->linha - 1 == pacman->posicao->linha - 1
            || fantasma->posicao->linha + 1 == pacman->posicao->linha + 1); 


    direita = (fantasma->posicao->coluna + 1 == pacman->posicao->coluna
            || fantasma->posicao->coluna + 1 == pacman->posicao->coluna - 1)
            && (fantasma->posicao->linha - 1 == pacman->posicao->linha - 1
            || fantasma->posicao->linha + 1 == pacman->posicao->linha + 1);


    if ( cima || baixo || esquerda || direita ){
        if ( !pacman->energizado || fantasma->comido > 0 ){
            pacman->vivo = 0;
        }
        else if ( pacman->energizado && fantasma->comido == 0){
            jogo->pontos += 200;
            fantasma->comido = 1;
        }
    }

    return;
}

