#ifndef _PACMAN_H_
#define _PACMAN_H_
#define LEFT 'a'
#define UP 'w'
#define DOWN 's'
#define RIGHT 'd'
#define BOMB 'b'

int end();
void move(char direction);
int isDirection(char direction);
void ghosts();
int directionGhosts(int xAtual, int yAtual, int* xDestiny, int* yDestiny);
void explodeEnergizers();
void explodeEnergizers2(int x, int y, int sumX, int sumY, int qtd);

#endif
