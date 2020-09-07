#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: resize n infile outfile\n");
        return 1;
    }

    int n = atoi(argv[1]);

    char *infile = argv[2];
    char *outfile = argv[3];

    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL) {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL) {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0) {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    int oldWidth = bi.biWidth;
    int oldHeight = bi.biHeight;
    int newWidth = oldWidth * n;
    int newHeight = oldHeight * n;

    int inPadding = (4 - (oldWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int outPadding = (4 - (newWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi.biHeight = newHeight;
    bi.biWidth = newWidth;
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * newWidth) + outPadding) * abs(newHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    RGBTRIPLE scanline[newWidth * sizeof(RGBTRIPLE)];

    for (int i = 0, biHeight = abs(oldHeight); i < biHeight; i++) {
        for (int j = 0; j < oldWidth; j++) {
            RGBTRIPLE triple;

            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            for (int k = 0; k < n; k++) {
                scanline[(j * n) + k] = triple;
            }
        }

        fseek(inptr, inPadding, SEEK_CUR);

        for (int j = 0; j < n; j++) {
            fwrite(scanline, sizeof(RGBTRIPLE), newWidth, outptr);

            for (int k = 0; k < outPadding; k++) {
                fputc(0x00, outptr);
            }
        }
    }

    fclose(inptr);
    fclose(outptr);
    return 0;
}