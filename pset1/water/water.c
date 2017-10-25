#include <cs50.h>
#include <stdio.h>

// Assignment pset1/water
int main(void)
{
    // Get input from user and store in n
    int n;
    do
    {
        printf("Minutes: ");
        n = get_int();

    }
    while (n <= 0);
    // Calculate bottles of water used
    printf("Bottles: %i\n", n * 12);
    return 0;
}