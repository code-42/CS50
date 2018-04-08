/**
 * Copies a BMP piece by piece, just because.
 */

#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

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

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    printf("44. header of %s \n\n", infile);
    printf("45. sizeof(BITMAPFILEHEADER) == %li\n", sizeof(BITMAPFILEHEADER));
    printf("46. sizeof(BITMAPINFOHEADER) == %li\n", sizeof(BITMAPINFOHEADER));
    printf("47. sizeof(RGBTRIPLE) == %li\n", sizeof(RGBTRIPLE));

    printf("48. bf.bfType == %i\n", bf.bfType);
    printf("49. bf.bfSize == %i\n", bf.bfSize);
    printf("50. bf.bfOffBits == %i\n", bf.bfOffBits);
    printf("51. bi.biSize == %i\n", bi.biSize);
    printf("52. bi.biWidth == %i\n", bi.biWidth);
    printf("53. bi.biHeight == %i\n", bi.biHeight);
    printf("55. bi.biBitCount == %i\n", bi.biBitCount);
    printf("57. bi.biSizeImage == %i\n", bi.biSizeImage);

    // determine padding for scanlines
    int original_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    printf("81. padding == %i\n", original_padding);

    // original biWidth and biHeight
    long original_biWidth = bi.biWidth;
    long original_biHeight = bi.biHeight;

    // change original to infile after dev
    // long biWidth = bi.biWidth;
    // printf("87. bi.biWidth == %li\n", biWidth);

    bi.biWidth = bi.biWidth * n;
    printf("87. bi.biWidth * n == %d\n", bi.biWidth);

    bi.biHeight = bi.biHeight * n;
    printf("90. bi.biHeight * n == %d\n", bi.biHeight);

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    // printf("96. padding == %i\n", padding);

    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + padding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = labs(original_biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < original_biWidth; j++)
        {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                for (int k = 0; k < n; k++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }

        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    printf("\n176. header after fwrite to %s \n", outfile);
    // printf("42. inputs are: %d, %s, %s\n", n, infile, outfile);

    printf("179. bf.bfType == %i\n", bf.bfType);
    printf("180. bf.bfSize == %i\n", bf.bfSize);
    printf("181. bf.bfOffBits == %i\n", bf.bfOffBits);
    printf("182. bi.biSize == %i\n", bi.biSize);
    printf("183. bi.biWidth == %i\n", bi.biWidth);
    // xxd -c columns == bi.biWith * 3 bytes
    printf("185. bi.biHeight == %i\n", bi.biHeight);
    printf("186. bi.biBitCount == %i\n", bi.biBitCount);
    printf("187. bi.biSizeImage == %i\n", bi.biSizeImage);

    // calculate padding for scanlines
    padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    printf("191. padding == %i\n", padding);


    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}