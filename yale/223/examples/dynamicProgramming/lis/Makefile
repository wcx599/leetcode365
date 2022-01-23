CC=c99
CFLAGS=-g3 -pedantic -Wall

all: test_lis

test: all
	echo 7 2 17 11 16 1 6 5 4 12 9 10 13 20 15 14 3 18 19 8 | ./test_lis

test_lis: test_lis.o lis.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) test_lis *.o
