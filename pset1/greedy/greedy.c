#include <cs50.h>
#include <stdio.h>
#include <math.h>

int getCoins(float change);

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
    
    // I refactored separate if blocks into nested if blocks
    // and changed >= to <
    if (change >= 0.25)
    {
        if (change < 0.25)
        {
            if (change < 0.10)
            {
                if (change < 0.05)
                {
                    // .04 % .01 == 0
                    float rmdr = (fmodf(change, 0.01));
                    printf("46.outside if(rmdr == 0) %f\n", rmdr);
                    if (rmdr == 0)
                    {
                        coins = change / .01;
                        // printf("coins == %d\n", coins);
                        printf("51.inside if(rmdr == 0) %d\n", coins);
                        return coins;
                    }
                } 
                    
                // if change < .10
                float rmdr = (fmodf(change, 0.10));
                printf("56.outside if(rmdr == 0) %f\n", rmdr);
                if (rmdr == 0)
                {
                    // change is a multiple of .10
                    coins = change / .10;
                    // printf("coins == %d\n", coins);
                    printf("63.inside if(rmdr == 0) %d\n", coins);
                    return coins;
                }
                // subtract rmdr and recurse it
                getCoins(rmdr);
      
            }
            
            // change > .10 && < .25
            float rmdr = (fmodf(change, 0.25));
            printf("70.outside if(rmdr == 0) %f\n", rmdr);
            if (rmdr == 0)
            {
                // change is a multiple of .25
                coins += change / .25;
                // printf("%d\n", coins);
                printf("76.inside if(rmdr == 0) %d\n", coins);
                return coins;
            }
            getCoins(rmdr);
    
        }

        // change > .25
        float rmdr = (fmodf(change, 0.25));
        printf("89.outside if(rmdr == 0) %f\n", rmdr);
        if (rmdr == 0)
        {
            // change is a multiple of .01
            coins = change / .25;
            // printf("coins == %d\n", coins);
            printf("95.inside if(rmdr == 0) %d\n", coins);
            return coins;
        }
        getCoins(rmdr);
    }

    return 1;
}
