CC=c99
CFLAGS=-g3 -Wall

PROGRAMS=treeDemo

all: $(PROGRAMS)

test: all
	echo 3 1 4 5 2 | valgrind -q --leak-check=full ./treeDemo 4

treeDemo: treeDemo.o tree.o
	$(CC) $(CFLAGS) -o $@ $^

treeDemo.o: treeDemo.c tree.h

tree.o: tree.c tree.h

clean:
	$(RM) *.o $(PROGRAMS)
