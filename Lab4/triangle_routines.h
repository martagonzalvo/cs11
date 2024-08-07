/*
 * FILE: triangle_routines.h
 *
 */

#ifndef _TRIANGLE_ROUTINES_H
#define _TRIANGLE_ROUTINES_H

#define BOARD_SIZE 15

/* 
 * triangle_print:  Prints the triangle game represented by <board>
 *                  in a nice, visual way to the standard output.
 *
 *                  The board must be an array of 15 integers.  Non-zero
 *                  values indicate a peg in that position.
 *
 */

extern void triangle_print(const int board[]);

/* 
 * triangle_input:  Allows the user to input a starting position for
 *                  the triangle game. 
 *
 *                  The board must be an array of 15 integers, which will 
 *                  contain the resulting board upon completion.  
 *
 */

extern void triangle_input(int board[]);

#endif  /* _TRIANGLE_ROUTINES_H */


