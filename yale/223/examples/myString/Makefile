test: test_myString
	./test_myString

test_myString: test_myString.o myString.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) test_myString *.o
