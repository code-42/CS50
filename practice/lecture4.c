// compilation of all simple programs in lecture 4

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void swapValue(int a, int b);
void swapPointer(int *a, int *b);
void compareValue(void);
void comparePointer(void);
void copyValue(void);
int copyPointer(void);

int main(void)
{
    int x = 1;
    int y = 2;

    printf("swapValue in x is %i, y is %i\n", x, y);
    swapValue(x, y);
    printf("swapValue out x is %i, y is %i\n", x, y);

    // x = 1;
    // y = 2;
    printf("swapPointer in x is %i \n", x);
    printf("swapPointer in y is %i \n", y);
    printf("swapping %i and %i \n", x, y);
    swapPointer(&x, &y);
    printf("swapPointer out x is now %i \n", x);
    printf("swapPointer out y is now %i \n", y);

    compareValue();
    comparePointer();

    copyValue();
    copyPointer();
}

void swapValue(int a, int b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

void swapPointer(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void compareValue(void){

    // get two strings
    string s = get_string("compareValue s: ");
    string t = get_string("compareValue t: ");

    // compare strings' addresses
    if (s == t)
    {
        printf("same\n");
    }
    else
    {
        printf("different\n");
    }
}

void comparePointer(void){

    // get two strings
    char *s = get_string("comparePointer s: ");
    char *t = get_string("comparePointer t: ");

    // compare strings for equality
    if (strcmp(s, t) == 0)
    {
        printf("same\n");
    }
    else
    {
        printf("different\n");
    }
}

void copyValue(void){
        // get a string
    string s = get_string("copyValue s: ");

    // copy string's address
    string t = s;

    // capitalize first letter in string
    if (strlen(t) > 0)
    {
        t[0] = toupper(t[0]);
    }

    // print string twice
    printf("copyValue s: %s\n", s);
    printf("copyValue t: %s\n", t);

}

int copyPointer(void){

    // get a string
    char *s = get_string("copyPointer s: ");
    if (!s)
    {
        return 1;
    }

    // allocate memory for another string
    char *t = malloc((strlen(s) + 1) * sizeof(char));
    if (!t)
    {
        return 1;
    }

    // copy string into memory
    for (int i = 0, n = strlen(s); i <= n; i++)
    {
        t[i] = s[i];
    }

    // capitalize first letter in copy
    if (strlen(t) > 0)
    {
        t[0] = toupper(t[0]);
    }

    // print strings
    printf("copyPointer s: %s\n", s);
    printf("copyPointer t: %s\n", t);

    // free memory
    free(t);
    return 0;
}