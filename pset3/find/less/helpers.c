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
    // When passing an array to a function, you have to pass in its size separately

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

    // Need to implement binary search
    // Recursion will help but not required
    return false;
}

/**
 * Sorts array of n values.
 */
// values is haystack[], int is size of haystack
// When passing an array to a function, you have to pass in its size separately
// void sort(int values[], int n)
// {
//     // TODO: implement a sorting algorithm
//     // Bubble sort
//     int i, j;
//     // Loop through values array
//     for (i = 0; i < n - 1; i++)
//     {
//         // Loop through remaining elements
//         for (j = 0; j < n - i - 1; j++)
//         {
//             // If current element is greater than the next element
//             if (values[j] > values[j + 1])
//             {
//                 // Swap elements
//                 int temp = values[j];
//                 values[j] = values[j + 1];
//                 values[j + 1] = temp;
//             }
//         }
//     }
//     return;
// }


void sort(int values[], int n)
{
  int swapCounter;
  int i;

  do
  {
      swapCounter = 0;
      for(i = 0; i < n - 1; i++)
      {
          if (values[i] > values[i + 1])
          {
            int temp = values[i];
            values[i] = values[i + 1];
            values[i + 1] = temp;
            swapCounter = 1;
          }

      }
  }
  while(swapCounter != 0);

  return;
}

// void sort(int values[], int n)
// {
//     // TODO: implement a sorting algorithm
//     // Bubble sort
//     int i, j;
//     // Loop through values array
//     for (i = 0; i < n; i++)
//     {
//         // Loop through remaining elements
//         for (j = 0; j < n - 1; j++)
//         {
//             // If current element is greater than the next element
//             if (values[j] > values[j + 1])
//             {
//                 // Swap elements
//                 int temp = values[j +  1];
//                 values[j + 1] = values[j];
//                 values[j] = temp;
//             }
//         }
//     }
//     return;
// }
