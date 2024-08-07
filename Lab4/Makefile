#
# CS 11 C track: Makefile for assignment 4.
#

CC = gcc
CFLAGS = -g -Wall -Wstrict-prototypes -ansi -pedantic -Wuninitialized

triangle_game: triangle_game.o triangle_routines.o
	$(CC) triangle_game.o triangle_routines.o -o triangle_game

triangle_example: triangle_example.o triangle_routines.o
	$(CC) triangle_example.o triangle_routines.o -o triangle_example

triangle_routines.o: triangle_routines.c triangle_routines.h
	$(CC) $(CFLAGS) -c triangle_routines.c

triangle_example.o: triangle_example.c triangle_routines.h
	$(CC) $(CFLAGS) -c triangle_example.c

triangle_game.o: triangle_game.c triangle_routines.h
	$(CC) $(CFLAGS) -c triangle_game.c

test:
	./triangle_game < test_input | more

check:
	c_style_check triangle_game.c

clean:
	rm -f *.o triangle_example triangle_game

