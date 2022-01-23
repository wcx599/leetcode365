CC=c99
CFLAGS=-g3 -Wall

PROGRAMS=testOrderBook

all: $(PROGRAMS)

test: all
	(echo "0 -3"; echo "0 4"; echo "0 -5" ; echo "0 4") | ./testOrderBook 2
	time ./testOrderBook 1337 1000000 1000
	valgrind -q --leak-check=full ./testOrderBook 1337 1000 20

testOrderBook: testOrderBook.o orderBook.o
testOrderBook.o: testOrderBook.c orderBook.h
orderBook.o: orderBook.c orderBook.h

clean:
	$(RM) *.o $(PROGRAMS)
