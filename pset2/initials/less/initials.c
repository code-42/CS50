#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Assignment pset2/initials/less
int main(void)
{
    // Get input from user
    string name;
    do
    {
        printf("Please enter your name: ");
        name = get_string();
    }

    while (strlen(name) < 1);

    printf("%s\n",name);
}
