CC=gcc
CFLAGS=--std=c99 -g3 -Wall -pedantic

all: shrink

shrink: shrink.o set.o
	$(CC) $(CFLAGS) -o $@ $^

tstShrink: shrink.o tstSet.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) *.o a.out shrink tstShrink

set.o: set.h set.c
shrink.o: set.h shrink.c
tstSet.o: set.h tstSet.c
