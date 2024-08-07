/*
 * CS 11, C track, lab 8
 *
 * FILE: main.c
 *       Testing the bytecode interpreter.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "bci.h"


void usage(char *progname)
{
    fprintf(stderr, "usage: %s filename\n", progname);
}


int main(int argc, char **argv)
{
    if (argc != 2)
    {
        usage(argv[0]);
        exit(1);
    }

    run_program(argv[1]);

    return 0;
}


