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

void convertToBit(void* pBuffer, size_t length);

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
    char *buffer;
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

    buffer = (char *)malloc(fileLen+1);
    fread(buffer, fileLen, 1, inptr);
    fclose(inptr);

    // convertToBit(&buffer, fileLen);
    free(buffer);

}

void convertToBit(void* pBuffer, size_t length)
{
    FILE* pOutput = fopen("file.txt", "w");
    for (size_t i=0; i < length; ++i)
    {
        unsigned char byte = (unsigned char)&pBuffer[i];
        for (int bitIndex=0; bitIndex < 8; ++bitIndex)
        {
            if ((byte & (1 << bitIndex)) != 0)
                fputs("1", pOutput);
            else
                fputs("0", pOutput);

            // fputs("\n", pOutput);
        }
    }

    fclose(pOutput);
}

/*
source https://stackoverflow.com/questions/10531884/write-a-jpg-image-file-in-c
segmentation fault

// convert buffer data to bits and write them to a text file
void convertToBit(void *buffer, int length)
{
    int c=0;
    int SIZE = length * 8;
    unsigned char bits[SIZE + 1];
    unsigned char mask = 1;
    unsigned char byte ;
    int i = 0;
    FILE *bitWRT = fopen("file.txt", "w");

    for (c=0;c<length;c++)
    {
        byte = ((char *)&buffer)[c];

        for(i = 0; i < 8; i++){
            bits[i] = (byte >> i) & mask;
            fprintf(bitWRT, "%d\n", bits[i]);
        }
    }
    fclose(bitWRT);
}
*/