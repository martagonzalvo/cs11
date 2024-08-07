/*
 * FILE: triangle_routines.c
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#include "triangle_routines.h"

#define BUFSIZE 4096

/* print_spaces:  Prints <num> spaces on the standard output. */
static void print_spaces(int num)
{
    for (; num > 0; num -= 1) 
    {
        printf(" ");
    }
}


/*
 * triangle_print:  Prints the triangle game represented by <board>
 *                  in a nice, visual way to the standard output.
 *
 *                  The board must be an array of 15 integers.  Non-zero
 *                  values indicate a peg in that position.
 * 
 */

void triangle_print(const int board[])
{
    int line;
    
    assert(board != NULL);
    
    for (line = 0; line < 5; line++) 
    {
        int start;
        int index;
        
        /* 
         * prefix_spaces: The number of spaces before each text line
         * output for this line of the triangle game.  Each "peg box" takes
         * four spaces, and there are (4-line) boxes we need to skip (look
         * at the output if this doesn't make sense).
         */

        int prefix_spaces = (4 - line) * 4;

        /* start:  The number of the first box on this line of output. */
        start = (line * (line + 1)) / 2; /* start = sum(n, n = 0 .. start) */
        
        /* 
         * Each box takes three lines of text to output.  This prints out
         * the first line, which is the tops for all of the pegs.
         */
        
        print_spaces(prefix_spaces);
        
        for (index = start; index < (line + start + 1); index++) 
        {
            if (board[index] != 0) 
            {
                printf(" __ ");
            } 
            else 
            {
                printf("    ");
            }
            
            printf("    ");
        }
        
        printf("\n");
        
        /* 
         * The second line of text is the position number, surrounded by
         * vertical bars if there is a peg here.
         */
        
        print_spaces(prefix_spaces);
        
        for (index = start; index < (line + start + 1); index++) 
        {
            if (board[index] != 0) 
            {
                printf("|%2d|", index);
            } 
            else 
            {
                printf(" %2d ", index);
            }
            
            printf("    ");
        }
        
        printf("\n");
        
        /* The third line of text is the bottoms of the pegs. */
        print_spaces(prefix_spaces);
        
        for (index = start; index < (line + start + 1); index++) 
        {
            if (board[index] != 0) 
            {
                printf("|__|");
            } 
            else 
            {
                printf("    ");
            }
            
            printf("    ");
        }
        printf("\n");
    }
}


/* 
 * get_pegnum:  Reads a peg number from the user, prompting them with
 *              the given prompt.
 *
 *              Returns -1 if the user entered "end"
 *              Returns a number from 0 to 14 if the user entered
 *              a valid peg number.
 *              Prints an error message and exits the program if an
 *              input/output error occurred
 *
 *              This is a pretty complex function.  Don't be worried if 
 *              it is a bit hard to understand.
 *
 *              "static" indicates that this function is only
 *              available in this file.
 *
 */

static int get_pegnum(const char *prompt)
{
    char buffer[BUFSIZE];
    int got_input = 0;
    int peg_num = -1;
    
    /* Loop until we get something valid from the user. */
    while (!got_input) 
    {
        /* Print out the provided prompt. */
        printf("%s", prompt);
        
        /* 
         * This reads a line of up to BUFSIZE characters from the user.
         * fgets returns NULL if there is an input error.
         */
        if (fgets(buffer, BUFSIZE, stdin) == NULL) 
        {
            fprintf(stderr, "\n");
            fprintf(stderr, "An error occurred while reading input.  "
                    "Exiting program.\n");
            exit(1);
        } 
        else 
        {
            /* We successfully read in a line of input. */
            int start;
            int len;
            int pos;
            
            /* 'len' holds the length of the string in 'buffer'. */
            len = strlen(buffer);
            
            /* 
             * Strip off any whitespace at the end of the string, by
             * writing 0 (the end of string character) over it.  Updates
             * 'len' to keep it at the length of the string.
             */
            while ((len > 0) && isspace(buffer[len-1])) 
            {
                len--;
                buffer[len] = 0;
            }
            
            for (start = 0; isspace(buffer[start]); start++) 
            {
                /* 
                 * No actions in the loop -- we just want start to be the
                 * position of the first non-whitespace character.
                 */
            }
            
            /* 
             * Start is now the position of the first non-whitespace
             * character in buffer.
             */
            if (buffer[start] == 0) 
            {
                /* The string was all whitespace, soprompt again. */
                continue;
            }
            
            /* Check if they said "end". */
            if ((buffer[start] == 'e')
                && (buffer[start + 1] == 'n')
                && (buffer[start + 2] == 'd')
                && (buffer[start + 3] == 0))
            {
                got_input = 1;
                peg_num = -1; /* This is how we tell our caller the user
                               * said "end".
                               */
            } 
            else 
            {
                /* 
                 * They didn't say "end", so we need to find out if they
                 * entered a number.
                 */
                
                int is_number = 1; /* true until proven false */
                
                if (buffer[start] == '-') 
                {
                    pos = start + 1;  /* Skip over starting '-'. */
                } 
                else 
                {
                    pos = start;  /* no minus to skip over */
                }

                for ( ; pos < len; pos++) 
                {
                    /* 
                     * It isn't a number if it contains any 
                     * non-digit characters.
                     */

                    if (!isdigit(buffer[pos])) 
                    {
                        is_number = 0;
                    }
                }
                
                if (!is_number) 
                {
                    printf("\nYou must enter either a peg number "
                           "(0 to 14, inclusive)\n");
                    printf("or the word \"end\". (without the quotes)\n");
                } 
                else 
                {
                    /* 
                     * 'atoi(buffer + start)' converts the string starting 
                     * at position 'start' in buffer to an integer.
                     */
                    peg_num = atoi(buffer + start);

                    if ((peg_num < 0) || (peg_num > 14))
                    {
                        printf("\nThat isn't a valid peg number "
                               "(0 to 14, inclusive)\n");
                    } 
                    else 
                    {
                        /* We got a valid peg number! */
                        got_input = 1;
                    }
                } /* from else clause of if (!is_number) */
            } /* from else clause of if (buffer is "end") */
        }  /* from else clause of if (fgets(...) == NULL) */
    }  /* from while(!got_input) */

    return peg_num;
}


/* 
 * triangle_input:  Allows the user to input a starting position for
 *                  the triangle game.
 *
 *                  The board must be an array of 15 integers, which will
 *                  contain the resultant board on completion.
 */

void triangle_input(int board[])
{
    int index;
    int done = 0;
    
    /* First, clear the board. */
    for (index = 0; index < BOARD_SIZE; index++) 
    {
        board[index] = 0;
    }
    
    while (!done) 
    {
        int peg_num;
        
        /* Show the current board. */
        triangle_print(board);
        
        /* Prompt the user. */
        printf("\n");
        printf("Enter a number to insert/remove a peg from that space, "
               "or enter the\n");
        printf("word \"end\" when the board is set up.\n");
        printf("\n");
        
        peg_num = get_pegnum("Input: ");
        
        if (peg_num < 0) 
        {
            /* They entered "end". */
            done = 1;
        } 
        else 
        {
            /* Invert the entered in peg. */
            board[peg_num] = !board[peg_num];
        }
    }
    
    /* 
     * At this point, they have entered in their desired board, 
     * so we return. 
     */

    return;
}

