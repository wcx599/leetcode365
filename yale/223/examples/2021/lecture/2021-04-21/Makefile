CC=c99
CFLAGS=-g3 -Wall

PROGRAMS=pfml

all: $(PROGRAMS)

test: all
	echo "{uoy {are} woH} {?yadot}" | ./pfml

pfml: pfml.o
pfml.o: pfml.c

clean:
	$(RM) *.o $(PROGRAMS)
