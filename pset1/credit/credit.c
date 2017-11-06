#include <cs50.h>
#include <stdio.h>

// Function prototype
void getCCbank(int digit1, int digit2);
int countCCDigits(long long cc);
long makeCCArray(int count, long long cc);

// Assignment pset1/credit
int main(void)
{
    /*
    * Temporarily comment out user input
    * Hard-code cc number instead
    * Uncomment line 24 cc = ... to get user input
    */
    // Get input from user and store in cc
    long long cc = 378282246310005;
    int count = 0;

    do
    {
        // read long long from stdin
        // cc = get_long_long("Please enter credit card number: ");

        // Count the number of digits in cc
        count = countCCDigits(cc);
    }
    while (count != 13 && count != 15 && count != 16);

    printf("Success: You entered %d digits in cc: %lli\n", count, cc);

    long *pccArray;
    pccArray = makeCCArray(count, cc);
    /*
    // Getting error returning array to pointer
    ~/workspace/cs50/pset1/credit/ (master) $ make credit
clang -fsanitize=signed-integer-overflow -fsanitize=undefined -ggdb3 -O0 -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wshadow    credit.c  -lcrypt -lcs50 -lm -o credit
credit.c:34:14: error: incompatible integer to pointer conversion assigning to 'long *' from 'long' [-Werror,-Wint-conversion]
    pccArray = makeCCArray(count, cc);
             ^ ~~~~~~~~~~~~~~~~~~~~~~
credit.c:144:12: error: incompatible pointer to integer conversion returning 'long (*)[count]' from a function with result type
      'long' [-Werror,-Wint-conversion]
    return &ccArray;
           ^~~~~~~~
2 errors generated.
make: *** [credit] Error 1
    */

    // Store first two digits of cc number to identify bank
    // int *digit1 = makeCCArray(count, cc);
    // int *digit2 = makeCCArray(count, cc);
    // // printf("72. %d%d\n", digit1, digit2);
    // getCCbank(digit1, digit2);


    return 0;
}

/////////////////////////////////////////////////////////////////////////////

int countCCDigits(long long cc)
{
         // Count the number of digits in cc
    long long ccDigits = 0;
    int count = 0;
    ccDigits = cc;
    while(ccDigits)
    {
        ccDigits=ccDigits/10;
        // printf("26. ccdigits == %lli\n", ccDigits);
        count++;
    }
    // printf("29. count == %d\n", count);
    return count;
}

/////////////////////////////////////////////////////////////////////////////

long makeCCArray(int count, long long cc)
{

    printf("36. count == %d\n", count);

    long ccArray[count];

    // Calculate number of elements in ccArray
    int arrLength = sizeof(ccArray) / sizeof(long);
    printf("39. arrLength == %d\n", arrLength);
    long n = 0;
    // count = 0;
    // Assing cc to a variable so cc does not change
    // Pass by value
    n = cc;

    // Initialize loop to number of array elements - 1
    for(int i = count - 1; i >= 0; i--)
    {
        // Digits go into array backwards
        ccArray[i] = n % 10;
        // printf("54. ccArray[%d] == %li\n", i, ccArray[i]);
        n /= 10;
    }

    printf("57. cc entered is: ");

    // Print out the cc number for sanity check
    for(int i = 0; i < count; i++)
    {
        printf("%li", ccArray[i]);
    }
    printf("\n");

/*
    // Multiply every other digit by 2, starting with the number’s second-to-last digit,
    // and then add those products' digits together.
    // int sumEveryOtherDigit = 0;
    int sumCount = 0;
    for(int i = count - 2; i >= 0; i -= 2)
    {
        printf("(%d", (int)ccArray[i]);
        printf(" x 2) + ");
        sumCount++;
        // printf("\n");
    }
    // printf("97. sumEveryOtherDigit == %d\n", sumEveryOtherDigit);

    int sumArray[sumCount];
    int sumArrLength = sizeof(sumArray) / sizeof(int);
    printf("100. sumArray.length == %d\n", sumArrLength);

    for(int i = sumArrLength - 1; i >= 0; i--)
    {
        // Digits go into array backwards
        if(n > 9)
        {
            sumArray[i] = n % 10;
            printf("110. sumArray[%d] == %d\n", i, sumArray[i]);
            n /= 10;
        }
        else
        {
            sumArray[i] = n;
        }
        printf("117. sumArray[%d] == %d\n", i, sumArray[i]);


    }

    // Print out the numbers to add up
    for(int i = 0; i < sumArrLength; i++)
    {
        printf("%d\n", sumArray[i]);
    }
    printf("\n");
*/

    return &ccArray;

}


/////////////////////////////////////////////////////////////////////////////

void getCCbank(int digit1, int digit2)
{
    printf("119. first 2 digits of cc are: %d%d \nType is: ", digit1, digit2);

    if(digit1 == 3)
    {
        if(digit2 == 4 || digit2 == 7)
            {
                printf("AMEX\n");
            }
    }

    if(digit1 == 5)
    {
        if(digit2 == 1 || digit2 == 2 || digit2 == 3 || digit2 == 4 || digit2 == 5)
            {
                printf("MasterCard\n");
            }
    }

    if(digit1 == 4)
    {
        printf("Visa\n");
    }
}