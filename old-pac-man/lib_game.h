#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include "adt_pacman.h"


/* _______________________________PACMAN_____________________________________ */

/* delay de velocidade do pacman */
#define DELAY_PACMAN 8
#define PACMAN_DELAY_LIMIT 3

/* definem a posicao inicial do pacman no ncurses */
#define INITIAL_ROW_POSITION 41 
#define INITIAL_COLUMN_POSITION 41 

/* _______________________________JOGO_______________________________________ */

/* delay de atualizacao do jogo */
#define DELAY 20000

/* definem o tamanho da matriz */
#define MAX_ROW 45 
#define MAX_COL 81

/* definem os valores de cada elemento na matriz */
#define GATE -2
#define BARRIER -1
#define EMPTY 0
#define DOTS 1
#define ENERGIZERS 2

/* _______________________________CORES______________________________________ */

/* definem as cores de cada elemento na matriz */
#define EMPTY_COLOR 0
#define BARRIER_COLOR 1
#define PACMAN_COLOR 2
#define DOTS_COLOR 3
#define BLINKY_COLOR 4
#define CLYDE_COLOR 5
#define PINKY_COLOR 6
#define INKY_COLOR 7
#define ENERGIZERS_COLOR 8
#define GATE_COLOR 9

/* ________________________FUNCOES E ESTRUTURAS______________________________ */

struct game {

    int points;
    int level;
    struct maze *maze;
};

struct maze {

    int numRow;
    int numCol; 
    int **matrix;
};


/* configuracoes inciais do ncurses */
int initialSettings();

/* configuracoes para finalizacao do jogo */
void endGame(struct game *game, struct pacman *pacman);

/* cria labirinto */
struct maze *createMaze();

/* inicializa o jogo */
struct game *startGame();

/* adiciona barreiras do labirinto */
void addBarriers(struct maze *maze); 

/* cria as barreiras do labirinto na matriz */
void createBarrier(struct maze *maze, int row, int numRows,
 int column, int numColumns);

/* exibe o labirinto */
void showMaze(struct maze *maze);

/* exibe o layout do jogo */
void showLayout(struct game *game, struct pacman *pacman);

/* checa se uma tecla foi pressionada */
int getKey();

/* faz a checagem da colizao do personagem na direcao do movimento */
int checkCollision(struct game *game, int direction, struct pacman *pacman);

/* transforma posicao do ncurses para matriz */
int convertPositions(int position);

/* adiciona as pastilhas normais no labirinto */
void addDots(struct maze *maze);

/* cria as pastilhas normais do labirinto na matriz, nas posicoes indicadas */
void createDots(struct maze *maze, int row, int column);

/* cria as pastilhas especiais do labirinto na matriz, nas posicoes indicadas */
void createEnergizers(struct maze *maze, int row, int column);

/* verifica se ainda tem pastilhas no labirinto */
int hasDots(struct maze *maze);

/*configuracoes pra recomecar o jogo */
void restartGame(struct game *game, struct pacman *pacman, int *direction,
 int *previousDirection, int *successfullyMove);

/* adiciona o portao a barreira dos fantasmas */
void addGate(struct maze *maze, int row, int column);

