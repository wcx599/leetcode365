CC=c99
CFLAGS=-Wall -pedantic -g3

test: testIntArray
	./testIntArray 57 1007
	./testIntArray 1000123 111
	valgrind -q --tool=memcheck --leak-check=yes ./testIntArray 937 1091

testIntArray: testIntArray.o intArray.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) testIntArray *.o
