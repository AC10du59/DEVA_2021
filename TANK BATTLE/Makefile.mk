all: jeu.o Menu.o main.o
	gcc jeu.o Menu.o main.o -o TANK BATTLE
jeu.o: -jeu.c 
	gcc -c -jeu.c -lmingw32 -lSDL -lSDLmain -llib\SDL_image.lib -llib\SDL_TTF.lib
Menu.o: Menu.c 
	gcc -c Menu.c -lmingw32 -lSDL -lSDLmain -llib\SDL_image.lib -llib\SDL_TTF.lib
main.o: main.c
	gcc -c main.c 
clear:
	del *.o