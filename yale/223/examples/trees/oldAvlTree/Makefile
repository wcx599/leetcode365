CC=c99
CFLAGS=-g3 -O3 -pedantic -Wall

all: test_avlTree avlSpeedTest

test: all
	time ./avlSpeedTest
	valgrind -q --leak-check=yes ./test_avlTree

test_avlTree: test_avlTree.o avlTree.o
	$(CC) $(CFLAGS) -o $@ $^

test_avlTree.o avlTree.o: avlTree.h

avlSpeedTest: avlSpeedTest.o avlTree.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) test_avlTree avlSpeedTest *.o
