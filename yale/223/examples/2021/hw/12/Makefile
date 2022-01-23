CC=c99
CFLAGS=-g3 -Wall

PROGRAMS=coloring

all: $(PROGRAMS)

test: all
	echo "3 0 1 0 2" | ./coloring

graph.o: graph.c graph.h
coloring.o: coloring.c graph.h

coloring: graph.o coloring.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) *.o $(PROGRAMS)
