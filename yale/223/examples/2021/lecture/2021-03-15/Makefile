CC=c99
CFLAGS=-g3 -Wall

PROGRAMS=testStack testStackArray timeStack timeStackArray

all: $(PROGRAMS)

test: all
	./testStack 5
	./testStackArray 5
	time ./timeStack 100000000
	time ./timeStackArray 100000000

testStack: testStack.o stack.o
	$(CC) $(CFLAGS) -o $@ $^

testStackArray: testStack.o stackArray.o
	$(CC) $(CFLAGS) -o $@ $^

timeStack: timeStack.o stack.o
	$(CC) $(CFLAGS) -O3 -o $@ $^

timeStackArray: timeStack.o stackArray.o
	$(CC) $(CFLAGS) -O3 -o $@ $^

testStack.o: testStack.c stack.h
timeStack.o: timeStack.c stack.h
stack.o: stack.c stack.h
stackArray.o: stackArray.c stack.h

clean:
	$(RM) *.o $(PROGRAMS)
