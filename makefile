run: out
	./out

out: main.c board.c game.c renderer.c utils.c
	gcc -o out game.c board.c main.c renderer.c utils.c -I. -lSDL2 -lSDL2_ttf