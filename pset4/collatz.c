#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int collatz(int n);

int main(int argc, string argv [])
{
    if(argc != 2)
    {
        printf("usage: ./collatz n");
        return 1;
    }
    int n = atoi(argv[1]);
    printf("%d \n", collatz(n));
}


int collatz(int n)
{
    if (n == 1)
        // if n == 1 then stop
        return 0;
    else if ((n % 2) == 0)
        // if n is even return n/2
        return 1 + collatz(n / 2);
    else
        // if n is odd return 3n + 1
        return 1 + collatz((3 * n) + 1);
}