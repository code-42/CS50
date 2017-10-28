#include <cs50.h>
#include <stdio.h>
#include <math.h>

int getCoins(float change);

<<<<<<< HEAD
=======

>>>>>>> dev3
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

<<<<<<< HEAD
    printf("Change == %f\n",change);
    int coins = getCoins(change);
    printf("Coins == %d\n",coins);
}


int getCoins(float change){
    // Returns the number of coins
    int nQuarters = 0;
    int nDimes = 0;
    int nNickles = 0;
    int nPennies = 0;
    int coins = nQuarters + nDimes + nNickles + nPennies;
    if (change >= 0.25)
    {
        // do modulo
        float rmd = (fmodf(change, 0.25));
        printf("32.outside if(rmd == 0) %f\n", rmd);
        if (rmd == 0)
        {
            // change is a multiple of .25
            coins += change / .25;
            // printf("%d\n", coins);
            printf("37.inside if(rmd == 0) %f\n", rmd);
            return coins;
        }
        else
        {
            float baseCoin = change - rmd;
            nQuarters = baseCoin / .25;
            printf("remainingChange == %f\n", rmd);
            getCoins(rmd);
        }
    }

    else if (change >= 0.10)
    {
        // do modulo
        float rmd = (fmodf(change, 0.10));
        if (rmd == 0)
        {
            // change is a multiple of .10
            coins = change / .10;
            // printf("coins == %d\n", coins);
            return coins;
        }
    }

    else if (change >= 0.05)
    {
        // do modulo
        float rmd = (fmodf(change, 0.05));
        if (rmd == 0)
        {
            // change is a multiple of .05
            // change < .10
            coins = change / .05;
            // printf("coins == %d\n", coins);
            return coins;
        }
    }

    else  // change < .05
    {
        // do modulo
        float rmd = (fmodf(change, 0.01));
        if (rmd == 0)
        {
            // change is a multiple of .01
            coins = change / .01;
            // printf("coins == %d\n", coins);
            return coins;
        }
    }

    return 1;
=======
    //printf("Change == %f\n",change);
    int coins = getCoins(change);
    printf("%d\n",coins);
}

// Returns the number of coins
int getCoins(float change){

    // First convert float to int
    change = round(change*100);
    // Now we are working with an int

    int coins = 0;
    while(change >= 25)
    {
        change = change - 25;
        coins++;
    }
    while(change >= 10)
    {
        change = change - 10;
        coins++;
    }
    while(change >= 5)
    {
        change = change - 5;
        coins++;
    }
    while(change >= 1)
    {
        change = change - 1;
        coins++;
    }
    return coins;
>>>>>>> dev3
}

