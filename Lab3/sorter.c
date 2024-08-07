#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAX_LENGTH  32

/* The sorter function sorts a lists of integers and prints them in increasing
 *     order, based on the bubble sort or minimum element algorithms. 
 *     Arguments: between 1 and 32 integers, [-b], [-q]
 *     Returns: Printed list of integers in increasing order
 */

void sorting_minimum_element(int input_array[], int length_array);
void sorting_bubble_sort(int input_array[], int length_array);

int main(int argc, char *argv[])
{
    int array_integers[MAX_LENGTH];
    int i;
    int quiet = 0;
    int sorting_bubble = 0;
    int length_array = 0;

    /*
     * We will analyze the command line input by checking for -q and -b tags, 
     *     converting the input numbers to integers, and putting them into 
     *     an array for sorting with the appropriate function. 
     *     `-q` indicates the program will not print any output
     *     `-b` indicates the sorting algorithm will be bubble sort instead
     *         of minimum element. 
     */
    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-q") == 0)
        {
            quiet = 1;
        }
        else if (strcmp(argv[i], "-b") == 0)
        {
            sorting_bubble = 1;  
        }
        else
        {
            array_integers[length_array] = atoi(argv[i]);
            ++length_array;
             /*
            * Checking that there are no more than 32 input numbers. Otherwise,
            *     the program exits.
            */
            if (length_array > MAX_LENGTH)
            {
                fprintf(
                    stderr,
                    "usage: %s [-b] [-q] num1 [num2 ...] (max 32 numbers)\n",
                    argv[0]
                );
                exit(1);
            }
        }
    }

    /*
     * Checking that there is at least 1 input number. Otherwise,
     *     the program exits.
     */
    if (length_array == 0)
    {
        fprintf(
            stderr,
            "usage: %s [-b] [-q] number1 [number2 ...] (maximum 32 numbers)\n",
            argv[0]
        );
        exit(1);
    }

    /*
     * Sorting the numbers with the default minimum element sorting function
     *    or the bubble sort.
     */
    if (sorting_bubble == 0)
    {
        sorting_minimum_element(array_integers, length_array);
    }
    else
    {
        sorting_bubble_sort(array_integers, length_array);
    }
    
    /*
     * Printing the ordered input array of numbers from lowest to highest.
     */
    if (quiet == 0)
    {
        for (i = 0; i < length_array; i++)
            printf("%d\n", array_integers[i]);
    }
    return 0;    
}

/* The function `sorting_minimum_element` uses the minimum element sorting
 *     algorithm to sort the elements in a list.
 *     Arguments: integer array of numbers, length of the array - 1
 *     Returns: sorted array of numbers in increasing order
 */
void sorting_minimum_element(int input_array[], int length_array)
{
    int start, smallest, index, temporary, i;
   /*
     * We loop through the array to find the smallest element and put it in the
     *     first position, and iterate with the remaining array starting at the
     *     next position until the whole array is sorted.
     * We check that the elements have been sorted with an assert statement.
     */
    start = 0;
    for (start = 0; start < length_array; start++)
    {
        smallest = start;
        for (index = start; index < length_array; index++)
        {
            if (input_array[index] < input_array[smallest])
            {
                smallest = index;
            }
        }
        temporary = input_array[start];
        input_array[start] = input_array[smallest];
        input_array[smallest] = temporary;
    }

    for (i = 1; i < length_array; i++)
    {
        assert(input_array[i] >= input_array[i-1]);
    }    
}

/* The `sorting_bubble_sort` function uses the Bubble sort algorithm to sort
 *     the elements in a list. 
 *     Arguments: integer array of numbers, length of the array - 1
 *     Returns: sorted array of numbers in increasing order
 */
void sorting_bubble_sort(int input_array[], int length_array)
{
    int swapped, temporary, i;
    /*
     * We check for every number if it is larger than the following number
     *     in the array. If it is larger, we swap the numbers and continue
     *     iteratively until the whole array has been looped through and 
     *     no elements have been swapped.
     * We check that the elements have been sorted with an assert statement.
     */
    swapped = 1;
    while (swapped == 1)
    {
        swapped = 0;
        for (i = 1; i < length_array; i++) 
        /******  until length -1? I don't think so bc already started 0 **/
        {
            if(input_array[i-1] > input_array[i])
            {
                temporary = (int) input_array[i-1];
                input_array[i-1] = input_array[i];
                input_array[i] = (int) temporary;
                swapped = 1;
            }
        }
    }
    for (i = 1; i < length_array; i++)
    {
        assert(input_array[i] >= input_array[i-1]);
    } 
}