CC=gcc
CFLAGS=-g3 -Wall

PROGRAMS=testInserter

all: $(PROGRAMS)

test: all
	echo "b a c d g a" | valgrind -q ./testInserter
	echo "0 abc 0 aaa 0 def 0 abc 1 qrs" | valgrind -q ./testInserter 3

testInserter: inserter.o testInserter.o
inserter.o: inserter.c inserter.h
testInserter.o: testInserter.c inserter.h

clean:
	$(RM) *.o $(PROGRAMS)
