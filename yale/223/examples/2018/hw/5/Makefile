CC=gcc
CFLAGS=--std=c99 --pedantic -g3
VALGRIND=valgrind -q --leak-check=full

all: ants

test: hash.test
	$(VALGRIND) ./hash.test 10

hash.test: hash.c
	$(CC) $(CFLAGS) -DTEST_MAIN -o $@ $^

ants: main.o ants.o hash.o point.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c ants.h hash.h point.h

ants.o: ants.c ants.h hash.h point.h

hash.o: hash.c hash.h point.h

point.o: point.c point.h

clean:
	$(RM) a.out *.o hash.test ants
