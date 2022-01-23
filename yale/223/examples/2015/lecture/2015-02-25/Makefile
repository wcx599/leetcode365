CC=gcc
CFLAGS=-std=c99 -g3 -Wall -pedantic

all: testSet

test: testSet
	./testSet 100

testSet: testSet.o set.o
	$(CC) $(CFLAGS) -o $@ $^

testSet.o: testSet.c set.h

set.o: set.c set.h

clean:
	$(RM) testSet *.o
