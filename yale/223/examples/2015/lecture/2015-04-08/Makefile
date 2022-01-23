CC=gcc
CFLAGS=-std=c99 -g3 -Wall -pedantic

all: search

test: all
	valgrind -q ./search 14

clean:
	$(RM) *.o search
