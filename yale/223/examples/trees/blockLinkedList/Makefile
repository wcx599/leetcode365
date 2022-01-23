CC=c99
CFLAGS=-O3 -pedantic -Wall

TEST_PROGS=testStackArray testStackList testStackBlockList

all: $(TEST_PROGS)

test: all
	for i in $(TEST_PROGS); do echo $$i; time ./$$i; done

testStackArray: testStack.o stackArray.o
	$(CC) $(CFLAGS) -o $@ $^

testStackList: testStack.o stackList.o
	$(CC) $(CFLAGS) -o $@ $^

testStackBlockList: testStack.o stackBlockList.o
	$(CC) $(CFLAGS) -o $@ $^

testStack.o stackArray.o stackList.o stackBlockList.o: stack.h

clean:
	$(RM) $(TEST_PROGS) *.o
