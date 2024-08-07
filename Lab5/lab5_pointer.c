#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "memcheck.h"

/* 
 * This programs simulates a simple one-dimensonal cellular automaton, which
 *     is a collection of cells arranged in a line. After being randomly
 *     populated initially with any of two states, the value of cells change
 *     over time depending on the value of its two immediate neighbors. This
 *     program takes a number of cells and number of generations that the 
 *     automaton should evolve for, and prints the result on the terminal,
 *     producing interesting triangle-shaped geometric patterns. This program
 *     uses pointer operations in the update function that evolves every 
 *     generation.
 */

void print_generation(int cells[], int num_cells);
void update_generation(int *cells, int num_cells);

/*
 * main:
 *     This function asks for a number of cells `num_cells` and number of 
 *     generations `num_generations`. It creates a one dimensional cellular 
 *     automaton of size `num_cells` and evolves it for as many generations as
 *     `num_generations` specifies. It prints every generation forming
 *     interesting geometric patterns.
 *  
 *     Arguments: num_cells, num_generations
 *     Return value: none
 */

int main(int argc, char *argv[])
{
    int num_cells, num_generations, i;
    int *cells;

    /*
     * Checking input is correct and sufficient, and that thre are at least 3
     * cells.
     */
    if (argc != 3 || atoi(argv[1]) < 3)
    {
        fprintf(
            stderr,
            "usage: %s num_cells num_generations (min 3 cells)\n",
            argv[0]
        );
        exit(1);
    }

    num_cells = atoi(argv[1]);
    num_generations = atoi(argv[2]);

    /*
     * Creating dynamic memory allocated array for cells, filling all values
     * with 0.
     */
    cells = (int *) calloc(num_cells, sizeof(int));
    if (cells == NULL)
    {
        fprintf(stderr, "Error! Memory allocation failed!\n");
        exit(1); 
    }

    /* 
     * Random seed with time to create first generation in `cells`. First and 
     * last cells are always empty (0).
     */
    srand(time(0));
    for (i = 1; i < num_cells - 1; i++) 
    {
        cells[i] = (int) rand() % 2;
    }
    print_generation(cells, num_cells);

    /*
     * Updating and printing all the indicated successive generations.
     */
    for (i = 0; i < num_generations; i++)
    {
        update_generation(cells, num_cells);
        print_generation(cells, num_cells);
    }

    /* Freeing dynamic memory and checking for memory leaks. */
    free(cells);
    print_memory_leaks();

    return 0;
}


/*
 * update_generation:
 *     This function updates a generation of cells of an array `cells` 
 *     changing its occupancy (0 empty, 1 full) based on two rules:
 *         - If a cell is full and any of the adjacent cells are full: 1, full
 *         - Otherwise, cell will change to 0, empty
 *     Arguments: cells, num_cells
 *     Return value: None
 * 
 */

void update_generation(int *cells, int num_cells)
{
    int *new_array, i, *previous, *current, *next, *new_value;

    /*
     * Creating new array that will store updated values, filled with 0s. Later
     * `cells` will point to this array's location.    
     */
    new_array = (int *) calloc(num_cells, sizeof(int));
    if (new_array == NULL)
    {
        fprintf(stderr, "Error! Memory allocation failed!\n");
        exit(1); 
    }

    /* 
     * Creating necessary pointers to verify the rules of the generation
     * update, and updating the new value only on the new array so that cells
     * remains intact throughout.
     */
    previous = cells;
    current = previous + 1;
    next = current + 1;

    new_value = new_array + 1;

    for (i = 1; i < num_cells - 1; i++)
    {
        if ((*previous + *next) == 1 && *current == 0)
        {
            *new_value = 1;
        }
        previous++;
        current++;
        next++;
        new_value++;
    }

    /*
     * Copying new_array into cells and freeing the allocated memory for the 
     * used `new_array`.
     */
    memcpy(cells, new_array, num_cells * sizeof(int));
    free(new_array); 
}


/*
 * print_generation:
 *     This function prints the occupancy of the one dimensional cellular 
 *     automaton array `cells`, printing empty (0) as `.` and full (1) as `*`
 *     for a given generation and occupancy.
 * 
 *     Arguments: int cells, int num_cells
 *     Return value: none
 * 
 */

void print_generation(int cells[], int num_cells)
{
    int i;

    for (i = 0; i < num_cells; i++)
    {
        if (cells[i] == 0)
        {
            printf(".");
        }
        else
        {
            printf("*");
        }
    }
    printf("\n");
}
