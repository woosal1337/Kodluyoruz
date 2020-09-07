#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"


int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: copy infile outfile\n");
        return 1;
    }

    char *infile = argv[1];
    char *outfile = argv[2];

    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL) {
        printf("Could not open %s.\n", infile);
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

    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++) {
        for (int j = 0; j < bi.biWidth; j++) {
            RGBTRIPLE triple;

            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            if (triple.rgbtRed == 0xff)
                triple.rgbtRed = 0x00;
            if (triple.rgbtBlue == 0xff)
                triple.rgbtBlue = 0x00;
            if (triple.rgbtGreen == 0xff)
                triple.rgbtGreen = 0x00;

            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        fseek(inptr, padding, SEEK_CUR);

        for (int k = 0; k < padding; k++)
            fputc(0x00, outptr);
    }

    fclose(inptr);
    fclose(outptr);
    return 0;
}