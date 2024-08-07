#
# CS 11: Makefile for C track, assignment 3.
#

CC     = gcc
CFLAGS = -g -Wall -Wstrict-prototypes -ansi -pedantic -Wuninitialized

sorter: sorter.o
	$(CC) sorter.o -o sorter

sorter.o: sorter.c
	$(CC) $(CFLAGS) -c sorter.c

test:
	./run_test

check:
	c_style_check sorter.c

clean:
	rm -f sorter *.o

