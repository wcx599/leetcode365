CC=c99
CFLAGS=-g3 -Wall

PROGRAMS=testWordBuffer countWords

all: $(PROGRAMS)

test: all
	./testWordBuffer < wordBuffer.h | head -5
	valgrind -q ./testWordBuffer < wordBuffer.h > /dev/null
	./countWords < wordBuffer.h | head -10
	valgrind -q ./countWords < wordBuffer.h > /dev/null

testWordBuffer: testWordBuffer.o wordBuffer.o
countWords: countWords.o wordBuffer.o dictStringInt.o

testWordBuffer.o: testWordBuffer.c wordBuffer.h
countWords.o: countWords.c wordBuffer.h dictStringInt.h
wordBuffer.o: wordBuffer.c wordBuffer.h
dictStringInt.o: dictStringInt.c dictStringInt.h

clean:
	$(RM) *.o $(PROGRAMS)
