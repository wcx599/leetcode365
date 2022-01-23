CC=gcc
CFLAGS=-g3 -Wall

PROGRAMS=testGraph

all: $(PROGRAMS)

test: all
	./testGraph 0 5
	./testGraph 1 5
	./testGraph 2 10
	./testGraph 3 8

testGraph: testGraph.o graph.o
testGraph.o: testGraph.c graph.h
graph.o: graph.c graph.h

clean:
	$(RM) *.o $(PROGRAMS)
