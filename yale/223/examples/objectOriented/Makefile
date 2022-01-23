# set variables so default rule does the right thing
# gcc -std=c99 instead of c99
# avoids oddities with clang on OSX
CC=gcc
CFLAGS=-std=c99 -Wall -pedantic -g3
VALGRIND=valgrind -q --leak-check=full

# programs to run valgrind on
VALGRIND_PROGS=testStack

# programs to test without valgrind
NO_VALGRIND_PROGS=

# programs with their own test lines
OTHER_PROGS=

PROGS=$(VALGRIND_PROGS) $(NO_VALGRIND_PROGS) $(OTHER_PROGS)

all: $(PROGS)

test: all
	for i in $(NO_VALGRIND_PROGS); do ./$$i; done
	for i in $(VALGRIND_PROGS); do $(VALGRIND) ./$$i; done

stack.o: stack.c stack.h

testStack.o: testStack.c stack.h object.h intObject.h stringObject.h

intObject.o: intObject.c object.h intObject.h

stringObject.o: stringObject.c object.h stringObject.h

testStack: testStack.o stack.o intObject.o stringObject.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(PROGS) *.o a.out
