# comments start with sharp sign

# variable declarations are VARNAME=expansion

# these are built-ins that control make internal rules
CC=c99
CFLAGS=-g3 -Wall

PROGRAMS=testBytes typedefIssues cat cp

# phantom target can be used to build other things
all: $(PROGRAMS)

test: all
	./typedefIssues
	./testBytes

# dependency rule
#
# target: source-files
# 	commands to build it [optional if built-in commands work]
#
# first character in each command must be `\t`, numeric value 9
# if it's a space, make will get confused

bogus:
	echo this does work now that it has a tab

testBytes: testBytes.o bytes.o

# can use explicit command if I don't like default
#
# testBytes: testBytes.o bytes.o
#	$(CC) $(CFLAGS) -o $@ $^ -lm

# dependencies for .o files
bytes.o: bytes.c bytes.h
testBytes.o: testBytes.c bytes.h

clean:
	$(RM) *.o $(PROGRAMS)
