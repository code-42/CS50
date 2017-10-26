#include <cs50.h>
#include <stdio.h>

void printSpace(int nTimes);
void printHash(int nTimes);

// Assignment pset1/mario/more
int main(void)
{
    // Get input from user
    int height;
    do
    {
        printf("Height: ");
        height = get_int();

    }
    while (height < 0 || height > 23);

    // Send spaces and hashes to print function
    for (int i = 2; i <= height+1; i++)
    {
        printSpace((height-i)+1);
        printHash(i);

        // Generate 2 half pyramids with 2 spaces between
        printf("  ");
        printHash(i);
        // printSpace((height-i)+1);
        printf("\n");
    }

}


void printSpace(int nTimes)
{
    // Print number of spaces
    for (int i = 0; i < nTimes; i++)
    {
        printf(" ");
    }
}

void printHash(int nTimes)
{
    // Print number of hashes
    for (int i = 0; i < nTimes; i++)
    {
        printf("#");
    }
}
