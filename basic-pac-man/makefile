
CFLAGS = -Wall 

objects = pacman.o map.o ui.o

all: pacman

pacman: $(objects)
	gcc $(objects) -o pacman.out

pacman.o: pacman.h
	gcc -c pacman.c $(CFLAGS)

map.o: map.h
	gcc -c map.c $(CFLAGS)

ui.o: ui.h
	gcc -c ui.c $(CFLAGS)

clean:
	rm -rf *.o
	
purge: clean
	rm -rf pacman.out

