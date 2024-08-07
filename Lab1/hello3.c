#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*  
 * main:
 *     This function asks for an input from the user, and generates a random 
 *     integer `n` between 1 and 10. A different salutation is then printed
 *     based on if `n` is even or odd, `n` times.
 * 
 *     Arguments: none.
 *     Return value: none.
 */

int main(void)
{
    char name[100];
    int n;
    int i;

    srand(time(0));

    printf("What's your name?\n");
    scanf("%99s", name);
    
    n = (int) 1 + rand() % 10;

    if (n % 2 == 0)
    {
        for (i = 0; i < n; i++)
        {
            printf("%d: hello, %s!\n", n, name);
        }
    }
    else
    {
        for (i = 0; i < n; i++)
        {
            printf("%d: hi there, %s!\n", n, name);
        }
    }

    return 0;
}
