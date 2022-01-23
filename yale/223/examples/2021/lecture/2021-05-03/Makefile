CC=c99
CFLAGS=-g3 -Wall -DDEBUG

PROGRAMS=testTst testRadixSort

all: $(PROGRAMS)

test: all
	echo "the cat in the hat" | ./testTst
	echo "the cat in the hat has a thought about that" | ./testTst "" "a" "th"
	echo "the cat in the hat has a thought about that" | ./testRadixSort


testTst: testTst.o tst.o
	$(CC) $(CFLAGS) -o $@ $^

testTst.o: testTst.c tst.h
tst.o: tst.c tst.h

testRadixSort: testRadixSort.o radixSort.o
	$(CC) $(CFLAGS) -o $@ $^

radixSort.o: radixSort.c radixSort.h
testRadixSort.o: testRadixSort.c radixSort.h

clean:
	$(RM) *.o $(PROGRAMS)
