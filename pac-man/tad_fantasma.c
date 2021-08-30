#include "tad_fantasma.h"


struct fantasma *criaFantasma(int id, int linhaInicial, int colunaInicial){

    struct fantasma *temp;

    temp = malloc(sizeof(struct fantasma));
    
    temp->id      = id; 
    temp->posicao = criaCoord(linhaInicial, colunaInicial);
    temp->alvo    = criaCoord(0, 0);
    temp->fugir   = 0;
    temp->comido  = 0;
    temp->direcoesDisponiveis = criaLista();
    temp->dirAtual = 0;

    return temp;
}


void mostraFantasma(struct fantasma *fantasma, int versaoFantasma){
    
    int x, y, atributo;

    if ( !fantasma->fugir ){

        if ( fantasma->id == BLINKY )
            atributo = A_REVERSE | COLOR_PAIR(COR_BLINKY);
        else if ( fantasma->id == PINKY )
            atributo = A_REVERSE | COLOR_PAIR(COR_PINKY);
        else if ( fantasma->id == INKY )
            atributo = A_REVERSE | COLOR_PAIR(COR_INKY);
        else if ( fantasma->id == CLYDE )
            atributo = A_REVERSE | COLOR_PAIR(COR_CLYDE);
    }
    else if ( fantasma->fugir && versaoFantasma ){
        atributo = A_REVERSE | COLOR_PAIR(0);
    }
    else if ( fantasma->fugir && !versaoFantasma ){
        atributo = A_REVERSE | COLOR_PAIR(COLOR_BLUE);
    }

    /* mostra o fantasma inteiro caso esteja entre essas posicoes */
    if ( fantasma->posicao->coluna >= 2 && fantasma->posicao->coluna <= 80 ){
        for (y = fantasma->posicao->linha - 1; y <= fantasma->posicao->linha + 1 ; y++){
            for (x = fantasma->posicao->coluna - 1; x <= fantasma->posicao->coluna + 1 ; x++){
                attron(atributo);
                mvprintw(y, x, " ");
                attroff(atributo);
            }
        }
    }
    /* atravessa o mapa */
    else
        fantasmaAtravessaMapa(fantasma, atributo);

    return;
}


void fantasmaAtravessaMapa(struct fantasma *fantasma, int atributo){

    int x, y, temp;

    attron(atributo);

    /* faz o desenho das partes do fantasma quando passa dos limites */
    if ( fantasma->posicao->coluna == 81 || fantasma->posicao->coluna == 0 ){
        temp = 1;
        if ( fantasma->posicao->coluna == 0 )
            fantasma->posicao->coluna = 81;

        for (y = fantasma->posicao->linha - 1; y <= fantasma->posicao->linha + 1; y++){
            for (x = fantasma->posicao->coluna - 1; x <= fantasma->posicao->coluna ; x++){
                mvprintw(y, x, " ");
            }
            mvprintw(y, temp, " ");
        }
    }
    else if ( fantasma->posicao->coluna == 1 || fantasma->posicao->coluna == 82 ){
        temp = 81;
        if ( fantasma->posicao->coluna == 82 )
            fantasma->posicao->coluna = 1;

        for (y = fantasma->posicao->linha - 1; y <= fantasma->posicao->linha + 1; y++){
            for (x = fantasma->posicao->coluna; x <= fantasma->posicao->coluna + 1 ; x++){
                mvprintw(y, x, " ");
            }
            mvprintw(y, temp, " ");
        }
    }

    attroff(atributo);

    return;
}


void defineAlvos(struct fantasma *fantasma, struct pacman *pacman, 
int direcaoPacman){

    int cima, baixo, esquerda, direita;

    int dentroDaCasa = fantasma->posicao->linha  >= 19 
                    && fantasma->posicao->linha  <= 24 
                    && fantasma->posicao->coluna >= 36 
                    && fantasma->posicao->coluna <= 45;

    switch(fantasma->id){
        case BLINKY:
            if ( !fantasma->fugir ){
                fantasma->alvo->linha  = pacman->posicao->linha;
                fantasma->alvo->coluna = pacman->posicao->coluna;
            }
            else {
                fantasma->alvo->linha  = ( rand() % 45 ) + 1;
                fantasma->alvo->coluna = ( rand() % 81 ) + 1;
            }
            break;


        case PINKY:
            if ( !dentroDaCasa && !fantasma->fugir ){
                if ( direcaoPacman == KEY_UP ){
                    fantasma->alvo->linha = pacman->posicao->linha - 5;
                    fantasma->alvo->coluna = pacman->posicao->coluna;
                }
                else if ( direcaoPacman == KEY_DOWN ){
                    fantasma->alvo->linha = pacman->posicao->linha + 5;
                    fantasma->alvo->coluna = pacman->posicao->coluna;
                }
                else if ( direcaoPacman == KEY_LEFT ){
                    fantasma->alvo->linha = pacman->posicao->linha;
                    fantasma->alvo->coluna = pacman->posicao->coluna - 5;
                }
                else if ( direcaoPacman == KEY_RIGHT ){
                    fantasma->alvo->linha = pacman->posicao->linha;
                    fantasma->alvo->coluna = pacman->posicao->coluna + 5;
                }
            }
            else if ( fantasma->fugir ){
                fantasma->alvo->linha  = ( rand() % 45 ) + 1;
                fantasma->alvo->coluna = ( rand() % 81 ) + 1;
            }
            else {
                fantasma->alvo->linha  = 17;
                fantasma->alvo->coluna = 41;
            }
            break;


        case INKY:
            if ( !dentroDaCasa && !fantasma->fugir ){
                fantasma->alvo->linha  += pacman->posicao->linha;
                fantasma->alvo->linha  /= 2;
                fantasma->alvo->coluna += pacman->posicao->coluna;
                fantasma->alvo->coluna /= 2;
            }
            else if ( fantasma->fugir ){
                fantasma->alvo->linha  = ( rand() % 45 ) + 1;
                fantasma->alvo->coluna = ( rand() % 81 ) + 1;
            }
            else {
                fantasma->alvo->linha  = 17;
                fantasma->alvo->coluna = 41;
            }
            break;


        case CLYDE:
            if ( !dentroDaCasa && !fantasma->fugir ){
                cima     = fantasma->posicao->linha  - 15 == pacman->posicao->linha;
                baixo    = fantasma->posicao->linha  + 15 == pacman->posicao->linha;
                esquerda = fantasma->posicao->coluna - 15 == pacman->posicao->coluna;
                direita  = fantasma->posicao->coluna + 15 == pacman->posicao->coluna;

                if ( cima || baixo || direita || esquerda ){
                    fantasma->alvo->linha  = pacman->posicao->linha;
                    fantasma->alvo->coluna = pacman->posicao->coluna;
                }
                else {
                    fantasma->alvo->linha  = ( rand() % 45 ) + 1;
                    fantasma->alvo->coluna = ( rand() % 81 ) + 1;
                }
            }
            else if ( fantasma->fugir ){
                fantasma->alvo->linha  = ( rand() % 45 ) + 1;
                fantasma->alvo->coluna = ( rand() % 81 ) + 1;
            }
            else {
                fantasma->alvo->linha  = 17;
                fantasma->alvo->coluna = 41;
            }
            break;
    }

    return;
}


int escolheDirecao(struct fantasma *fantasma, struct pacman *pacman, 
int direcaoPacman){

    int temNovaDirecao = fantasma->direcoesDisponiveis->temNovoNodo;

    if ( temNovaDirecao ){
        defineAlvos(fantasma, pacman, direcaoPacman);
        fantasma->dirAtual = direcaoComMenorDistancia(fantasma);
    }

    return fantasma->dirAtual;
}


int direcaoComMenorDistancia(struct fantasma *fantasma){

    struct nodo *aux = fantasma->direcoesDisponiveis->inicio;
    int direcao = 0, dirMenor = 0;
    int menorDistancia = 900000;
    int distancia = 0;

    /* varre a lista com as direcoes disponiveis para o fantasma seguir */
    while ( aux != NULL ){
        direcao = aux->valor;
        if ( direcao == KEY_UP ){
            distancia = calculaDistancia(fantasma->posicao->linha - 1, 
            fantasma->posicao->coluna, fantasma->alvo->linha, fantasma->alvo->coluna);
        }
        else if ( direcao == KEY_DOWN ){
            distancia = calculaDistancia(fantasma->posicao->linha + 1, 
            fantasma->posicao->coluna, fantasma->alvo->linha, fantasma->alvo->coluna);
        }
        else if ( direcao == KEY_LEFT ){
            distancia = calculaDistancia(fantasma->posicao->linha, 
            fantasma->posicao->coluna - 1, fantasma->alvo->linha, fantasma->alvo->coluna);
        }
        else if ( direcao == KEY_RIGHT ){
            distancia = calculaDistancia(fantasma->posicao->linha, 
            fantasma->posicao->coluna + 1, fantasma->alvo->linha, fantasma->alvo->coluna);
        }

        if ( distancia < menorDistancia ){
            menorDistancia = distancia;
            dirMenor = direcao;
        }

        aux = aux->prox;
    }

    return dirMenor;
}


int calculaDistancia(int linha, int coluna, int linhaAlvo, int colunaAlvo){
    
    /* formula da distancia entre dois pontos */
    int dist = (linha - linhaAlvo) * (linha - linhaAlvo) + 
            (coluna - colunaAlvo) * (coluna - colunaAlvo);

    return dist;
}


void moveFantasma(struct fantasma *fantasma, int direcao){

    if ( direcao == KEY_UP ){
        fantasma->posicao->linha -= 1;
    }
    else if ( direcao == KEY_DOWN ){
        fantasma->posicao->linha += 1;
    }
    else if ( direcao == KEY_LEFT ){
        fantasma->posicao->coluna -= 1;
    }
    else if ( direcao == KEY_RIGHT ){
        fantasma->posicao->coluna += 1;
    }

    /* zera a variavel que identifica novos nodos na lista */
    /* usada para detectar as encruzilhadas/novos caminhos */
    fantasma->direcoesDisponiveis->temNovoNodo = 0;

    return;
}


void reiniciaPosicaoFantasma(struct fantasma *fantasma){

    esvaziaLista(fantasma->direcoesDisponiveis);

    /* fantasma vermelho */
    if ( fantasma->id == BLINKY ){
        fantasma->posicao->linha  = 17; 
        fantasma->posicao->coluna = 41;
    }
    /* fantasma rosa */
    else if ( fantasma->id == PINKY ){
        fantasma->posicao->linha   = 23; 
        fantasma->posicao->coluna  = 41; 
    }
    /* fantasma azul */
    else if ( fantasma->id == INKY ){
        fantasma->posicao->linha    = 23; 
        fantasma->posicao->coluna   = 38; 
    }
    /* fantasma amarelo */
    else if ( fantasma->id == CLYDE ){    
        fantasma->posicao->linha   = 23; 
        fantasma->posicao->coluna  = 44; 
    }

    return;
}


int foiComido(struct fantasma *fantasma){

    /* foi comido */
    if ( fantasma->comido == 1 ){
        reiniciaPosicaoFantasma(fantasma);
        fantasma->comido = 2;
    }
    /* nao foi comido */
    else if ( fantasma->comido == 0 ){
        return 0;
    }

    return 1;
}


void fogeOuPersegue(struct fantasma *fantasma, struct pacman *pacman){
    
    /* se o pacman estiver energizado, determina se foge ou persegue */
    if ( pacman->energizado )
        fantasma->fugir = !foiComido(fantasma);
    else 
    /* se nao estiver energizado, persegue */
        fantasma->fugir = fantasma->comido = 0;
    
    return;
}


void destroiFantasma(struct fantasma *fantasma){

    destroiLista(fantasma->direcoesDisponiveis);
    free(fantasma->posicao);
    free(fantasma->alvo);
    free(fantasma);

    return;
}
