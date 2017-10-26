#include <cs50.h>
#include <stdio.h>
#include <math.h>

// Assignment pset1/greedy
int main(void)
{
    // Get input from user
    float change;
    do
    {
        printf("O hai! How much change is owed? ");
        change = get_float();

    }
    while (change < 0);

    if (change > 0.25)
    {
        // do modulo
        if (fmod(change, 0.25) == 0)
        {
            // change is a multiple of .25
            int coins = change / .25;
            printf("%d\n", coins);
            return 0;
        }
    }

    // if (change > 0.10)
    // {
    //     // do modulo
    //     if ((int)change % .10 == 0)
    //     {
    //         // change is a multiple of .10
    //         // change < .25
    //         return (int)change / (int).10;
    //     }
    // }

    // if (change > 0.05)
    // {
    //     // do modulo
    //     if ((int)change % .05 == 0)
    //     {
    //         // change is a multiple of .05
    //         // change < .10
    //         return (int)change / (int).05;
    //     }
    // }

    // if (change > 0.01)
    // {
    //     // do modulo
    //     if ((int)change % .01 == 0)
    //     {
    //         // change is a multiple of .01
    //         // change < .05
    //         return (int)change / (int).01;
    //     }
    // }
}
