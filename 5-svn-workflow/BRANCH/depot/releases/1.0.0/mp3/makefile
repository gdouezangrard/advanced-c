
VERSION=1
REVISION=0
PATCH=0

CC=gcc
CFLAGS=-Wall
LDFLAGS=


.PHONY: all clean

all : 
	make -e -S -C src all
	make -e -S -C example all

clean:
	make -e -S -C src clean
	make -e -S -C example clean

tar :
	tar -cvzf ../mp3_$(VERSION).$(REVISION).$(PATCH).tgz --exclude=.svn src example makefile

