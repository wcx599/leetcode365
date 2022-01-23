CC=gcc
CFLAGS=-std=c99 -g3 -Wall -pedantic

all: testStrategy

test: testHeap testStrategy
	./testHeap
	valgrind -q ./testStrategy h 1000 10

testStrategy: testStrategy.o strategy.o heap.o
	$(CC) $(CFLAGS) -o $@ $^

strategy.o: strategy.c strategy.h

testStrategy.o: testStrategy.c strategy.h

testHeap: heap.c heap.h
	$(CC) $(CFLAGS) -DTEST_MAIN -o $@ $<

clean:
	$(RM) -r testHeap testStrategy testFiles *.o gmon.out
