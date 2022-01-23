CC=c99
CFLAGS=-g3 -O3 -Wall -DDEBUG

PROGRAMS=fib lis lcs

all: $(PROGRAMS)

test: lisTest lcsTest

lisTest: lis
	./lis "This was a triumph. I'm making a note here: HUGE SUCCESS."

lcsTest: lcs
	./lcs "Absence of evidence is not evidence of absence." \
	    "There once was a boy called Eustace Clarence Scrub, and he almost deserved it."

clean:
	$(RM) *.o $(PROGRAMS)
