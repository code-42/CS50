#include <cs50.h>
#include <stdio.h>

// Assignment pset1/credit
int main(void)
{
    // Get input from user and store in n
    long long cc;
    int count = 0;
    do
    {
        printf("Please enter credit card number: ");
        cc = get_long_long();

        // Count the number of digits in cc
        long long ccc = 0;
        count = 0;
        ccc = cc;
        while(ccc)
        {
            ccc=ccc/10;
            count++;
        }

    }
    while (count != 13 && count != 15 && count != 16);


    printf("Success: You entered %d digits in cc: %lli\n", count, cc);


    return 0;
}