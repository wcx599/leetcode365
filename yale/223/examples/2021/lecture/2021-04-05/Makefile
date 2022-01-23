CC=c99
CFLAGS=-g3 -Wall

PROGRAMS=recursion binarySearch quickSort

all: $(PROGRAMS)

test-quickSort: quickSort
	./quickSort

test: all
	./recursion
	./binarySearch 5
	./binarySearch 8

recursion: recursion.o
recursion.o: recursion.c
binarySearch: binarySearch.o
binarySearch.o: binarySearch.c
quickSort: quickSort.o
quickSort.o: quickSort.c

clean:
	$(RM) *.o $(PROGRAMS)
