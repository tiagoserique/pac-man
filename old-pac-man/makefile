
LIBS = -lncurses

CFLAGS = -Wall 

objects = main.o adt_pacman.o lib_game.o lib_screen.o

all: game

game: $(objects)
	gcc $(objects) -o pacman.out $(LIBS)

main.o:
	gcc -c main.c $(CFLAGS) $(LIBS)

adt_pacman.o: adt_pacman.h
	gcc -c adt_pacman.c $(CFLAGS) $(LIBS)

lib_game.o: lib_game.h
	gcc -c lib_game.c $(CFLAGS) $(LIBS)

lib_screen.o: lib_screen.h
	gcc -c lib_screen.c $(CFLAGS) $(LIBS)


clean:
	rm -rf *.o
	
purge: clean
	rm -rf pacman.out

