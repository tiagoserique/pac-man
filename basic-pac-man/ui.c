#include <stdio.h>
#include "map.h"

char drawingWall[4][7] = {
	{"......" },
	{"......" },
	{"......" },
	{"......" }
};

char drawingGhost[4][7] = {
	{" .-.  " },
	{"| OO| " },
	{"|   | " },
	{"'^^^' " }
};

char drawingHero[4][7] = {
	{" .--. "  },
	{"/ _.-'"  },
	{"\\  '-." },
	{" '--' "  }
};

char drawingEnergizers[4][7] = {
	{"      "},
	{" .-.  "},
	{" '-'  "},
	{"      "}
};

char drawingEmpty[4][7] = {
	{"      "},
	{"      "},
	{"      "},
	{"      "}
};

void printPart(char drawing[4][7], int part) {
	printf("%s", drawing[part]);
}

void printMap(MAP* m) {
	for(int i = 0; i < m->rows; i++) {

		for(int part = 0; part < 4; part++) {
			for(int j = 0; j < m->columns; j++) {

				switch(m->matrix[i][j]) {
					case GHOST:
						printPart(drawingGhost, part);
						break;
					case HERO:
						printPart(drawingHero, part);
						break;
					case ENERGIZERS:
						printPart(drawingEnergizers, part);
						break;
					case VERTICAL_WALL:
					case HORIZONTAL_WALL:
						printPart(drawingWall, part);
						break;
					case EMPTY:
						printPart(drawingEmpty, part);
						break;
				}
				
			}
			printf("\n");
		}

	}
}
