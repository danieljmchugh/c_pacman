all: pacman

pacman: src/main.c
	gcc -o pacman src/main.c src/gamestate.c src/player.c src/ghost.c

clean:
	rm pacman