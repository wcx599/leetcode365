CC=gcc
CFLAGS=-std=c99 -g3 -Wall -pedantic

# turns on test main routine #ifdef and sets up gcov
EXTRA_TEST_FLAGS=-DTEST_MAIN -fprofile-arcs -ftest-coverage

all:

test: testCounter
	./testCounter
	gcov counter.c

testCounter: counter.c counter.h
	# $< expands to first dependency only
	$(CC) $(CFLAGS) $(EXTRA_TEST_FLAGS) -o $@ $<

clean:
	$(RM) *.o testCounter *.gcov *.gcda *.gcno
