CC=c99
CFLAGS=-g3 -Wall

PROGRAMS=testWordBuffer countWords

all: $(PROGRAMS)

test: test-wordBuffer test-countWords

test-wordBuffer: testWordBuffer
	./testWordBuffer < wordBuffer.h | head -5
	valgrind -q --leak-check=full ./testWordBuffer < wordBuffer.h > /dev/null

test-countWords: countWords
	echo "a b c d e f a b c d d" | ./countWords 1 | head -10
	valgrind -q --leak-check=full ./countWords 1 < wordBuffer.h > /dev/null

testWordBuffer: testWordBuffer.o wordBuffer.o
countWords: countWords.o wordBuffer.o mapInt.o stringKey.o intKey.o

testWordBuffer.o: testWordBuffer.c wordBuffer.h
countWords.o: countWords.c wordBuffer.h mapInt.h
wordBuffer.o: wordBuffer.c wordBuffer.h
mapInt.o: mapInt.c mapInt.h

clean:
	$(RM) *.o $(PROGRAMS)
