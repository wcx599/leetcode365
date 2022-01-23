# set variables so default rule does the right thing
# gcc -std=c99 instead of c99
# avoids oddities with clang on OSX
CC=gcc
CFLAGS=-std=c99 -Wall -pedantic -g3

PROGS=badReturnPointer array realloc

all: $(PROGS)

test: all
	./badReturnPointer
	./array
	echo This is a long string that we will run through the realloc demo. | ./realloc

clean:
	$(RM) $(PROGS) *.o a.out
