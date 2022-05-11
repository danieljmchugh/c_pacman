all: pacman

pacman: src/main.c
	gcc -o pacman src/main.c src/gamestate.c

clean:
	rm pacman