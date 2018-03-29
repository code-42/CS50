# Questions

## What's `stdint.h`?

Defines new integer types because older basic integer types deemed insufficient for new environments.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

uint8_t is an unsigned char with a max value of 255
uint32_t
int32_t
uint16_t is an unsigned short equal to 2 bytes (16 bits) with a max value of 65535

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

BYTE
DWORD
LONG
WORD

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

424d

## What's the difference between `bfSize` and `biSize`?

bfSize is for BITMAPFILEHEADER at offset 2
biSize is for BITMAPINFOHEADER at offset 14

## What does it mean if `biHeight` is negative?

If biHeight is negative, the bitmap is a top-down DIB and its origin is the upper-left corner.
source https://msdn.microsoft.com/en-us/library/dd183376(v=vs.85).aspx

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitcount at offset 28

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

Usage: ./copy infile outfile and argc must equal 3

## Why is the third argument to `fread` always `1` in our code?

If the third argument is 1, fread will read 1 data element which is sizeof(BITMAPFILEHEADER) or 14 bytes long.

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

0000 or 1 byte

## What does `fseek` do?

TODO

## What is `SEEK_CUR`?

TODO