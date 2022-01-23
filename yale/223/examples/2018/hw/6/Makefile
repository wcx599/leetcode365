CC=gcc
CFLAGS=--std=c99 -g3 -Wall -pedantic

all: treeSort

treeSort: tree.o treeSort.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) *.o a.out treeSort

tree.o: tree.h tree.c
treeSort.o: tree.h treeSort.c
