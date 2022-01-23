CC=gcc
CFLAGS=-std=c99 -Wall -pedantic -g3

all: turing

compositor: turing.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) turing *.o
