/**
 * Copies a BMP piece by piece, just because.
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./copy infile \n");
        return 1;
    }

    char *infile = argv[1];


    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    printf("48. bf.bfType == %i\n", bf.bfType);
    printf("49. bf.bfSize == %i\n", bf.bfSize);
    printf("50. bf.bfOffBits == %i\n", bf.bfOffBits);
    printf("51. bi.biSize == %i\n", bi.biSize);
    printf("52. bi.biWidth == %i\n", bi.biWidth);
    printf("53. bi.biHeight == %i\n", bi.biHeight);
    printf("54. bi.biPlanes == %i\n", bi.biPlanes);
    printf("55. bi.biBitCount == %i\n", bi.biBitCount);
    printf("56. bi.biCompression == %i\n", bi.biCompression);
    printf("57. bi.biSizeImage == %i\n", bi.biSizeImage);
    printf("58. bi.biXPelsPerMeter == %i\n", bi.biXPelsPerMeter);
    printf("59. bi.biYPelsPerMeter == %i\n", bi.biYPelsPerMeter);
    printf("60. bi.biClrUsed == %i\n", bi.biClrUsed);
    printf("61. bi.biClrImportant == %i\n", bi.biClrImportant);

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    printf("64. padding == %i\n", padding);

    // iterate over infile's scanlines
    // for each row

    int blueCount = 0;
    int greenCount = 0;
    int redCount = 0;

    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        // for each pixel in row
        for (int j = 0; j < bi.biWidth; j++)
        {
            RGBTRIPLE triple;

            if(triple.rgbtBlue == 0xFF)
                blueCount++;

            if(triple.rgbtGreen == 0xFF)
                greenCount++;

            if(triple.rgbtRed == 0xFF)
                redCount++;


            // print to screen single characters read from file
            // https://youtu.be/QOD2hHiHpn0?t=497
            // char ch;
            // while((ch = fgetc(inptr)) != EOF)
            //     printf("ch == %c", ch);

            printf("%i ", bi.biWidth);
            // temporary storage


            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // printf("\n");
            // printf("%i", *triple);
        }
        printf("\n");
    }

    printf("110. rgbBlue %i\n", blueCount);
    printf("111. rgbGreen %i\n", greenCount);
    printf("112. rgbRed %i\n", redCount);

    // video @ 8.27
    char ch;
    while((ch = fgetc(inptr)) != EOF)
        printf("%c", ch);

    // close infile
    fclose(inptr);

    // success
    return 0;
}
