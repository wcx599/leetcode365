CC=c99
CFLAGS=-g3 -Wall

PROGRAMS=testQsort testHeapsort

N=10000000

all: $(PROGRAMS)

test: all
	time ./testQsort $(N)
	time ./testHeapsort $(N)

testQsort: testQsort.o
	$(CC) $(CFLAGS) -o $@ $^

testQsort.o: testQsort.c

testHeapsort: testHeapsort.o heapsort.o
	$(CC) $(CFLAGS) -o $@ $^

testHeapsort.o: testHeapsort.c heapsort.h
heapsort.o: heapsort.c heapsort.h

clean:
	$(RM) *.o $(PROGRAMS)
