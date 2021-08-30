#include "lib_telas.h"

int main(){

    if ( !configuracoesIniciais() ){
        return 1;
    }

    /* define uma seed para gerar numeros aleatorios */
    srand(time(NULL)); 

/* __________________________INICIA PERSONAGENS______________________________ */


    struct pacman *pacman = criaPacman();
    int delayPacman = DELAY_PACMAN; 

    struct fantasma *blinky = criaFantasma(BLINKY, 17, 41); /* fantasma vermelho */
    struct fantasma *pinky  = criaFantasma(PINKY,  23, 41); /* fantasma rosa     */
    struct fantasma *inky   = criaFantasma(INKY,   23, 38); /* fantasma azul     */
    struct fantasma *clyde  = criaFantasma(CLYDE,  23, 44); /* fantasma amarelo  */
    int delayFantasmas = DELAY_FANTASMAS;
    int versaoFantasma = 0; /* determina a cor quando os fantasmas devem fugir */
    int tempoInky  = 0;
    int tempoClyde = 0;

/* _____________________________INICIA JOGO___________________________________*/


    struct jogo *jogo;
    int direcao, direcaoAnterior, sucessoAoMover, tempo;
    
    /* inicia o jogo */
    jogo = inicializaJogo();

    /* ajusta a movimentacao */
    direcao = direcaoAnterior = KEY_LEFT;
    sucessoAoMover = 1;

    /* imprime os elementos do jogo */
    erase();
    exibeTudo(jogo, pacman, blinky, pinky, inky, clyde, versaoFantasma);
    refresh();
    sleep(1);

/* ___________________________LOOP PRINCIPAL_________________________________ */


    while ( pacman->vivo && pacman->vidas >= 0 ){

        /* passa de nivel quando nao tiver pastilhas */
        if ( !temPastilha(jogo->labirinto) ){
            if ( telaDeNovoNivel() ){

                reiniciaJogo(jogo, pacman, &direcao, &direcaoAnterior,
                 &sucessoAoMover);
                
                reiniciaPosicaoFantasma(blinky);
                reiniciaPosicaoFantasma(pinky);
                reiniciaPosicaoFantasma(inky);
                reiniciaPosicaoFantasma(clyde);
                blinky->fugir = blinky->comido = 0;
                pinky->fugir  = pinky->comido  = 0;
                inky->fugir   = inky->comido   = 0;
                clyde->fugir  = clyde->comido  = 0;

                jogo->nivel++;

                if ( delayPacman >= LIMITE_DELAY_PACMAN )
                    delayPacman -= 1;
                pacman->tempoEnergizado = 0;

                if ( delayFantasmas >= LIMITE_DELAY_FANTASMAS )
                    delayFantasmas -= 1;

                clear();
                exibeTudo(jogo, pacman, blinky, pinky, inky, clyde, versaoFantasma);
                refresh();
            }
            else
                break;
        }


        /* verifica se houve alguma tecla apertada */
        if ( pegaTecla() ){
            direcao = getch();
        }


        /* finaliza jogo caso "q" seja apertado */
        if ( direcao == 'q' ){
            break;
        }


        /* reinicia jogo caso "r" seja apertado */
        if ( direcao == 'r'){
            reiniciaJogo(jogo, pacman, &direcao, &direcaoAnterior, &sucessoAoMover);

            reiniciaPosicaoFantasma(blinky);
            reiniciaPosicaoFantasma(pinky);
            reiniciaPosicaoFantasma(inky);
            reiniciaPosicaoFantasma(clyde);
            delayFantasmas = DELAY_FANTASMAS;
            blinky->fugir = blinky->comido = 0;
            pinky->fugir  = pinky->comido  = 0;
            inky->fugir   = inky->comido   = 0;
            clyde->fugir  = clyde->comido  = 0;
            tempoInky  = 0;
            tempoClyde = 0;

            pacman->tempoEnergizado = 0;
            jogo->pontos = 0;
            jogo->nivel  = 1;

            clear();
            exibeTudo(jogo, pacman, blinky, pinky, inky, clyde, versaoFantasma);
            refresh();
        }


        /* controla a movimentacao */
        switch ( direcao ){

            /* se houver barreiras, move na direcao anterior */
            /* se nao houver barreiras, move na direcao apertada */
            case KEY_UP :
                sucessoAoMover = colisaoPacman(jogo, KEY_UP, pacman);

                if ( sucessoAoMover && !( tempo % delayPacman ) ){          
                    movePacman(KEY_UP, pacman);
                }
                else if ( colisaoPacman(jogo, direcaoAnterior, pacman) 
                && !(tempo % delayPacman) ){
                    movePacman(direcaoAnterior, pacman);
                }
                break;


            case KEY_DOWN :
                sucessoAoMover = colisaoPacman(jogo, KEY_DOWN, pacman);

                if ( sucessoAoMover && !(tempo % delayPacman) ){           
                    movePacman(KEY_DOWN, pacman);
                }
                else if ( colisaoPacman(jogo, direcaoAnterior, pacman)
                && !(tempo % delayPacman) ){
                    movePacman(direcaoAnterior, pacman);
                }
                break;


            case KEY_LEFT :
                sucessoAoMover = colisaoPacman(jogo, KEY_LEFT, pacman);

                if ( sucessoAoMover && !(tempo % delayPacman) ){       
                    movePacman(KEY_LEFT, pacman);
                }
                else if ( colisaoPacman(jogo, direcaoAnterior, pacman) 
                && !(tempo % delayPacman) ){
                    movePacman(direcaoAnterior, pacman);
                }
                break;


            case KEY_RIGHT :
                sucessoAoMover = colisaoPacman(jogo, KEY_RIGHT, pacman);
                
                if ( sucessoAoMover && !(tempo % delayPacman) ){   
                    movePacman(KEY_RIGHT, pacman);
                }
                else if ( colisaoPacman(jogo, direcaoAnterior, pacman) 
                && !(tempo % delayPacman) ){
                    movePacman(direcaoAnterior, pacman);
                }
                break;


            default :
                sucessoAoMover = 0;

                if ( colisaoPacman(jogo, direcaoAnterior, pacman) 
                && !(tempo % delayPacman) ){
                    movePacman(direcaoAnterior, pacman);
                }
                break;
        }


        /* determina se a direcao deve ser atualizada ou nao */
        if ( sucessoAoMover ){
            direcaoAnterior = direcao;
        }


        /* faz a temporizacao do power up */
        if ( pacman->energizado ){
            pacman->tempoEnergizado++;

            if ( pacman->tempoEnergizado > DELAY_ENERGIZADO ){
                pacman->energizado = 0;
                pacman->tempoEnergizado = 0;
            }
        }


        /* movimenta os fantasmas */
        if ( !(tempo % delayFantasmas) ){
            int direcaoFantasma;
            colisaoFantasmas(jogo, blinky, pacman);
            direcaoFantasma = escolheDirecao(blinky, pacman, direcao);
            moveFantasma(blinky, direcaoFantasma);

            colisaoFantasmas(jogo, pinky, pacman);
            direcaoFantasma = escolheDirecao(pinky, pacman, direcao);
            moveFantasma(pinky, direcaoFantasma);

            if ( tempoInky++ >= 20 ){
                colisaoFantasmas(jogo, inky, pacman);
                inky->alvo->linha  = blinky->posicao->linha;
                inky->alvo->coluna = blinky->posicao->coluna;
                direcaoFantasma = escolheDirecao(inky, pacman, direcao);
                moveFantasma(inky, direcaoFantasma);
                tempoInky = 20;
            }

            if ( tempoClyde++ >= 40 ){
                colisaoFantasmas(jogo, clyde, pacman);
                direcaoFantasma = escolheDirecao(clyde, pacman, direcao);
                moveFantasma(clyde, direcaoFantasma);
                tempoClyde = 40;
            }

            fogeOuPersegue(blinky, pacman);            
            fogeOuPersegue(pinky,  pacman);            
            fogeOuPersegue(inky,   pacman);            
            fogeOuPersegue(clyde,  pacman);

            if ( versaoFantasma ){
                versaoFantasma = 0;
            }
            else {
                versaoFantasma = 1;
            }
            
        }


        /* apaga a tela nas posicoes que sofreram modificacao */
        erase();     
        exibeTudo(jogo, pacman, blinky, pinky, inky, clyde, versaoFantasma);
        
        if ( !pacman->vivo ){
            erase();
            pacman->posicao->linha = LIN_INICIAL;
            pacman->posicao->coluna = COL_INICIAL;
            pacman->vivo    = 1;
            pacman->vidas  -= 1;
            pacman->energizado = 0;

            direcao = direcaoAnterior = KEY_LEFT;

            reiniciaPosicaoFantasma(blinky);
            reiniciaPosicaoFantasma(pinky);
            reiniciaPosicaoFantasma(inky);
            reiniciaPosicaoFantasma(clyde);
            blinky->fugir = 0;
            pinky->fugir  = 0;
            inky->fugir   = 0;
            clyde->fugir  = 0;
            tempoInky  = 0;
            tempoClyde = 0;

            exibeTudo(jogo, pacman, blinky, pinky, inky, clyde, versaoFantasma);

            refresh();

            if ( pacman->vidas > 0 )
                sleep(2);
        }
        
        /* mostra tela de game over */
        if ( pacman->vidas == 0 ){
            
            /* reiniciar o jogo */
            if ( telaDeFimDeJogo() ){
                reiniciaJogo(jogo, pacman, &direcao, &direcaoAnterior, 
                &sucessoAoMover);

                reiniciaPosicaoFantasma(blinky);
                reiniciaPosicaoFantasma(pinky);
                reiniciaPosicaoFantasma(inky);
                reiniciaPosicaoFantasma(clyde);
                delayFantasmas = DELAY_FANTASMAS;
                blinky->fugir = blinky->comido = 0;
                pinky->fugir  = pinky->comido  = 0;
                inky->fugir   = inky->comido   = 0;
                clyde->fugir  = clyde->comido  = 0;
                tempoInky  = 0;
                tempoClyde = 0;

                jogo->pontos = 0;
                jogo->nivel  = 1;
                
                pacman->vidas = VIDAS;
                pacman->vivo = 1;
                delayPacman = DELAY_PACMAN;
                pacman->tempoEnergizado = 0;

                clear();
                exibeTudo(jogo, pacman, blinky, pinky, inky, clyde, versaoFantasma);
            }
            /* sai do jogo */
            else
                break;
        }
        
        usleep(DELAY); 
        refresh();


        tempo++;
        tempo = tempo % 600000;
    }

    destroiFantasma(blinky);
    destroiFantasma(pinky);
    destroiFantasma(inky);
    destroiFantasma(clyde);
    
    destroiPacman(pacman);

    finalizaJogo(jogo);

    return 0;
}
