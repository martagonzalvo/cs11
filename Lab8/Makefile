#
# Makefile for C track, assignment 8.
#

CC     = gcc
CFLAGS = -g -Wall -Wstrict-prototypes -ansi -pedantic

bci: main.o bci.o
	$(CC) main.o bci.o -o bci

main.o: main.c bci.c bci.h
	$(CC) $(CFLAGS) -c main.c

bci.o: bci.c bci.h
	$(CC) $(CFLAGS) -c bci.c

test:
	./run_test

check:
	c_style_check bci.c

clean:
	rm -f *.o bci 





