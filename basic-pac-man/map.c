#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"

int isWall(MAP* m, int x, int y){
    return m->matrix[x][y] == VERTICAL_WALL
        || m->matrix[x][y] == HORIZONTAL_WALL;
}

int isCharacter(MAP* m, char character, int x, int y){
    return m->matrix[x][y] == character;
}

int canWalk(MAP* m, char character, int x, int y){
    return isValid(m, x, y) 
        && !isWall(m, x, y) 
        && !isCharacter(m, character, x, y);
}

void copyMap(MAP* destiny, MAP* origin){
    destiny->rows = origin->rows;
    destiny->columns = origin->columns;

    allocateMap(destiny);

    for (int i = 0; i < origin->rows; i++){
        strcpy(destiny->matrix[i], origin->matrix[i]);   
    }

}

void walkOnTheMap(MAP* m, int xOrigin, int yOrigin, int xDestiny, int yDestiny){
    char character = m->matrix[xOrigin][yOrigin];
    m->matrix[xDestiny][yDestiny] = character;
    m->matrix[xOrigin][yOrigin] = EMPTY;
}

int isValid(MAP* m, int x, int y){
    if (x >= m->rows || y >= m->columns)
        return 0;
    return 1;
}

int isEmpty(MAP* m, int x, int y){
    return m->matrix[x][y] == EMPTY;
}

void readMap(MAP* m){
    FILE* file;
    file = fopen("map.txt", "r");
    if (file == 0) {
        printf("Error opening file");
        exit(1);
    }

    fscanf(file, "%d %d", &(m->rows), &(m->columns));
    allocateMap(m);

    for (int i = 0; i < m->rows; i++){
        fscanf(file, "%s", m->matrix[i]);
    }

    fclose(file);
}

void allocateMap(MAP* m){
    m->matrix = malloc(sizeof(char*) * m->rows);

    for (int i = 0; i < m->rows; i++){
        m->matrix[i] = malloc(sizeof(char) * m->columns + 1);
    }
}

void freeMap(MAP* m){
    for (int i = 0; i < m->rows; i++){
        free(m->matrix[i]);
    }
    free(m->matrix);
}

int findInMap(MAP* m, POSITION* p, char c){
    for (int i = 0; i < m->rows; i++){
        for (int j = 0; j < m->columns; j++){
            if (m->matrix[i][j] == c) {
                p->x = i;
                p->y = j;
                return 1;
            }
        }
    }
    return 0;
}
