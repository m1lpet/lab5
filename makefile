CC = gcc
CFLAGS = -Wall -g

all: boardgame_store
	./boardgame_store

boardgame_store: main.o boardgame.o
	$(CC) $(CFLAGS) main.o boardgame.o -o boardgame_store

%.o: %.c boardgame.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f boardgame_store *.o
