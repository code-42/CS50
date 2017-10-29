#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Assignment pset2/initials/more
int main(void)
{
    // Get input from user
    string name = get_string();

    // Sanity check if user input something
    if (name != NULL)
    {
        // Print the first character in Uppercase if it is a letter
        if ((name[0] >= 'A' && name[0] <= 'Z') || (name[0] >= 'a' && name[0] <= 'z'))
        {
            printf("%c", toupper(name[0]));
        }

        // Loop through each character after checking the first letter
        for (int i = 1, n = strlen(name); i < n; i++)
        {
            // If the character is a space, continue to next iteration
            if (name[i] == (char)' ')
            {
                continue;
            }

            // Print the first letter after a space
            if (name[i - 1] == (char)' ')
            {
                printf("%c", toupper(name[i]));
            }
        }
    }
    printf("\n");
}
