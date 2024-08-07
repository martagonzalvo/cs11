#include <stdio.h>

/*
 * main:
 *     This function asks the user to input their name, and then prints the 
 *     salutation "hello, <name>!".
 * 
 *     Arguments: none.
 *     Return value: none.
 */

int main(void)
{
    char name[100];

    printf("What's your name?\n");
    scanf("%99s", name);
    printf("hello, %s!\n", name);

    return 0;
}
