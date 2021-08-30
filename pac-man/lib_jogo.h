#include "tad_fantasma.h"


/* _______________________________JOGO_______________________________________ */

/* delay de atualizacao do jogo */
#define DELAY 20000

/* definem o tamanho da matriz */
#define MAX_LIN 45 
#define MAX_COL 81

/* definem os valores de cada elemento na matriz */
#define PORTAO -2
#define BARREIRA -1
#define VAZIO 0
#define PASTILHA_NORMAL 1
#define PASTILHA_ESPECIAL 2

/* _______________________________CORES______________________________________ */

/* definem as cores de cada elemento na matriz */
#define COR_VAZIO 0
#define COR_BARREIRA 4
#define COR_PASTILHA 9
#define COR_PASTILHA_ESPECIAL 7
#define COR_PORTAO 5

/* ________________________FUNCOES E ESTRUTURAS______________________________ */

struct jogo {

    int pontos;
    int nivel;
    struct labirinto *labirinto;
};

struct labirinto {

    int qtdLin;
    int qtdCol; 
    int **matriz;
};


/* configuracoes inciais do ncurses */
int configuracoesIniciais();

/* configuracoes para finalizacao do jogo */
void finalizaJogo(struct jogo *jogo);

/* cria labirinto */
struct labirinto *criaLabirinto();

/* inicializa o jogo */
struct jogo *inicializaJogo();

/* adiciona barreiras do labirinto */
void adicionaBarreiras(struct labirinto *labirinto); 

/* cria as barreiras do labirinto na matriz */
void criaBarreira(struct labirinto *labirinto, int linha, int qtdLinhas,
 int coluna, int qtdColunas);

/* exibe o labirinto */
void mostraLabirinto(struct labirinto *labirinto);

/* checa se uma tecla foi pressionada */
int pegaTecla();

/* faz a checagem da colizao do pacman na direcao do movimento */
int colisaoPacman(struct jogo *jogo, int direcao, struct pacman *pacman);

/* transforma posicao do ncurses para matriz */
int convertePosicoes(int posicao);

/* adiciona as pastilhas normais no labirinto */
void adicionaPastilhas(struct labirinto *labirinto);

/* cria as pastilhas normais do labirinto na matriz, nas posicoes indicadas */
void criaPastilhaNormal(struct labirinto *labirinto, int linha, int coluna);

/* cria as pastilhas especiais do labirinto na matriz, nas posicoes indicadas */
void criaPastilhaEspecial(struct labirinto *labirinto, int linha, int coluna);

/* verifica se ainda tem pastilhas no labirinto */
int temPastilha(struct labirinto *labirinto);

/*configuracoes pra recomecar o jogo */
void reiniciaJogo(struct jogo *jogo, struct pacman *pacman, int *direcao,
 int *direcaoAnterior, int *sucessoAoMover);

/* adiciona o portao a barreira dos fantasmas */
void adicionaPortao(struct labirinto *labirinto, int linha, int coluna);

/* faz a checagem da colizao do fantasma em todas as direcoes */
void colisaoFantasmas(struct jogo *jogo, struct fantasma *fantasma, 
struct pacman *pacman);
