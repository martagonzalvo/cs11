#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "triangle_routines.h"
#define NMOVES 36
#define BOARD_SIZE 15

/*
 * The `triangle_game` function solves the solitaire "Triangle Game" board
 *     board game, played on a triangular board with fifteen equally-spaced
 *     holes in the shape of a pyramid. Initially all holes except for one,
 *     the middle hole on a 3-hole row are filled with pegs. The goal of the
 *     game is to make the game last as long as possible (13 moves). Each move
 *     eliminates a peg, by moving an adjacent peg over it to the adjacent hole
 *     in the opposite side of the peg to be eliminated. 
 * 
 * This function takes an input board and checks that it is solvable, and 
 *     prints the best moves in inverse order to solve the board.
 */

/* List of valid moves */
int moves[NMOVES][3] =
{
    {0, 1, 3},
    {3, 1, 0},
    {1, 3, 6},
    {6, 3, 1},
    {3, 6, 10},
    {10, 6, 3},
    {2, 4, 7},
    {7, 4, 2},
    {4, 7, 11},
    {11, 7, 4},
    {5, 8, 12},
    {12, 8, 5},
    {0, 2, 5},
    {5, 2, 0},
    {2, 5, 9},
    {9, 5, 2},
    {5, 9, 14},
    {14, 9, 5},
    {1, 4, 8},
    {8, 4, 1},
    {4, 8, 13},
    {13, 8, 4},
    {3, 7, 12},
    {12, 7, 3},
    {3, 4, 5},
    {5, 4, 3},
    {6, 7, 8},
    {8, 7, 6},
    {7, 8, 9},
    {9, 8, 7},
    {10, 11, 12},
    {12, 11, 10},
    {11, 12, 13},
    {13, 12, 11},
    {12, 13, 14},
    {14, 13, 12}
};


int npegs(int board[]);
int valid_move(int board[], int move[]);
void make_move(int board[], int move[]);
void unmake_move(int board[], int move[]);
int solve(int board[]);


int main(void)
{
    /* Taking input board from the user. */
    int board[BOARD_SIZE];
    triangle_input(board); 

    /* 
     * Solving the boards with a recursive function, which will also print
     * the moves in reverse order.
     */
    printf("Game is solved with the following moves in reverse order:\n");
    solve(board);

    return 0;
}


/* Return the number of pegs on the board. */
int npegs(int board[])
{
    /* We add up the number of pegs on the board. */
    int i;
    int sum = 0;
    for (i = 0; i < BOARD_SIZE; i++)
    {
        sum += board[i];
    }
    return sum;
}


/* Return 1 if the move is valid on this board, otherwise return 0. */
int valid_move(int board[], int move[])
{
    /* Check that there is an empty hole, and that the starting peg and 
     *     the peg to be removed are present.
     */
    if (
        board[move[0]] == 0 && board[move[1]] == 1 && board[move[2]] == 1
        )
    {  
        return 1;
    }
    else
    {
        return 0;
    }
}


/* Make this move on this board by moving jumping over an adjacent
 * peg and landing into an empty hole. The peg that was jumped over is 
 * eliminated. 
 */
void make_move(int board[], int move[])
{
    board[move[0]] = 1;
    board[move[1]] = 0;
    board[move[2]] = 0;
}

/* Unmake this move on this board, adding peg that was jumped over and
 * eliminated and moving peg that jumped to adjacent hole next to the peg
 * that was eliminated.
 */
void unmake_move(int board[], int move[])
{

    board[move[0]] = 0;
    board[move[1]] = 1;
    board[move[2]] = 1;
}


/*
 * Solve the game starting from this board.  Return 1 if the game can
 * be solved; otherwise return 0.  Do not permanently alter the board passed
 * in. Once a solution is found, print the boards making up the solution in
 * reverse order.
 */
int solve(int board[])
{
    int i;
    /* Base case, board is solved. */
    if (npegs(board) == 1)
    {
        triangle_print(board);
        return 1;
    } 

    /* For each valid move, check if it's valid in the current board and make
     * the move. */
    for (i = 0; i < NMOVES; i++)
    {
        if (valid_move(board, moves[i]) == 1)
        {
            make_move(board, moves[i]);

            /* With that move, check iteratively with this same function if
             * the board is solved. If it leads to a solved board, unmake the
             * move and print the board. It will lead to printing every move in
             * order. 
             */
            if (solve(board) == 1)
            {
                unmake_move(board, moves[i]);
                triangle_print(board);
                return 1;
            }
            /* Unmake the move and return the board untouched. */
            unmake_move(board, moves[i]);  
        }
    }
    return 0;
}