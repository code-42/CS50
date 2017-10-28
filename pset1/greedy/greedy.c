#include <cs50.h>
#include <stdio.h>
#include <math.h>

int getCoins(float change, int coins);
int calcCoins(float change, int coins,  int denomination);

// Assignment pset1/greedy
int main(void)
{
    // Get input from user
    float change = 0;
    do
    {
        printf("O hai! How much change is owed? ");
        change = get_float();
    }
    while (change < 0.0f);

    //printf("Change == %f\n",change);
    int coins = getCoins(change, 1);
    printf("\n22.Coins == %d\n",coins);
}

// Returns the number of coins
int getCoins(float change, int coins){
    printf("27. getCoins(%.65f,%d)\n", change, coins);

    // First convert float to int
    change = change*100;
    change = round(change);
    printf("37. %.65f\n", change);
    // Now we are working with an int * 100
    // return it to cents when returns to main

    int denomination = 0;
    if (change == 0)
    {
        printf("30. change == 0");
        return coins;
    }

    // I refactored separate if blocks into nested if blocks
    // First determine amount of change and denomination size
    if (change >= 1)
    {
        if (change >= 5)
        {
            if (change >= 10)
            {
                if (change >= 25)
                {
                    denomination = 25;
                    printf("65. change == %f denomination == %d\n", change, denomination);
                    coins = calcCoins(change, coins, denomination);
                }
                denomination = 10;
                printf("59. change == %f denomination == %d\n", change, denomination);
                coins = calcCoins(change, coins, denomination);
            }
            denomination = 5;
            printf("53. change == %f denomination == %d\n", change, denomination);
            coins = calcCoins(change, coins, denomination);
        }
        denomination = 1;
        printf("47. change == %f denomination == %d\n", change, denomination);
        coins = calcCoins(change, coins, denomination);
    }
    return coins;
}


int calcCoins(float change, int coins, int denomination){

        float remainderr = (fmod(change, denomination));
        // int coins = 0;
        if (remainderr == 0)
        {
            coins = change / denomination;
            printf("133.inside if(remainderr == 0) and coins == %d\n", coins);
            return coins;
        }
        else
        {
            printf("136.rmdr == %f\n", remainderr);
            coins = (change - remainderr) / denomination;
            printf("138.coins == %d\n", coins);
            getCoins(remainderr/100, coins);
            return coins;
        }
        // return coins;
}