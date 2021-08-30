#ifndef _MAP_H_
#define _MAP_H_
#define HERO '@'
#define GHOST 'F'
#define EMPTY '.'
#define VERTICAL_WALL '|'
#define HORIZONTAL_WALL '-'
#define ENERGIZERS 'P'

struct map {
    char** matrix;
    int rows;
    int columns;
};

typedef struct map MAP;

void freeMap(MAP* m);
void readMap(MAP* m);
void allocateMap(MAP* m);
void printMap(MAP* m);
int isValid(MAP* m, int x, int y);
int isEmpty(MAP* m, int x, int y); 
void walkOnTheMap(MAP* m, int xOrigin, int yOrigin, int xDestiny, int yDestiny);
void copyMap(MAP* destiny, MAP* origin);
int isWall(MAP* m, int x, int y);
int isCharacter(MAP* m, char character, int x, int y);
int canWalk(MAP* m, char character, int x, int y);

struct position {
    int x;
    int y;
};

typedef struct position POSITION;

int findInMap(MAP* m, POSITION* p, char c);

#endif
