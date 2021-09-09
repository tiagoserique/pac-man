#include "lib_game.h"
#include "lib_screen.h"

int main(){

    if ( !initialSettings() ){
        return 1;
    }

/* __________________________INICIA PERSONAGENS______________________________ */
    
    struct pacman *pacman = createPacman();
    pacman->rowPosition = INITIAL_ROW_POSITION;
    pacman->columnPosition = INITIAL_COLUMN_POSITION;
    int delayPacman = DELAY_PACMAN;

/* _____________________________INICIA JOGO___________________________________*/

    struct game *game;
    int direction, previousDirection, successfullyMove, time;
    
    /* inicia o jogo */
    game = startGame();

    /* ajusta a movimentacao */
    direction = previousDirection = KEY_LEFT;
    successfullyMove = 1;

    /* imprime os elementos do jogo */
    erase();
    showMaze(game->maze);
    showLayout(game, pacman);
    showPacman(pacman);
    refresh();


/* ___________________________LOOP PRINCIPAL_________________________________ */

    while ( pacman->alive && pacman->lifes >= 0 ){
        
        /* passa de nivel quando nao tiver pastilhas */
        if ( !hasDots(game->maze) ){
            if ( newLevelScreen() ){

                restartGame(game, pacman, &direction, &previousDirection, &successfullyMove);
                game->level++;

                if ( delayPacman >= PACMAN_DELAY_LIMIT )
                    delayPacman -= 1;
            }
            else
                break;
        }
                
        /* verifica se houve alguma tecla apertada */
        if ( getKey() ){
            direction = getch();
        }

        /* finaliza jogo caso "q" seja apertado */
        if ( direction == 'q' ){
            break;
        }

        /* reinicia jogo caso "r" seja apertado */
        if ( direction == 'r'){

            restartGame(game, pacman, &direction, &previousDirection, &successfullyMove);
            game->points = 0;
            game->level = 1;
        }

        /* controla a movimentacao */
        switch ( direction ){

            /* se houver barreiras, move na direcao anterior */
            /* se nao houver barreiras, move na direcao apertada */
            case KEY_UP :
                
                successfullyMove = checkCollision(game, KEY_UP, pacman);

                if ( successfullyMove && !( time % delayPacman ) ){          
                    movePacman(KEY_UP, pacman);
                }
                else if ( checkCollision(game, previousDirection, pacman) 
                && !(time % delayPacman) ){

                    movePacman(previousDirection, pacman);
                }
                break;

            case KEY_DOWN :
                
                successfullyMove = checkCollision(game, KEY_DOWN, pacman);

                if ( successfullyMove && !(time % delayPacman) ){           
                    movePacman(KEY_DOWN, pacman);
                }
                else if ( checkCollision(game, previousDirection, pacman)
                && !(time % delayPacman) ){

                    movePacman(previousDirection, pacman);
                }
                break;

            case KEY_LEFT :
                
                successfullyMove = checkCollision(game, KEY_LEFT, pacman);

                if ( successfullyMove && !(time % delayPacman) ){       
                    movePacman(KEY_LEFT, pacman);
                }
                else if ( checkCollision(game, previousDirection, pacman) 
                && !(time % delayPacman) ){

                    movePacman(previousDirection, pacman);
                }
                break;

            case KEY_RIGHT :
                
                successfullyMove = checkCollision(game, KEY_RIGHT, pacman);
                
                if ( successfullyMove && !(time % delayPacman) ){   
                    movePacman(KEY_RIGHT, pacman);
                }
                else if ( checkCollision(game, previousDirection, pacman) 
                && !(time % delayPacman) ){

                    movePacman(previousDirection, pacman);
                }
                break;

            default :
                
                successfullyMove = 0;

                if ( checkCollision(game, previousDirection, pacman) 
                && !(time % delayPacman) ){

                    movePacman(previousDirection, pacman);
                }
                break;
        }

        if ( successfullyMove ){
            previousDirection = direction;
        }

        /* atualiza a tela nas posicoes que sofreram modificacao */
        erase();
        showMaze(game->maze);
        showLayout(game, pacman);
        showPacman(pacman);
        /* caso nao haja mais vidas, mostra tela de game over*/
        if ( pacman->lifes < 0 ){
            /* caso queira reiniciar o jogo*/
            if ( endGameScreen() ){

                restartGame(game, pacman, &direction, &previousDirection, 
                &successfullyMove);
                
                game->points = 0;
                game->level = 1;
                
                pacman->lifes = LIFES;
                pacman->alive = 1;
                delayPacman = DELAY_PACMAN;
            }
            /* caso queira sair do jogo*/
            else
                break;
        }
        usleep(DELAY); 
        refresh();

        time++;
        if ( time == 60000 ){
            time = 0;
        }
    }

    endGame(game, pacman);

    return 0;
}
