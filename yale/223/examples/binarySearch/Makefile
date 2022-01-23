CC=c99
CFLAGS=-g3 -Wall -pedantic

all: testBinarySearchRecursive testBinarySearchIterative

test: all
	./testBinarySearchRecursive
	./testBinarySearchIterative

testBinarySearchRecursive: testBinarySearch.o binarySearchRecursive.o
	$(CC) $(CFLAGS) -o $@ $^

testBinarySearchIterative: testBinarySearch.o binarySearchIterative.o
	$(CC) $(CFLAGS) -o $@ $^

testBinarySearch.o: testBinarySearch.c binarySearch.h

binarySearchRecursive.o: binarySearchRecursive.c binarySearch.h

binarySearchIterative.o: binarySearchIterative.c binarySearch.h

clean:
	$(RM) testBinarySearchRecursive testBinarySearchIterative *.o
