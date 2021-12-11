compile: $(wildcard *.c)
	gcc -o out $? -I. -lSDL2 -lSDL2_ttf -fsanitize=address
