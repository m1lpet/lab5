CC = gcc
CFLAGS = -Wall -g

all: boardgame_store
	./boardgame_store

boardgame_store: main.o boardgame.o
	$(CC) $(CFLAGS) main.o boardgame.o -o boardgame_store

main.o: main.c boardgame.h
	$(CC) $(CFLAGS) -c main.c -o main.o

boardgame.o: boardgame.c boardgame.h
	$(CC) $(CFLAGS) -c boardgame.c -o boardgame.o

clean:
	rm -f boardgame_store *.o boardgames.txt
