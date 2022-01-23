CC=c99
CFLAGS=-g3 -Wall

all: testSuffixArray

test: all
	/bin/echo -n abracadabra-abracadabra-shmabracadabra | ./testSuffixArray abra

testSuffixArray: testSuffixArray.o suffixArray.o
	$(CC) $(CFLAGS) -o $@ $^

testSuffixArray.o suffixArray.o: suffixArray.h

clean:
	$(RM) testSuffixArray *.o
