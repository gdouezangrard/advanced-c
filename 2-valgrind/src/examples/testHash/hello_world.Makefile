# Sample makefile template
# May also be Used in Purifying Hello World
# Use make -f hello_world.Makefile PDIR=<purifyhome> a.out.pure

# Purify related flags
PFLAGS	= -first-only -leaks-at-exit=yes
PDIR	= `purify -print-home-dir`
PURIFY	= purify $(PFLAGS)
PSTUBS	= $(PDIR)/purify_stubs.a

# General flags
CC	= cc
CFLAGS	= -g -I$(PDIR)

# Targets
all: a.out a.out.pure

a.out: hello_world.c
	 $(CC) $(CFLAGS) -o $@ $? $(PSTUBS)

a.out.pure: hello_world.c
	 $(PURIFY) $(CC) $(CFLAGS) -o $@ $? $(PSTUBS)
