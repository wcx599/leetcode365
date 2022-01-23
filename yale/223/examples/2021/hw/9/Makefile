CC=c99
CFLAGS=-g3 -Wall

PROGRAMS=pfml

all: $(PROGRAMS)

test: all
	echo "{uoy {are} woH} {?yadot}" | ./pfml

pfml: pfml.o bytes.o
pfml.o: pfml.c bytes.h
bytes.o: bytes.c bytes.h

clean:
	$(RM) *.o $(PROGRAMS)
