# set variables so default rule does the right thing
# gcc -std=c99 instead of c99
# avoids oddities with clang on OSX
CC=gcc
CFLAGS=-std=c99 -Wall -pedantic -g3

PROGS=pointers bufferOverRun arrays strings

all: $(PROGS)

test: all
	./pointers

clean:
	$(RM) $(PROGS) *.o a.out
