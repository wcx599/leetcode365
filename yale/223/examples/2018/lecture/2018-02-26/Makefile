# set variables so default rule does the right thing
# gcc -std=c99 instead of c99
# avoids oddities with clang on OSX
CC=gcc
CFLAGS=-std=c99 -Wall -pedantic -g3 -O2
VALGRIND=valgrind -q --leak-check=full

# programs to run valgrind on
VALGRIND_PROGS=

# programs to test without valgrind
NO_VALGRIND_PROGS=

# programs with their own test lines
OTHER_PROGS=stringutil.test countWords

PROGS=$(VALGRIND_PROGS) $(NO_VALGRIND_PROGS) $(OTHER_PROGS)

all: $(PROGS)

test: all
	echo "hi there: supercalifragilisticexpialidocious " | $(VALGRIND) -q ./stringutil.test
	echo "hi there: supercalifragilisticexpialidocious, hi, hi!, Hi" | $(VALGRIND) -q ./countWords

countWords: countWords.o hash.o stringutil.o
	$(CC) $(CFLAGS) -o $@ $^

countWords.o: countWords.c hash.h stringutil.h

hash.o: hash.c hash.h stringutil.h

stringutil.o: stringutil.c stringutil.h

stringutil.test: stringutil.c
	$(CC) $(CFLAGS) -DTEST_MAIN -o $@ $^

clean:
	$(RM) $(PROGS) *.o a.out
