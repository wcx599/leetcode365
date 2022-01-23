CC=gcc
CFLAGS=-std=c99 -g3 -Wall -pedantic
all: testPriorityQueue

test: all
	./testPriorityQueue

testPriorityQueue: priorityQueue.c priorityQueue.h
	# $< gets first dependency only 
	$(CC) $(CFLAGS) -DTEST_MAIN -o $@ $<

clean:
	$(RM) *.o testPriorityQueue
