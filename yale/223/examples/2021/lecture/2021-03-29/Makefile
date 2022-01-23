CC=c99
CFLAGS=-g3 -Wall

PROGRAMS=testWordBuffer countWords qsortDemo dispatch

all: $(PROGRAMS)

test: test-wordBuffer test-countWords test-qsortDemo test-dispatch

test-wordBuffer: testWordBuffer
	./testWordBuffer < wordBuffer.h | head -5
	valgrind -q ./testWordBuffer < wordBuffer.h > /dev/null

test-countWords: countWords
	./countWords 1 < wordBuffer.h | head -10
	valgrind -q ./countWords 1 < wordBuffer.h > /dev/null

test-qsortDemo: qsortDemo
	./qsortDemo

test-dispatch: dispatch
	./dispatch hello
	./dispatch goodbye
	./dispatch echo 1 2 3
	./dispatch fail || echo it failed
	./dispatch no such command || exit 0

testWordBuffer: testWordBuffer.o wordBuffer.o
countWords: countWords.o wordBuffer.o dictStringInt.o
qsortDemo: qsortDemo.o
dispatch: dispatch.o

testWordBuffer.o: testWordBuffer.c wordBuffer.h
countWords.o: countWords.c wordBuffer.h dictStringInt.h
wordBuffer.o: wordBuffer.c wordBuffer.h
dictStringInt.o: dictStringInt.c dictStringInt.h

clean:
	$(RM) *.o $(PROGRAMS)
