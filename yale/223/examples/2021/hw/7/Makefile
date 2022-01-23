CC=c99
CFLAGS=-g3 -Wall

PROGRAMS=decrypt

all: $(PROGRAMS)

decrypt: decrypt.o table.o
decrypt.o: decrypt.c table.h
table.o: table.c table.h

clean:
	$(RM) *.o $(PROGRAMS)
