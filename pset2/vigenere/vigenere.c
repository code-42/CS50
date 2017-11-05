#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// pset2/vigenere.c
// Implement a program that encrypts messages using Vigenère’s cipher:
// If p is some plain text and k is a keyword (i.e., an alphbetical string,
// whereby A represents 0, B represents 1, C represents 2, …, and Z represents 25),
// then each letter, ci, in the ciphertext, c, is computed as c[i] = (p[i] + k[j]) % 26

// Program must accept a single command-line argument: a keyword, k,
// composed entirely of alphabetical characters
int main(int argc, string argv[])
{
    if (argc != 2)
    {
        // Error message if no argument or too many arguments
        printf("Usage: ./vigenere key\n");
        return 1;
    }

    // Assign argv[1] to k
    string k = argv[1];

    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!((k[i] >= 'A' && k[i] <= 'Z') || (k[i] >= 'a' && k[i] <= 'z')))
        {
            // Error message if key is not alphabetical characters
            printf("Usage: ./vigenere key must be alphabetical characters\n");
            return 1;
        }
    }

    // Prompt user for a plaintext string
    printf("plaintext:  ");
    string p = get_string();

    // variable k is for key
    // variable p is for plaintext

    // Get the length of p and key for loops
    int lenP = strlen(p);
    int lenK = strlen(k);

    // Output will go after ciphertext:
    printf("ciphertext: ");

    // Loop through the plaintext string
    for (int i = 0, j = 0; i < lenP; i++)
    {
        // Make the key character look like its from zero-based array
        int upperK = toupper(k[j]);

        // Determine that the character in p is an Uppercase letter
        if (p[i] >= 'A' && p[i] <= 'Z')
        {
            // Calculate ciher for uppercase letter
            printf("%c", (char)(((int)p[i] - 65 + upperK - 65) % 26) + 65);

            // Increment the index of key
            j++;

            // Loop around to the first letter of key
            j = j % lenK;
        }

        // // Determine if the character is lowercase
        else if (p[i] >= 'a' && p[i] <= 'z')
        {
            // Calculate ciher for lowercase letter
            printf("%c", (char)(((int)p[i] - 97 + upperK - 65) % 26) + 97);

            // Increment the index of key
            j++;

            // Loop around to the first letter of key
            j = j % lenK;
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
