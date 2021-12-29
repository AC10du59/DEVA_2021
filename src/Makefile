OBJS	= projet.o arbre.o menu.o multi.o ordi.o
SOURCE	= projet.c arbre.c menu.c multi.c ordi.c
HEADER	= 
OUT	= projet
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

projet.o: projet.c
	$(CC) $(FLAGS) projet.c 

arbre.o: arbre.c
	$(CC) $(FLAGS) arbre.c 

menu.o: menu.c
	$(CC) $(FLAGS) menu.c 

multi.o: multi.c
	$(CC) $(FLAGS) multi.c 

ordi.o: ordi.c
	$(CC) $(FLAGS) ordi.c 


clean:
	rm -f $(OBJS) $(OUT)
