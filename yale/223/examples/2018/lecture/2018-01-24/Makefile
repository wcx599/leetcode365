# set variables so default rule does the right thing
# gcc -std=c99 instead of c99
# avoids oddities with clang on OSX
CC=gcc
CFLAGS=-std=c99 -Wall -pedantic -g3

all: eval cat rot1 readInt

test: all
	./eval
	echo test | ./cat
	./cat < Makefile
	echo test | ./rot1
	echo test | ./rot1 | ./rot1
	echo 12345 | ./readInt
	each boo | ./readInt

clean:
	$(RM) eval *.o a.out
