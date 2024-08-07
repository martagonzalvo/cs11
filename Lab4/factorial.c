#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* prototype */
int factorial(int n);

int factorial(int n)
{
    assert(n >= 0);

    if (n == 0)
    {
        return 1;
    }
    else
    {
        /* Recursive call to the factorial function: */
        return (n * factorial(n - 1));
    }
}

int main(int argc, char *argv[])
{
    int n, f;

    if (argc != 2)
    {
        fprintf(stderr, "usage: %s n\n", argv[0]);
        exit(1);
    }

    n = atoi(argv[1]);
    f = factorial(n);
    printf("factorial of %d = %d\n", n, f);

    return 0;
}