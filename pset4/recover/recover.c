/**
 * recover.c
 *
 * find JPEGs in card.raw
 *
 * Usage: ./recover card.raw
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


int main(int argc, char *argv[])
{
    // program should accept one command-line argument - name of  file to recover
    if (argc != 2)
    {
        fprintf(stderr, "Usage: recover card.raw\n");
        return 1;
    }

    // assign filename to char*
    char *infile = argv[1];

    // open input file
    FILE *inptr = fopen(infile, "r");

    // check if something went wrong
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // struct to contain bytes from fread
    uint8_t buffer[512];

    // initialize jpg variables
    int fileNum = 0;
    char filename[8];
    FILE *img = NULL;

    // repeat until end of file card.raw
    // read 512 bytes into buffer
    while (fread(buffer, 512, 1, inptr) != 0)
    {
        // set a flag
        bool SOF = false;

        // look for jpg signature in header
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // found jpg signature in header
            SOF = true;
        }

        if (SOF)
        {
            // close previous output file when next jpg found
            if (img)
            {
                fclose(img);
            }

            // sprintf writes an empty file then increments filename number
            sprintf(filename, "%03i.jpg", fileNum++);

            // open the img file for writing
            img = fopen(filename, "w");

            // check if something went wrong
            if (img == NULL)
            {
                fprintf(stderr, "Could not open %s.\n", filename);
                return 2;
            }

            // write 512 byte until new jpg is found
            fwrite(buffer, 512, 1, img);
        }
        else
        {
            // continue writing next buffer if img file is still open
            if (img != NULL)
            {
                fwrite(buffer, 512, 1, img);
            }
        }
    }

    // close any open files before exit
    if (img)
    {
        fclose(img);
    }

    if (inptr)
    {
        fclose(inptr);
    }
    return 0;
}
