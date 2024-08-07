#include <stdio.h>

void sorting_bubble_sort(int input_array[], int length_array);

int main(void){
    int  i = 10; 
    int *j = &i; 
    printf("i = %d\n", i); 
    printf("j = %x\n", j); 
    printf("j points to: %d\n", *j);

    int input_array[5] = {1, 4, 3, 6, 3};
    int length_array = 5;
    printf("%d, %d \n", input_array[1], input_array[2]);
    sorting_bubble_sort(input_array, length_array);
    printf("%d, %d \n", input_array[1], input_array[2]);
}

void sorting_bubble_sort(int input_array[], int length_array){
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
}