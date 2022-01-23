# set variables so default rule does the right thing
# gcc -std=c99 instead of c99
# avoids oddities with clang on OSX
CC=gcc
CFLAGS=-std=c99 -Wall -pedantic -g3 -O2

# programs to run valgrind on
VALGRIND_PROGS=license1.test license2.test badQueue goodQueue

# programs to test without valgrind
OTHER_PROGS=

PROGS=$(VALGRIND_PROGS) $(OTHER_PROGS)

all: $(PROGS)

test: all
	for i in $(PROGS); do echo $$i; ./$$i; done
	for i in $(VALGRIND_PROGS); do echo valgrind $$i; valgrind -q --leak-check=full ./$$i; done

%.test: %.o licenseTest.o
	$(CC) $(CFLAGS) -o $@ $^

badQueue: badQueue.o testQueue.o
	$(CC) $(CFLAGS) -o $@ $^

goodQueue: goodQueue.o testQueue.o 
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) -rf $(PROGS) *.o a.out *.dSYM
