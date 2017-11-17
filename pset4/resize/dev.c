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

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    printf("62. sizeof(BITMAPFILEHEADER) == %li\n", sizeof(BITMAPFILEHEADER));
    printf("63. sizeof(BITMAPINFOHEADER) == %li\n", sizeof(BITMAPINFOHEADER));
    printf("64. sizeof(RGBTRIPLE) == %li\n", sizeof(RGBTRIPLE));

    printf("52. header of %s \n\n", infile);
    printf("48. bf.bfType == %i\n", bf.bfType);
    printf("49. bf.bfSize == %i\n", bf.bfSize);
    printf("50. bf.bfOffBits == %i\n", bf.bfOffBits);
    printf("51. bi.biSize == %i\n", bi.biSize);
    printf("52. bi.biWidth == %i\n", bi.biWidth);
    printf("53. bi.biHeight == %i\n", bi.biHeight);
    printf("55. bi.biBitCount == %i\n", bi.biBitCount);
    printf("57. bi.biSizeImage == %i\n", bi.biSizeImage);

    // determine padding for scanlines
    int originalPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    printf("81. originalPadding == %i\n", originalPadding);

    // change original to infile after dev
    long originalBiWidth = bi.biWidth;
    printf("87. bi.originalBiWidth == %li\n", originalBiWidth);
    // long originalBiHeight = bi.biHeight;

    bi.biWidth = bi.biWidth * n;
    printf("87. bi.biWidth == %d\n", bi.biWidth);

    bi.biHeight = bi.biHeight * n;
    printf("90. bi.biHeight == %d\n", bi.biHeight);

    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    printf("96. padding == %i\n", padding);


    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + padding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    // for each row
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // printf("108. i loop %d\n", i);
      // iterate over pixels in scanline
        //   write to outfile vertically n times
        for(int y = 0; y < n; y++)
        {
            printf("113. y loop %d\n", y);
        // for each pixel in row
            for (int j = 0; j < bi.biWidth; j++)
            {
                // printf("112. j loop %d\n", j);
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write to outfile horizontally n times
                for(int x = 0; x < n; x++)
                {
                    printf("127. x loop %d\n", x);
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // then add it back (to demonstrate how)
            // for (int k = 0; k < padding; k++)
            // {
            //     fputc(0x00, outptr);
            // }

            fseek(inptr, (originalBiWidth * sizeof(RGBTRIPLE)), SEEK_CUR);
        }

        // skip over padding, if any
        fseek(inptr, originalBiWidth * sizeof(RGBTRIPLE) + originalPadding, SEEK_CUR);
    }
    printf("\n176. header after fwrite to %s \n", outfile);
    // printf("42. inputs are: %d, %s, %s\n", n, infile, outfile);

    printf("179. bf.bfType == %i\n", bf.bfType);
    printf("180. bf.bfSize == %i\n", bf.bfSize);
    printf("181. bf.bfOffBits == %i\n", bf.bfOffBits);
    printf("182. bi.biSize == %i\n", bi.biSize);
    printf("1873. bi.biWidth == %i\n", bi.biWidth);
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
