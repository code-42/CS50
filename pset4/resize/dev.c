/**
 * Copies a BMP piece by piece, just because.
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./copy n infile outfile\n");
        return 1;
    }

    int n = atoi(argv[1]);

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    printf("42. inputs are: %d, %s, %s\n", n, infile, outfile);

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    printf("52. header of %s \n\n", infile);

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

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // bf.bfSize = bf.bfSize * n;
    // bi.biSize = bi.biSize * n;
    bi.biWidth = bi.biWidth * n;
    printf("80. bi.biWidth == %d\n", bi.biWidth);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    // for each row
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        // for each pixel in row
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write to outfile horizontally n times
            for(int z = 0; z < n; z++)
            {
                if(triple.rgbtRed == 0xFF){
                    // tripleR++;
                    triple.rgbtRed = 0x00;
                }

                if(triple.rgbtGreen == 0x00){
                    // tripleG++;
                    triple.rgbtGreen = 0xff;
                }

                if(triple.rgbtBlue == 0x00){
                    // tripleG++;
                    triple.rgbtBlue = 0xaa;
                }

                // video @ 8.27
                char ch;
                while((ch = fgetc(inptr)) != EOF)
                    printf("%c", ch);

                // write RGB triple to outfile
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
        }

        // temporary storage
        RGBTRIPLE triple;

        // write to outfile vertically n times
        for(int y = 0; y < n; y++)
        {
            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    printf("\n153. header after fwrite to %s \n", outfile);
    // printf("42. inputs are: %d, %s, %s\n", n, infile, outfile);

    printf("117. bf.bfType == %i\n", bf.bfType);
    printf("118. bf.bfSize == %i\n", bf.bfSize);
    printf("119. bf.bfOffBits == %i\n", bf.bfOffBits);
    printf("120. bi.biSize == %i\n", bi.biSize);
    printf("121. bi.biWidth == %i\n", bi.biWidth);
    // bi.biWith * 3 = xxd -c columns
    printf("122. bi.biHeight == %i\n", bi.biHeight);
    printf("123. bi.biPlanes == %i\n", bi.biPlanes);
    printf("124. bi.biBitCount == %i\n", bi.biBitCount);
    printf("125. bi.biCompression == %i\n", bi.biCompression);
    printf("126. bi.biSizeImage == %i\n", bi.biSizeImage);
    printf("127. bi.biXPelsPerMeter == %i\n", bi.biXPelsPerMeter);
    printf("128. bi.biYPelsPerMeter == %i\n", bi.biYPelsPerMeter);
    printf("129. bi.biClrUsed == %i\n", bi.biClrUsed);
    printf("130. bi.biClrImportant == %i\n", bi.biClrImportant);

                // // video @ 8.27
                // char ch;
                // while((ch = fgetc(inptr)) != EOF)
                //     printf("%c", ch);

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
