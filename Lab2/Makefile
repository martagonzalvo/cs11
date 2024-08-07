#
# Makefile for CS 11, C track, week 2.
#

#
# NOTE: When pasting this file from a browser window into a text editor,
#       the tab characters at the beginning of the command lines will
#       almost always be replaced by e.g. eight spaces.  You MUST convert
#       them back into a single tab or this file will not work!  "make"
#       is _extremely_ picky about this: command lines must start with one
#       tab and no spaces, no more and no less.  You're better off saving
#       this file directly (e.g. by typing control-S in mozilla or firefox).
#       Also, remove this comment in your submitted Makefile.
#

CC              = gcc
CFLAGS          = -Wall -Wstrict-prototypes -ansi -pedantic -Wuninitialized
INFILE          = years.in
OUTFILE         = easter_dates.out
CORRECT_OUTFILE = correct_easter_dates.out


easter: easter.o
	$(CC) easter.o -o easter

easter.o: easter.c
	$(CC) ${CFLAGS} -c easter.c

test:
	./easter < $(INFILE) > $(OUTFILE)
	./run_test $(OUTFILE) $(CORRECT_OUTFILE)

check:
	c_style_check easter.c

clean:
	rm -f easter.o easter easter_dates.out

