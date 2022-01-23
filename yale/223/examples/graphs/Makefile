CC=gcc
CFLAGS=-std=c99 -g3 -Wall -pedantic

EXECUTABLES=graphTest genericSearchTest

all: $(EXECUTABLES)

test: all
	valgrind -q --leak-check=yes ./graphTest
	valgrind -q --leak-check=yes ./genericSearchTest

graphTest: graphTest.o graph.o
	$(CC) $(CFLAGS) -o $@ $^

genericSearchTest: genericSearchTest.o genericSearch.o graph.o
	$(CC) $(CFLAGS) -o $@ $^

graphTest.o: graphTest.c graph.h

genericSearchTest.o: genericSearchTest.c genericSearch.h graph.h

graph.o: graph.c graph.h

genericSearch.o: genericSearch.c genericSearch.h

clean:
	$(RM) *.o $(EXECUTABLES)
