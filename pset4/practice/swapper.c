#include <stdio.h>

// ref= https://docs.cs50.net/2016/fall/notes/4/week4.html
// Pointers

void swap(int *a, int *b);

int main(void)
{
    int x = 1;
    int y = 2;
    printf("x is %i \n", x);
    printf("y is %i \n", y);
    printf("swapping %i and %i \n", x, y);
    swap(&x, &y);
    printf("x is now %i \n", x);
    printf("y is now %i \n", y);
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}