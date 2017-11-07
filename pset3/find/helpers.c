/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    // Arguments are needle, haystack, size

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

/**
 * Sorts array of n values.
 */
 // values is haystack[], int is size of haystack
void sort(int values[], int n)
{
    // TODO: implement a sorting algorithm

    return;
}
