#include <cs50.h>
#include <stdio.h>
#include <math.h>

int getCoins(float change, int coins);

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
    while (change < 0.0f);

    //printf("Change == %f\n",change);
    int coins = getCoins(change, 0);
    printf("\n22.Coins == %d\n",coins);
}

// Returns the number of coins
int getCoins(float change, int coins){
    printf("27. getCoins(%.65f,%d)\n", change, coins);

    // First convert float to int
    change = change*100;
    //change = change/100;
    // double round(double change);

    //printf("32. getCoins(%.65f,%d)\n", change, coins);
    //printf("35. %.65f\n", round(change));
    change = round(change);
    //change = change/100;
    printf("37. %.65f\n", change);

    if (change == 0)
    {
        printf("30. change == 0");
        return coins;
    }

    float rmdr = 0.0;
    // I refactored separate if blocks into nested if blocks
    if (change >= 1)
    {
        if (change >= 5)
        {
            if (change >= 10)
            {
                if (change >= 25)
                {
                    rmdr = (fmod(change, 25));
                    if (rmdr == 0)
                    {
                        coins = change / 25;
                        // printf("coins == %d\n", coins);
                        printf("49.inside if(rmdr == 0) %d\n", coins);
                        return coins;
                    }
                    printf("52.rmdr == %f\n", rmdr);
                    coins+= (change - rmdr) / 25;
                    printf("54.coins == %d\n", coins);
                    getCoins(rmdr/100, coins);
                }

                // .10 <= change < .25
                rmdr = (fmod(change, 10));
                if (rmdr == 0)
                {
                    // change is a multiple of .10
                    coins = change / 10;
                    printf("66.inside if(rmdr == 0) %d\n", coins);
                    return coins;
                }
                printf("69.rmdr == %f\n", rmdr);
                coins+= (change - rmdr) / 10;
                printf("71.coins == %d\n", coins);
                getCoins(rmdr/100, coins);

            }

            // .05 <= change < .10
            rmdr = (fmod(change, 5));
            if (rmdr == 0)
            {
                coins += change / 5;
                printf("84.inside if(rmdr == 0) %d\n", coins);
                return coins;
            }
            printf("87.rmdr == %.65f\n", rmdr);
            coins+= (change - rmdr) / 5;
            printf("89.coins == %d\n", coins);
            getCoins(rmdr/100, coins);
        }


        // .01 <= change < .05
        rmdr = (fmod(change, 1));
        if (rmdr == 0)
        {
            coins = change / 1;
            printf("101.inside if(rmdr == 0) %d\n", coins);
            return coins;
        }
        printf("104.rmdr == %f\n", rmdr);
        coins+= (change - rmdr) / 1;
        printf("106.coins == %d\n", coins);
        getCoins(rmdr/100, coins);
    }
    return coins;
}

