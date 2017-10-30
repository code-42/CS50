#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// pset2/caesar.c
// Implement a program that encrypts messages using Caesar’s cipher
// c is computed as c[i] = (p[i] + k) % 26

// Program must accept a single argument, a non-negative integer k
int main(int argc, string argv[])
{
    if (argc != 2)
    {
        // Error message if no argument or too many arguments
        printf("Usage: ./caesar k\n");
        return 1;
    }

    // Convert string to int
    int k = atoi(argv[1]);
    // printf("%d", k);

    // Prompt user for a plaintext string
    printf("plaintext:  ");
    string p = get_string();

    printf("ciphertext: ");

    // Loop through the plaintext string
    for (int i = 0, n = strlen(p); i < n; i++)
    {
        // Check that the character is a letter
        if ((p[i] >= 'A' && p[i] <= 'Z') || (p[i] >= 'a' && p[i] <= 'z'))
        {
            // Determine if the character is uppercase
            if (p[i] >= 'A' && p[i] <= 'Z')
            {
                // Calculate ciher for uppercase letter
                printf("%c", ((p[i] + k - 'A') % 26) + 'A');
            }

            // Determine if the character is lowercase
            if (p[i] >= 'a' && p[i] <= 'z')
            {
                // Calculate ciher for lowercase letter
                printf("%c", ((p[i] + k - 'a') % 26) + 'a');
            }
        }
        else
        {
            // Print characters that are not letters
            printf("%c", p[i]);
        }
    }

    // After outputting ciphertext, you should print a newline
    printf("\n");

    // Your program should then exit by returning 0 from main
    return 0;
}
