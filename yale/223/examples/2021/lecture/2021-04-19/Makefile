CC=c99
CFLAGS=-g3 -Wall

PROGRAMS=treeDemo

all: $(PROGRAMS)

test: all
	echo 1 2 3 4 5 6 7 -5 -3 -2 -11 | valgrind -q --leak-check=full ./treeDemo 4

treeDemo: treeDemo.o tree.o
	$(CC) $(CFLAGS) -o $@ $^

treeDemo.o: treeDemo.c tree.h

tree.o: tree.c tree.h

clean:
	$(RM) *.o $(PROGRAMS)
