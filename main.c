#include "lib_telas.h"

int main(){

    if ( !configuracoesIniciais() ){
        return 1;
    }

/* __________________________INICIA PERSONAGENS______________________________ */
    
    struct pacman *pacman = criaPacman();
    pacman->posiLin = POSI_LIN_INICIAL;
    pacman->posiCol = POSI_COL_INICIAL;
    int delayPacman = DELAY_PACMAN;
    
    /* fantasma vermelho */
    struct fantasma *blinky = criaBlinky();

    struct fantasma *pinky = criaPinky();
  
    struct fantasma *inky  = criaInky();
    
    struct fantasma *clyde = criaClyde();
    


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
    exibeTudo(jogo, pacman, blinky, pinky, inky, clyde);
    refresh();


/* ___________________________LOOP PRINCIPAL_________________________________ */

    while ( pacman->vivo && pacman->vidas >= 0 ){
        
        /* passa de nivel quando nao tiver pastilhas */
        if ( !temPastilha(jogo->labirinto) ){
            if ( telaDeNovoNivel() ){

                reiniciaJogo(jogo, pacman, &direcao, &direcaoAnterior, &sucessoAoMover);
                
                jogo->nivel++;

                if ( delayPacman >= DELAY_LIMITE_PACMAN )
                    delayPacman -= 1;

                clear();
                exibeTudo(jogo, pacman, blinky, pinky, inky, clyde);
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

            jogo->pontos = 0;
            jogo->nivel = 1;

            clear();
            exibeTudo(jogo, pacman, blinky, pinky, inky, clyde);
            refresh();
        }

        /* controla a movimentacao */
        switch ( direcao ){

            /* se houver barreiras, move na direcao anterior */
            /* se nao houver barreiras, move na direcao apertada */
            case KEY_UP :
                
                sucessoAoMover = colizaoPacman(jogo, KEY_UP, pacman);

                if ( sucessoAoMover && !( tempo % delayPacman ) ){          
                    movePacman(KEY_UP, pacman);
                }
                else if ( colizaoPacman(jogo, direcaoAnterior, pacman) 
                && !(tempo % delayPacman) ){

                    movePacman(direcaoAnterior, pacman);
                }
                break;

            case KEY_DOWN :
                
                sucessoAoMover = colizaoPacman(jogo, KEY_DOWN, pacman);

                if ( sucessoAoMover && !(tempo % delayPacman) ){           
                    movePacman(KEY_DOWN, pacman);
                }
                else if ( colizaoPacman(jogo, direcaoAnterior, pacman)
                && !(tempo % delayPacman) ){

                    movePacman(direcaoAnterior, pacman);
                }
                break;

            case KEY_LEFT :
                
                sucessoAoMover = colizaoPacman(jogo, KEY_LEFT, pacman);

                if ( sucessoAoMover && !(tempo % delayPacman) ){       
                    movePacman(KEY_LEFT, pacman);
                }
                else if ( colizaoPacman(jogo, direcaoAnterior, pacman) 
                && !(tempo % delayPacman) ){

                    movePacman(direcaoAnterior, pacman);
                }
                break;

            case KEY_RIGHT :
                
                sucessoAoMover = colizaoPacman(jogo, KEY_RIGHT, pacman);
                
                if ( sucessoAoMover && !(tempo % delayPacman) ){   
                    movePacman(KEY_RIGHT, pacman);
                }
                else if ( colizaoPacman(jogo, direcaoAnterior, pacman) 
                && !(tempo % delayPacman) ){

                    movePacman(direcaoAnterior, pacman);
                }
                break;

            default :
                
                sucessoAoMover = 0;

                if ( colizaoPacman(jogo, direcaoAnterior, pacman) 
                && !(tempo % delayPacman) ){

                    movePacman(direcaoAnterior, pacman);
                }
                break;
        }

        if ( sucessoAoMover ){
            direcaoAnterior = direcao;
        }

        
        erase();     /* apaga a tela nas posicoes que sofreram modificacao */
        exibeTudo(jogo, pacman, blinky, pinky, inky, clyde);
        
        /* caso nao haja mais vidas, mostra tela de game over*/
        if ( pacman->vidas < 0 ){
            /* caso queira reiniciar o jogo*/
            if ( telaDeFimDeJogo() ){

                reiniciaJogo(jogo, pacman, &direcao, &direcaoAnterior, 
                &sucessoAoMover);

                jogo->pontos = 0;
                jogo->nivel = 1;
                
                pacman->vidas = VIDAS;
                pacman->vivo = 1;
                delayPacman = DELAY_PACMAN;

                clear();
                exibeTudo(jogo, pacman, blinky, pinky, inky, clyde);
            }
            /* caso queira sair do jogo*/
            else
                break;
        }
        
        usleep(DELAY); 
        refresh();

        /*
        if ( !pacman->vivo ){
            erase();
            pacman->posiLin = POSI_LIN_INICIAL;
            pacman->posiCol = POSI_COL_INICIAL;
            pacman->vivo    = 0;
            mostraPacman(pacman);

            reseta posi aliens 
            mostra os aliens

            refresh();
            sleep(3);
        }
        */

        tempo++;
        if ( tempo == 60000 ){
            tempo = 0;
        }
    }

    destroiPacman(pacman);
    finalizaJogo(jogo);

    return 0;
}
