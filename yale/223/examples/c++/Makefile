CPP=g++
CPPFLAGS=-g3 -Wall

all: helloworld

helloworld: helloworld.o
	$(CPP) $(CPPFLAGS) -o $@ $^

test: all
	./helloworld

clean:
	$(RM) helloworld *.o
