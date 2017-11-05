#include <cs50.h>
#include <stdio.h>
#include <math.h>

// Initialize prototype function
int getCoins(float change);

// Assignment pset1/greedy
int main(void)
{
    // Initialize variable
    float change;

    // Get input from user
    do
    {
        printf("O hai! How much change is owed? ");
        change = get_float();
    }
    while (change < 0);

    // Initialize variable and call function
    int coins = getCoins(change);

    // Print results
    printf("%d\n", coins);
}


// Returns the number of coins
int getCoins(float change)
{

    // First convert float to int
    change = round(change * 100);
    // Now we are working with an int

    int coins = 0;

    // Loop through decreasing coin sizes
    while
    (change >= 25)
    {
        change = change - 25;
        coins++;
    }
    while
    (change >= 10)
    {
        change = change - 10;
        coins++;
    }
    while
    (change >= 5)
    {
        change = change - 5;
        coins++;
    }
    while
    (change >= 1)
    {
        change = change - 1;
        coins++;
    }
    return coins;
}

