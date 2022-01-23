CC=gcc
CFLAGS=-std=c99 -g3 -Wall -pedantic

all: maze

maze: maze.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

clean:
	$(RM) *.o maze test.pgm
