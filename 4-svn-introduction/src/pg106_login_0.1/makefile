LEVEL = -g
CFLAGS = -c -Wall
LDFLAGS = 

OBJECTS = main.o mp3.o

all : main

main : $(OBJECTS)
	gcc -o $@ $(LDFLAGS) $(LEVEL) $(OBJECTS)
	
main.o : 
	gcc -o $@ $(CFLAGS) $(LEVEL) main.c
	
mp3.o :
	gcc -o $@ $(CFLAGS) $(LEVEL) mp3.c
	
	
clean :
	rm -f *.o main
	
depends :
	gcc -MM *.c > depends.d
	
-include depends.d

tar :
	tar -cvzf mp3.tgz *.c *.h makefile