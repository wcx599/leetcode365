# set variables so default rule does the right thing
# gcc -std=c99 instead of c99
# avoids oddities with clang on OSX
CC=gcc
CFLAGS=-std=c99 -Wall -pedantic -g3

PROGS=struct packedVector union

all: $(PROGS)

test: all
	for i in $(PROGS); do echo ./$$i; ./$$i; done
	# for i in $(PROGS); do echo ./$$i; valgrind --tool=memcheck ./$$i; done

clean:
	$(RM) $(PROGS) *.o a.out
