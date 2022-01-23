CC=c99
CFLAGS=-g3 -Wall

PROGRAMS=testDeque

all: $(PROGRAMS)

test: all
	./testDeque
	valgrind ./testDeque > /dev/null

testDeque: testDeque.o deque.o

deque.o: deque.c deque.h
testDeque.o: testDeque.c deque.h

clean:
	$(RM) *.o $(PROGRAMS)
