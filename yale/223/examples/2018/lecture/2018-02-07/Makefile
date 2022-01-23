# set variables so default rule does the right thing
# gcc -std=c99 instead of c99
# avoids oddities with clang on OSX
CC=gcc
CFLAGS=-std=c99 -Wall -pedantic -g3

# programs to run valgrind on
VALGRIND_PROGS=usePackedVector

# programs to test without valgrind
OTHER_PROGS=

PROGS=$(VALGRIND_PROGS) $(OTHER_PROGS)

all: $(PROGS)

test: all
	for i in $(PROGS); do echo Running ./$$i; ./$$i; done
	for i in $(VALGRIND_PROGS); do echo Running valgrind on ./$$i; valgrind --tool=memcheck ./$$i; done

usePackedVector: usePackedVector.o packedVector.o
	$(CC) $(CFLAGS) -o usePackedVector usePackedVector.o packedVector.o

clean:
	$(RM) $(PROGS) *.o a.out
