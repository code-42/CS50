/**
 * recover.c
 *
 * find JPEGs in file card.raw
 *
 * Usage: ./recover card.raw
 */

#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
        // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: recover card.raw\n");
        return 1;
    }

    // assign filename to char*
    char *infile = argv[1];
    // char *buffer;
    int fileLen;

    printf("22. inputs are: %s\n", infile);

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    fseek(inptr, 0, SEEK_END);
    fileLen = ftell(inptr);
    printf("%d\n", fileLen);
    fseek(inptr, 0, SEEK_SET);

    // buffer = (char *)malloc(fileLen+1);
    BYTE buffer[512];

    // initialize jpg variables
    int increment = 0;
    char outfilename[8];

    // fread(buffer, fileLen, 1, inptr);
    // fread(buffer, 1, 512, inptr);
    int j = 0, k = 0, l = 0, m = 0, n = 0;
    while(fread(buffer, 512, 1, inptr) != 0)
    {   j++;
        if(inptr != NULL)
        {   k++;

            for (int i = 1; i < 512; i++){
                if ((buffer[i] == 0xd9) && (buffer[i-1] == 0xff)){
                    printf("found 0xffd9 @ byte %d in fread %d\n", i, k);
                }
            }

            if (buffer[0] == 0xff &&
                buffer[1] == 0xd8 &&
                buffer[2] == 0xff &&
                (buffer[3] == 0xe1 || buffer[3] == 0xe0))
                {
                    l++;
                    sprintf(outfilename, "%.3d.jpg", increment++);

                    // open new file
                    FILE* outptr;
                    outptr = fopen(outfilename, "a");

                    // write first block of 512 bytes, then read next block
                    fwrite(buffer, 512, 1, outptr);

                    if(fread(buffer, 512, 1, inptr) == 0)
                    {
                        m++;
                        break;
                    }


                    // copy all information from inpointer to buffer to jpg
                    while ((buffer[0] != 0xff  &&
                            buffer[1] != 0xd8  &&
                            buffer[2] != 0xff &&
                            (buffer[3] != 0xe1 && buffer[3] != 0xe0)))
                            {
                                n++;
                                // if next byte is NULL break
                                if(fread(buffer, 512, 1, inptr) == 0)
                                    break;

                                fread(buffer, 512, 1, inptr);

                                //copies jpg file 1 byte at a time
                                fwrite(buffer, 512, 1, outptr);
                                // printf("%s ", buffer);

                            }

                            fclose(outptr);
                }
        }
    }
    printf("j = %d\nk = %d\nl = %d\nm = %d\nn = %d\n", n, n, n, n, n);

    fclose(inptr);

    // free(buffer);

}

