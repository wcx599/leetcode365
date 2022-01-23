# here are some variable definitions
CC=gcc
CFLAGS=-std=c99 -Wall -pedantic -g3

# putting this at the top makes this the default
all: hello

test: all
	./hello
	./hello | wc

# says hello depends on these two .o files
hello: hello.o helloHelper.o
	# command line, starts with TAB character
	#  $@ = target
	#  $^ = dependencies
	$(CC) $(CFLAGS) -o $@ $^

hello.o: hello.c helloHelper.h
helloHelper.o: helloHelper.c helloHelper.h

clean:
	$(RM) hello countPrimes *.o
