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
        printf("Usage: ./vigenere key\n");
        return 1;
    }

    // Assign key to k
    string k = argv[1];

    // Prompt user for a plaintext string
    printf("plaintext:  ");
    string p = get_string();

    // Array of alphabet characters
    // for (int i = 65; i < 65 + 26; i++)
    // {
    //     printf("%c is %i\n", (char) i, i-65);
    // }

    // Get the length of p and k for loops
    int lenP = strlen(p);
    int lenK = strlen(k);

    printf("ciphertext: ");

    // Loop through the plaintext string
    for (int i = 0; i < lenP; i++)
    {
        // Determine that the character in p is an Uppercase letter
        if (p[i] >= 'A' && p[i] <= 'Z')
        {
            // Calculate ciher for uppercase letter
            printf("%c", (char)((int)p[i]-65 + (int)k[i%lenK]-65) % 26 + 65);
        }

        // Determine if the character is lowercase
        if (p[i] >= 'a' && p[i] <= 'z')
        {
            // Calculate ciher for lowercase letter
            printf("%c", (char)((int)p[i]-97 + (int)k[i%lenK]-97) % 26 + 97);
        }
    }

    // After outputting ciphertext, you should print a newline
    printf("\n");

    // Your program should then exit by returning 0 from main
    return 0;
}
