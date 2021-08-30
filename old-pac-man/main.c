#include "lib_jogo.h"
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
    mostraLabirinto(jogo->labirinto);
    mostraLayout(jogo, pacman);
    mostraPacman(pacman);
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
        }

        /* controla a movimentacao */
        switch ( direcao ){

            /* se houver barreiras, move na direcao anterior */
            /* se nao houver barreiras, move na direcao apertada */
            case KEY_UP :
                
                sucessoAoMover = checaColizao(jogo, KEY_UP, pacman);

                if ( sucessoAoMover && !( tempo % delayPacman ) ){          
                    movePacman(KEY_UP, pacman);
                }
                else if ( checaColizao(jogo, direcaoAnterior, pacman) 
                && !(tempo % delayPacman) ){

                    movePacman(direcaoAnterior, pacman);
                }
                break;

            case KEY_DOWN :
                
                sucessoAoMover = checaColizao(jogo, KEY_DOWN, pacman);

                if ( sucessoAoMover && !(tempo % delayPacman) ){           
                    movePacman(KEY_DOWN, pacman);
                }
                else if ( checaColizao(jogo, direcaoAnterior, pacman)
                && !(tempo % delayPacman) ){

                    movePacman(direcaoAnterior, pacman);
                }
                break;

            case KEY_LEFT :
                
                sucessoAoMover = checaColizao(jogo, KEY_LEFT, pacman);

                if ( sucessoAoMover && !(tempo % delayPacman) ){       
                    movePacman(KEY_LEFT, pacman);
                }
                else if ( checaColizao(jogo, direcaoAnterior, pacman) 
                && !(tempo % delayPacman) ){

                    movePacman(direcaoAnterior, pacman);
                }
                break;

            case KEY_RIGHT :
                
                sucessoAoMover = checaColizao(jogo, KEY_RIGHT, pacman);
                
                if ( sucessoAoMover && !(tempo % delayPacman) ){   
                    movePacman(KEY_RIGHT, pacman);
                }
                else if ( checaColizao(jogo, direcaoAnterior, pacman) 
                && !(tempo % delayPacman) ){

                    movePacman(direcaoAnterior, pacman);
                }
                break;

            default :
                
                sucessoAoMover = 0;

                if ( checaColizao(jogo, direcaoAnterior, pacman) 
                && !(tempo % delayPacman) ){

                    movePacman(direcaoAnterior, pacman);
                }
                break;
        }

        if ( sucessoAoMover ){
            direcaoAnterior = direcao;
        }

        /* atualiza a tela nas posicoes que sofreram modificacao */
        erase();
        mostraLabirinto(jogo->labirinto);
        mostraLayout(jogo, pacman);
        mostraPacman(pacman);
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
            }
            /* caso queira sair do jogo*/
            else
                break;
        }
        usleep(DELAY); 
        refresh();

        tempo++;
        if ( tempo == 60000 ){
            tempo = 0;
        }
    }

    finalizaJogo(jogo, pacman);

    return 0;
}
