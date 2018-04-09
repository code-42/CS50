/**
 * recover.c
 *
 * find JPEGs in file card.raw
 *
 * Usage: ./recover card.raw
 *
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

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // buffer = (char *)malloc(fileLen+1);
    BYTE buffer[512];
    // uint8_t buffer[512];

    // initialize jpg variables
    int fileNum = 0;
    char filename[8];

    // int fileLen = 0;
    // int *pfileLen = NULL;

    int k = 0; //, l = 0, m = 0, n = 0, startBlock = 0, endBlock = 0, bytesLong = 0;
    // int sf = 0, ef = 0;

    // repeat until end of file card.raw
    // read 512 bytes into buffer

    long block = 0;
    while(fread(buffer, 512, 1, inptr) != 0)
    {
        eprintf("block %ld == %d \n",block, k);
        _Bool sof = false;

        // set fseek to beginning of current 512k block
        // fseek(inptr, block, SEEK_SET);

        for (int i = 1; i < 511; i++){
            // look for SOF signature in header
            if (buffer[i-1] == 0xff &&
                buffer[i] == 0xd8 &&
                buffer[i+1] == 0xff &&
                (buffer[i+2] >= 0xe0 && buffer[i+2] <= 0xef))
            {
                sof = true;
                eprintf("found 0x%0x%0x%0x%0x @ byte %d in block %d\n", buffer[0], buffer[1], buffer[2], buffer[3], i-1, k);
            }

            if (sof)
            {
                fseek(inptr, block, SEEK_SET);

                eprintf("block %ld == %d ",block, k);
                // eprintf(" %d \n",i);

                sprintf(filename, "%03i.jpg", fileNum++);
                eprintf("%s \n",filename);

                FILE *img = fopen(filename, "w");

                while (fread(buffer, 512, 1, inptr) != 0)
                {
                    fwrite(buffer, 512, 1, img);

                    block++;

                    fseek(inptr, block, SEEK_SET);

                    // if next file signature is detected
                    if (buffer[i-1] == 0xff &&
                        buffer[i] == 0xd8 &&
                        buffer[i+1] == 0xff &&
                        (buffer[i+2] == 0xe1 || buffer[i+2] == 0xe0))
                    {
                        block--;
                        break;
                    }
                    fseek(inptr, block, SEEK_SET);
                }
                fileNum++;
                fclose(img);
            }
        }
        block++;
        k++;
    }
    fclose(inptr);
    return 0;
}
