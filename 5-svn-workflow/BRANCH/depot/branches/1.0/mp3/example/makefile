CC=gcc
CFLAGS=-Wall 
LDFLAGS=

override CFLAGS+=-I../src

HEADERS=
SRCS=main.c
OBJS=$(subst .c,.o,$(SRCS))

.PHONY: all clean

-include .depends

.depends: $(SRCS) $(HEADERS)
	$(CC) -MM $(CFLAGS) $^ > .depends

all: main

main: $(OBJS) ../src/mp3.o
	$(CC) $(CFLAGS) $^ -o $@


clean:
	rm -f $(OBJS) .depends main

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


