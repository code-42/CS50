/**
 * recover.c
 *
 * find JPEGs in file card.raw
 *
 * Usage: ./recover card.raw
 *
 * help from https://stackoverflow.com/questions/25594775
 */

#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
// #include <stdbool.h>
#include "bmp.h"

// void convertToBit(void* pBuffer, size_t length);

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
    // BYTE buffer[512];
    uint8_t buffer[512];

    // initialize jpg variables
    int fileNum = 0;
    char filename[8];

    // fread(buffer, fileLen, 1, inptr);
    // fread(buffer, 1, 512, inptr);
    int k = 0, l = 0, m = 0, n = 0, startBlock = 0, endBlock = 0, bytesLong = 0;
    int sf = 0, ef = 0;

    FILE* img = NULL;

    while(fread(buffer, 512, 1, inptr) != 0)
    {

        sf = 0;
        ef = 0;
        // loop through each block of 512 bytes
        for (int i = 1; i < 512; i++){
            // SOF signature
            if (buffer[i-1] == 0xff &&
                buffer[i] == 0xd8 &&
                buffer[i+1] == 0xff &&
                (buffer[i+2] == 0xe1 || buffer[i+2] == 0xe0))
            {
                sf = 1;
                printf("\n%d. found 0x%0x%0x%0x%0x @ byte %d in block %d ", l, buffer[0], buffer[1], buffer[2], buffer[3], i-1, k);
                startBlock = k;
                sprintf(filename, "%03i.jpg", fileNum++);
                l++;

                // open new file
                // FILE* img = NULL;
                img = fopen(filename, "a");

                // write first block of 512 bytes
                fwrite(buffer, 512, 1, img);
                // fclose(img);
                sf = 0;

                fseek(img, 0, SEEK_END);
                fileLen = ftell(img);
                printf("%d\n", fileLen);
                fseek(img, 0, SEEK_SET);
                break;


            if(sf == 0 && fileLen > 0){

                // open new file
                // img = fopen(filename, "a");

                // write next block of 512 bytes
                fwrite(buffer, 512, 1, img);
                // fclose(img);
                break;
            }

                if ((buffer[i] == 0xd9) && (buffer[i-1] == 0xff)){
                    ef = 1;
                    endBlock = k;
                    bytesLong = ((endBlock-startBlock)*512) - (512-i);
                    printf("and found 0x%0x%0x @ byte %d in block %d and is ~ %d bytesLong\n", buffer[i-1], buffer[i], i, k, bytesLong);
                    // fclose(img);
                    break;
                }
            } else {
                break;
            }
        }
        k++;
    }

/*
            if (buffer[0] == 0xff &&
                buffer[1] == 0xd8 &&
                buffer[2] == 0xff &&
                (buffer[3] == 0xe1 || buffer[3] == 0xe0))
            {
                // printf("found 0x%0x%0x%0x%0x @ byte %d in block %d ", buffer[0], buffer[1], buffer[2], buffer[3], i, k);
                // sprintf(filename, "%.3d.jpg", increment++);
                sprintf(filename, "%03i.jpg", increment++);
                // printf("%d filename = %s ", l, filename);
                l++;

                // open new file
                FILE* img = fopen(filename, "w");

                // write first block of 512 bytes, then read next block
                fwrite(buffer, 512, 1, img);

                if(fread(buffer, 512, 1, inptr) == 0)
                {
                    m++;
                    printf("96. %s ", "she's gonna break!");
                    break;
                }


                //
                while ((buffer[0] != 0xff  &&
                        buffer[1] != 0xd8  &&
                        buffer[2] != 0xff &&
                        (buffer[3] != 0xe1 && buffer[3] != 0xe0)))
                {
                    n++;
                    // if next byte is NULL break
                    if(fread(buffer, 512, 1, inptr) == 0){
                        printf("109. %s ", "she's gonna break!");
                        break;
                    }

                    fread(buffer, 512, 1, inptr);

                    //copies jpg file 1 byte at a time
                    fwrite(buffer, 512, 1, img);
                    // printf("%s ", buffer);

                }

                fclose(img);
            }
            */



    printf("\nk = %d\nl = %d\nm = %d\nn = %d\n", k, l, m, n);

    fclose(inptr);

    // free(buffer);
    return 0;

}
