#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pacman.h"
#include "map.h"
#include "ui.h"

MAP m;
POSITION hero;
int hasEnergizers = 0;

int directionGhosts(int xAtual, int yAtual, int* xDestiny, int* yDestiny){
    int options[4][2] = {
        {xAtual, yAtual-1},
        {xAtual, yAtual+1},
        {xAtual-1, yAtual},
        {xAtual+1, yAtual}
    };

    srand(time(0));

    for (int i = 0; i < 10; i++){
        int position = rand() % 4;

        if (canWalk(&m, GHOST, options[position][0], options[position][1])){ 
            *xDestiny = options[position][0];
            *yDestiny = options[position][1];
            return 1;
        }
    } 
   return 0;
}

void ghosts(){
    MAP copy;
    
    copyMap(&copy, &m);

    for (int i = 0; i < m.rows; i++){
        for (int j = 0; j < m.columns; j++){
            if (copy.matrix[i][j] == GHOST){
                int xDestiny, yDestiny;
                int found = directionGhosts(i, j, &xDestiny, &yDestiny);

                if (found)
                    walkOnTheMap(&m, i, j, xDestiny, yDestiny);
            }
        }
    }

    freeMap(&copy);
}

int end(){
    POSITION position;
    int pacman = findInMap(&m, &position, HERO);
    return !pacman;
}

int isDirection(char direction){
    if (direction == LEFT 
    || direction == UP
    || direction == DOWN
    || direction == RIGHT)
        return 0;
    return 1;
}

void move(char direction){

    if (isDirection(direction))
        return;

    int nextX = hero.x;
    int nextY = hero.y;

    switch(direction){
        case LEFT:
            nextY--;
            break;
        case UP:
            nextX--;
            break;
        case DOWN:
            nextX++;
            break;
        case RIGHT:
            nextY++;
            break;
    }

    if (!canWalk(&m, HERO, nextX, nextY))
        return;

    if (isCharacter(&m, ENERGIZERS, nextX, nextY))
        hasEnergizers = 1;

    walkOnTheMap(&m, hero.x, hero.y, nextX, nextY);
    hero.x = nextX;
    hero.y = nextY;

}

void explodeEnergizers(){
    if (!hasEnergizers)
        return;

    explodeEnergizers2(hero.x, hero.y, 0, 1, 3);
    explodeEnergizers2(hero.x, hero.y, 0, -1, 3);
    explodeEnergizers2(hero.x, hero.y, 1, 0, 3);
    explodeEnergizers2(hero.x, hero.y, -1, 0, 3);

    hasEnergizers = 0;
}

void explodeEnergizers2(int x, int y, int sumX, int sumY, int qtd){
    if (qtd == 0)
       return;

    int newX = x + sumX;
    int newY = y + sumY;

    if (!isValid(&m, newX, newY))
        return;

    if (isWall(&m, newX, newY))
        return;

    m.matrix[newX][newY] = EMPTY;
    explodeEnergizers2(newX, newY, sumX, sumY, qtd-1);
}

int main(){

    readMap(&m);
    findInMap(&m, &hero, HERO);
    
    do{
        printMap(&m);
        char command;
        scanf(" %c", &command);
        move(command);
        if (command == BOMB) 
            explodeEnergizers();
        ghosts();
    } while(!end());

    freeMap(&m);
}
