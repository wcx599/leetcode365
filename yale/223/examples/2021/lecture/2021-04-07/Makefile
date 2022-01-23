CC=c99
CFLAGS=-g3 -Wall

PROGRAMS=count scanf calc

TEST_FILE=test.counts

all: $(PROGRAMS)

test: all
	./count $(TEST_FILE) 0
	./count $(TEST_FILE) 0
	./count $(TEST_FILE) 1
	./count $(TEST_FILE) 100
	./count $(TEST_FILE) 1000000
	valgrind -q --leak-check=full ./count $(TEST_FILE) 12

count: count.o counters.o
count.o: count.c counters.h
counters.o: counters.c counters.h
scanf: scanf.o
scanf.o: scanf.c

clean:
	$(RM) *.o $(PROGRAMS) $(TEST_FILE)
