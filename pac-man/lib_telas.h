#include "lib_jogo.h"


/* chama a tela de fim de jogo */
int telaDeFimDeJogo();

/* chama a tela de novo nivel */
int telaDeNovoNivel();

/* exibe o layout do jogo */
void mostraLayout(int pontos, int nivel, int vidas);

/* faz a chamada de tudo que deve ser mostrado na tela */
void exibeTudo(struct jogo *jogo, struct pacman *pacman, struct fantasma *blinky,
struct fantasma *pinky, struct fantasma *inky, struct fantasma *clyde,
 int versaoFantasma);