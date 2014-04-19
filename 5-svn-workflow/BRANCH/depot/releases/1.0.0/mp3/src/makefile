CC=gcc
CFLAGS=-Wall
LDFLAGS=

HEADERS=mp3.h
SRCS=mp3.c
OBJS=$(subst .c,.o,$(SRCS))

.PHONY: all clean

-include .depends

.depends: $(SRCS) $(HEADERS)
	$(CC) -MM $(CFLAGS) $^ > .depends

all: $(OBJS)


clean:
	rm -f $(OBJS) .depends

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


