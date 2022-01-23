CC=gcc
CFLAGS=-std=c99 -Wall -pedantic -g3

TARGET=test-dict

OBJECT_FILES=test-dict.o tester.o dict.o

all: $(TARGET)

test: all
	./$(TARGET)

$(TARGET): $(OBJECT_FILES)
	$(CC) $(CFLAGS) -o $@ $^

tester.o: tester.c tester.h

test-dict.o: test-dict.c tester.h dict.h

dict.o: dict.c dict.h

clean:
	$(RM) $(TARGET) *.o
