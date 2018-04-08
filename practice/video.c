#include <stdio.h>
#include <stdlib.h>

// my interpretation of CS50 pointers video
// https://youtu.be/yOdd3uYC--A?t=1751

int video(int n);

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("usage: ./video n\n");
        return 1;
    }

    int n = atoi(argv[1]);
    video(n);

}

int video(int k)
{
    printf("26. k == %d\n", k);

    // declare a pointer
    int* pk;

    // assign the address of k to pk
    pk = &k;
    printf("29. pk == %d\n", *pk);

    // assign the value 35 to the place pk points to
    *pk = 35;

    // declare a variable m
    int m;
    m = 4;
    printf("33. m == %d\n", m);

    // assign the address of m to the pointer pk
    // pk now points to the address of m which holds the value 4
    pk = &m;
    printf("35. pk == %d\n", *pk);

    return 0;
}