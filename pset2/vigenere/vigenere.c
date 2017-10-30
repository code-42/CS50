#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// pset2/vigenere.c
// Implement a program that encrypts messages using Vigenère’s cipher:
// If p is some plaintext and k is a keyword (i.e., an alphbetical string,
// whereby A represents 0, B represents 1, C represents 2, …, and Z represents 25),
// then each letter, ci, in the ciphertext, c, is computed as c[i] = (p[i] + k[j]) % 26

// Program must accept a single command-line argument: a keyword, k,
// composed entirely of alphabetical characters
int main(int argc, string argv[])
{
    if (argc != 2)
    {
        // Error message if no argument or too many arguments
        printf("Usage: ./vigenere k\n");
        return 1;
    }

    // Assign key to k
    string k = argv[1];

    // Prompt user for a plaintext string
    printf("plaintext:  ");
    string p = get_string();

    printf("ciphertext: ");

    // Loop through the plaintext string
    for (int i = 0, n = strlen(p); i < n; i++)
    {
        // Check that the character in p is a letter
        if ((p[i] >= 'A' && p[i] <= 'Z') || (p[i] >= 'a' && p[i] <= 'z'))
        {

            for (int j = 0, l = strlen(k); j < l; j++)
            {
                 // Determine if the character is uppercase
                if (p[i] >= 'A' && p[i] <= 'Z')
                {
                    // Calculate ciher for uppercase letter
                    printf("%c", ((p[i] + k[j] - 'A') % 26) + 'A');

                }

                // Determine if the character is lowercase
                if (p[i] >= 'a' && p[i] <= 'z')
                {
                    // Calculate ciher for lowercase letter
                    printf("%c", ((p[i] + k[j] - 'a') % 26) + 'a');
                }
                break;
            }
        }
        else
        {
            // Print characters that are not letters
            printf("%c", p[i]);
        }
        continue;
    }

    // After outputting ciphertext, you should print a newline
    printf("\n");

    // Your program should then exit by returning 0 from main
    return 0;
}
