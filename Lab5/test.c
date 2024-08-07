#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void){
    printf("size of integer: %d\n",     sizeof(int));
    printf("size of (int *): %d\n",     sizeof(int *));


    int arr[] = {1, 2, 3, 4, 5};
    printf("arr[3] = %d\n", arr[3]);
    printf("arr[3] = %d\n", *(arr + 3));


    int i;
    srand(time(0));
    for (i = 0; i < 20; i++)
    {
        printf("%d ",  (int) rand() % (2));
    }
    
    return 0;
}