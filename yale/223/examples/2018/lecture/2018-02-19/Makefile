# set variables so default rule does the right thing
# gcc -std=c99 instead of c99
# avoids oddities with clang on OSX
CC=gcc
CFLAGS=-std=c99 -Wall -pedantic -g3 -O2

# programs to run valgrind on
VALGRIND_PROGS=

# programs to test without valgrind
OTHER_PROGS=linkedList

PROGS=$(VALGRIND_PROGS) $(OTHER_PROGS)

all: $(PROGS)

test: all
	echo "hi there" | ./linkedList
	echo "hi there" | valgrind ./linkedList

clean:
	$(RM) $(PROGS) *.o a.out
