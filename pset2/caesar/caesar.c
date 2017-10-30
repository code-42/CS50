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
    for (int i = 0, n = strlen(p); i < n; i++)
    {
        if ((p[i] >= 'A' && p[i] <= 'Z') || (p[i] >= 'a' && p[i] <= 'z'))
        {
            if (p[i] >= 'A' && p[i] <= 'Z')
            {
                //
                printf("%c", ((p[i] + k - 'A') % 26) + 'A');
            }

            if (p[i] >= 'a' && p[i] <= 'z')
            {
                //
                printf("%c", ((p[i] + k - 'a') % 26) + 'a');
            }
        }
        else
        {
            printf("%c", p[i]);
        }
    }

    printf("\n");
    return 0;
}
