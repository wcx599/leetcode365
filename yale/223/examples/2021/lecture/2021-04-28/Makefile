CC=c99
CFLAGS=-g3 -Wall

PROGRAMS=testGraph

all: $(PROGRAMS)

test: all
#	./testGraph print 0 5
#	./testGraph print 1 5
#	./testGraph print 2 10
#	./testGraph print 3 8
	./testGraph print 4 3
	./testGraph dfs 3 8
	./testGraph bfs 3 8
	./testGraph bfs 4 3

testGraph: testGraph.o graph.o search.o
testGraph.o: testGraph.c graph.h
graph.o: graph.c graph.h
search.o: search.c graph.h search.h

clean:
	$(RM) *.o $(PROGRAMS)
