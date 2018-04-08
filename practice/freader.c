#include <stdio.h>
#include <stdlib.h>

// int main(int argc, char *argv[])
int main()
{

    FILE* in = fopen("in.txt", "r");

    if (in == NULL)
    {
        printf("File does not exist.\n");
        return 1;
    }

    FILE* out = fopen("out.txt", "a");

    char ptr[5];

    while(fread(ptr, 5, 1, in) == 1)
    {
        fwrite(ptr, 5, 1, out);
    }

    fclose(in);
    fclose(out);

}