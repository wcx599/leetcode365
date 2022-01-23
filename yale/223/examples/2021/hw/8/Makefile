CC=c99
CFLAGS=-g3 -Wall

PROGRAMS=decompress compress

all: $(PROGRAMS)

decompress: decompress.o
decompress.o: decompress.c compressionFormat.h

compress: compress.o
compress.o: compress.c compressionFormat.h

clean:
	$(RM) *.o $(PROGRAMS)
