/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

// bool binarySearchRecursive(int values[], int n, int left, int mid);

/**
 * Returns true if value is in array of n values, else false.
 */
// Arguments are needle, haystack, size
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm

    // This is binary search *inspired* by hackerrank java video
    // https://www.youtube.com/watch?v=P3YID7liBug
    // and of course by this famous tweet
    // https://twitter.com/GeekyCoderr/status/928816151529959425

    // Iterative search
    int left = 0;
    int right = n - 1;
    while (left <= right)
    {
        int mid = left + ((right - left) / 2);
        // printf("33. mid == %d, left == %d, right == %d", mid, left, ((right - left) / 2));
        if (values[mid] == value)
        {
            return true;
        }
        else if (value < values[mid])
        {
            right = mid - 1;
            // printf("\n42. mid == %d, left == %d, right == %d", mid, left, ((right - left) / 2));
        }
        else if (value > values[mid])
        {
            left = mid + 1;
            // printf("\n48. mid == %d, left == %d, right == %d", mid, left, ((right - left) / 2));
        }
    }
    return false;
}


/**
 * Sorts array of n values.
 */
// values is haystack[], int is size of haystack
void sort(int values[], int n)
{
    // TODO: implement a sorting algorithm

    // Bubble sort O(n^2)
    int i, j;

    // Loop through values array
    for (i = 0; i < n - 1; i++)
    {
        // Loop through remaining elements
        for (j = 0; j < n - i - 1; j++)
        {
            // If current element is greater than the next element
            if (values[j] > values[j + 1])
            {
                // Swap elements
                int temp = values[j];
                values[j] = values[j + 1];
                values[j + 1] = temp;
            }
        }
    }
    return;
}


/*
// This is linear search O(n^2)
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    // Arguments are needle, haystack, size

    // this is linear search
    if ( n < 1 )
    {
        return false;
    }

    // Linear search
    for (int i = 0; i < n ; i++)
    {
                if (values[i] == value)
        {
            return true;
        }
    }

    return false;
}
*/

/////////////////////////////

/*
// This is Recursive Binary Search O(n)
// make Error:
// ~/workspace/cs50/pset3/find/more/ (master) $ make
// clang -ggdb3 -O0 -std=c11 -Wall -Werror -o find find.c helpers.c -lcs50 -lm
// helpers.c:59:16: error: implicit declaration of function 'binarySearchRecursive' is invalid in C99
//      [-Werror,-Wimplicit-function-declaration]
//        return binarySearchRecursive(values, n, left, mid - 1);
//               ^
// 1 error generated.
// make: *** [find] Error 1
// ~/workspace/cs50/pset3/find/more/ (master) $ make

bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    // Arguments are needle, haystack, size


    // This is binary search *inspired* by hackerrank java video
    // https://www.youtube.com/watch?v=P3YID7liBug
    // and of course by this famous tweet
    // https://twitter.com/GeekyCoderr/status/928816151529959425

    // Recursive search
    int left = 0;
    int right = n - 1;

    if (left > right)
    {
        return false;
    }

    int mid = left + ((right - left) / 2);
    if (values[mid] == n)
    {
        return true;
    }
    else if (n < values[mid])
    {
        return binarySearchRecursive(values, n, left, mid - 1);
    }
    else
    {
        return binarySearchRecursive(values, n, mid + 1, right);
    }
}
*/