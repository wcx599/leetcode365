CC=gcc
CFLAGS=-std=c99 -g3 -Wall -pedantic

all: search

examples: all
	./search g 20 | dot -Tpng > graph20.png
	./search b 20 | dot -Tpng > bfs20.png
	./search d 20 | dot -Tpng > dfs20.png

test: all
	valgrind -q ./search b 14

clean:
	$(RM) *.o search *.png
