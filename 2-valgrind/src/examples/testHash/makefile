# makefile for purify example directory 

CC =		cc

all: testHash testHash.pure

# add this target for purify
testHash.pure: testHash.o hash.o
	purify $(CC) -g  -o $@ testHash.o hash.o

testHash: testHash.o hash.o
	$(CC) -g -o $@ testHash.o hash.o

hash.o: hash.c config.h hash.h
	$(CC) -c -g hash.c

testHash.o: testHash.c config.h hash.h
	$(CC) -c -g testHash.c

clean:
	/bin/rm -f core *.o *.a testHash testHash.pure *~
	/bin/rm -f *_pure* .pur*






