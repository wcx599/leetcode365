CC=c99
CFLAGs=-Wall -pedantic

all: twice

test: all
	./twice

twice: main.o twice.o
	$(CC) $(CFLAGS) -o $@ $^

tryUsingAdd: tryUsingAdd.o twice.o
	$(CC) $(CFLAGS) -o $@ $^
	
clean:
	$(RM) twice *.o
