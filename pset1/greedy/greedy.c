#include <cs50.h>
#include <stdio.h>
#include <math.h>

int getCoins(float change);
int calcCoins(int cents, int coins,  int denomination);

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

    // Separate preentation from logic
    int coins = getCoins(change);
    printf("\n22.Coins == %d\n",coins);
}

// Returns the number of coins
int getCoins(float change){
    printf("27. getCoins(%.65f)\n", change);

    // First convert float to int
    // int cents = round(change);
    int cents = change*100;
    // cents = round(cents);
    printf("37. convert to cents: %d cents\n", cents);
    // Now we are working with an int * 100

    int coins = 0;
    int denomination = 0;
    if (change == 0.0f)
    {
        printf("30. change == 0");
        return coins;
    }

    // I refactored separate if blocks into switch case statement
    // First determine amount of change and denomination size

    if (cents >= 25)
    {
        if (cents < 25)
        {
            if (cents < 10)
            {
                if (cents < 5)
                {
                    denomination = 1; // Pennies
                }
                denomination = 5; // Nickels
            }
            denomination = 10; // Dimes
        }
        denomination = 25; // Quarters
    }


   switch(denomination){
    case 25:
        printf("66. cents == %d, coins == %d, denomination == %d\n", cents, coins, denomination);
        coins = calcCoins(cents, coins, denomination);
        break;

    case 10:
        printf("71. cents == %d, coins == %d, denomination == %d\n", cents, coins, denomination);
        coins = calcCoins(cents, coins, denomination);
        break;

    case 5:
        printf("76. cents == %d, coins == %d, denomination == %d\n", cents, coins, denomination);
        coins = calcCoins(cents, coins, denomination);
        break;

    case 1:
        printf("81. cents == %d, coins == %d, denomination == %d\n", cents, coins, denomination);
        coins = calcCoins(cents, coins, denomination);
        break;
    }
    return coins;
}


int calcCoins(int cents, int coins, int denomination){

        int remainderr = (cents % denomination);
        printf("92. %d mod %d == %d\n", cents, denomination, remainderr);
//         if (remainderr == 0)
//         {
//             coins = cents / denomination;
//             printf("96.inside if(remainderr == 0) and coins == %d\n", coins);
//             return coins;
//         }
//         else
//         {
//             printf("101.rmdr == %d\n", remainderr);
//             coins = (cents - remainderr) / denomination;
//             printf("103.coins == %d\n", coins);
//             return getCoins(remainderr/100);
//             // return coins;
//         }

        if (remainderr > 0)
        {
            printf("101.remainderr == %d\n", remainderr);
            coins = (cents - remainderr) / denomination;
            printf("103.coins == %d\n", coins);
            printf("114. remainderr/100 == %.165f\n", (double)remainderr/100);
            return getCoins((double)remainderr/100);
            // return coins;
        }
        else
        {
            coins = cents / denomination;
            printf("96.inside if(remainderr == 0) and coins == %d\n", coins);
            return coins;
        }
}