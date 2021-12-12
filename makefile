compile: $(wildcard *.c)
	gcc -o 2048 $? -I. -lSDL2 -lSDL2_ttf
