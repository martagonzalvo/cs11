#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "memcheck.h"
#include "linked_list.h"
#define DEBUG 0

/* 
 * The sorter function sorts an arbitrary number of integers and prints them in 
 *     increasing order, based on the quicksort algorithm. 
 *     Arguments: integers to be sorted, [-q]
 *     Returns: Printed list of integers in increasing order
 */


node *quicksort(node *list);


int main(int argc, char *argv[])
{
    int i;
    int quiet = 0;
    int list_length = 0;

    node *sorted_list;        /* pointer to the list */
    node *list;        /* pointer to the list */
    node *temp;        /* temporary pointer to node */
    list = NULL;       /* NULL represents the empty list. */

    /*
     * We will analyze the command line input by checking for -q tags, 
     *     create new node in a linked list for each number.
     *     `-q` indicates the program will not print any output
     */
    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-q") == 0)
        {
            quiet = 1;
        } 
        else
        {
            temp = create_node(atoi(argv[i]), list);
            /* Set the 'list' pointer to point to the new node. */
            list = temp;
            list_length++;
        }        
    }

    /*
     * Checking that there is at least 1 input number. Otherwise,
     *     the program exits.
     */
    if (list_length == 0)
    {
        fprintf(
            stderr,
            "usage: %s[-q] number1 [number2 ...]\n",
            argv[0]
        );
        exit(1);
    }

    /* Sorting the list with the quicksort algorithm. */

    sorted_list = quicksort(list);

    /* Printing the ordered input array of numbers from lowest to highest. */

    if (quiet == 0)
    {
        print_list(sorted_list);
    }

    /* Freeing the used memory and checking for memory leaks. */
    free_list(list);
    free_list(sorted_list);
    print_memory_leaks();
    
    return 0;    
}

/* 
 * This function uses the efficient quicksort algorithm on a linked list.
 *     From the starting list and a given value of the list, the list is 
 *     divided into two sub-lists containing smaller and larger
 *     values than the starting given value; and those list are sorted 
 *     recursively.
 *     Arguments: list to be sorted.
 *     Returns: Pointer to new sorted list.
 */

node *quicksort(node *list)
{
    node *start;
    node *list_small; 
    node *list_large;
    node *prev;
    node *curr; 
    node *sorted_list_small;
    node *sorted_list_large;
    node *sorted_list_temp;
    node *sorted_list;

    int pivot;
    int curr_data;

    /* If list is empty or 1 node, list is fully sorted.  */
    if (list == NULL || list -> next == NULL)
    {
        return copy_list(list);
    }

    /* Creating a copy of the first node of the list. */
    start = create_node(list->data, NULL);
    
    /* Current value of the first node and next node to compare to. */
    pivot = list->data;
    curr = list->next;
    
    /* 
     * Creating two lists from the original, one with values smaller than the
     * value of the first node and another large one with values equal or 
     * larger than the value of the original node `pivot`.
     */
    list_small = NULL;
    list_large = NULL;

    while (curr != NULL)
    {   
        curr_data = curr->data;

        /* 
         * Creating the large or equal list and copying into it the appropriate
         * values, starting a new list or linking to the start of the existing 
         * `list_large`. 
         */
        if (curr_data >= pivot)
        {
            if (list_large == NULL)
            {
                list_large = create_node(curr_data, NULL);
            }
            else 
            {   
                prev = create_node(curr_data, list_large);
                list_large = prev;
            }
        }
        /* 
         * Creating the smaller list and copying into it the appropriate
         * values, starting a new list or linking to the start of the existing 
         * `list_small`. 
         */
        else
        {
            if (list_small == NULL)
            {
                list_small = create_node(curr_data, NULL);
            }
            else 
            {   
                prev = create_node(curr_data, list_small);
                list_small = prev;
            }
        }
        curr = curr->next;
    }

    /* 
     * Recursively sorting the two lists with the quicksort function, and
     *    appending them to the final sorted list: smaller than first
     *    node, copy of the first node, and larger or equal to the first
     *    node. 
     */
    sorted_list_small = quicksort(list_small);
    sorted_list_large = quicksort(list_large);
    
    sorted_list_temp = append_lists(start, sorted_list_large);
    sorted_list = append_lists(sorted_list_small, sorted_list_temp);

    /* Freeing all the memory used in all the created lists. */
    free(start);
    free_list(list_small);
    free_list(list_large);
    free_list(sorted_list_small);
    free_list(sorted_list_large);
    free_list(sorted_list_temp);

    /*
     * Checking that the list is sorted correctly before returning.
     */
    assert(is_sorted(sorted_list));
    
    return sorted_list; 
}