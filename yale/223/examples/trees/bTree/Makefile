CC=c99
CFLAGS=-O3 -pedantic -Wall

test: testBTree
	time ./testBTree

testBTree: bTree.o testBTree.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) testBTree *.o
