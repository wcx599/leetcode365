CC=gcc
CFLAGS=-std=c99 -Wall -pedantic -g3

TARGET=testOrderedSet

OBJECT_FILES=testOrderedSet.o orderedSet.o

all: $(TARGET)

# this is a very basic placeholder test
test: all
	printf '+hello\n+world\np\ns\nh\nfh\np\ns\nh\n-hello\np\ns\nh\n' | valgrind -q ./$(TARGET)

$(TARGET): $(OBJECT_FILES)
	$(CC) $(CFLAGS) -o $@ $^

testOrderedSet.o: testOrderedSet.c orderedSet.h

orderedSet.o: orderedSet.c orderedSet.h

clean:
	$(RM) $(TARGET) $(OBJECT_FILES)
