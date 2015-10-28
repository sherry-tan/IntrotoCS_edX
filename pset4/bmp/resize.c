/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resizes BMP
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"


int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    
    // remember filenames
    int n = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];

    if (n < 1 || n >100) 
    {
        printf("Usage: Enter n between 1 and 100");
        return 1;
    }

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
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
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // computes width and height of enlarged image and saves width and height of original image in 2 variables
    int inheight = abs(bi.biHeight);
    int inwidth = bi.biWidth;
    bi.biWidth = bi.biWidth * n ;
    bi.biHeight = bi.biHeight * n ;
    
    // determine padding for scanline and enlarged image
    int padding =  (4 - (inwidth  * sizeof(RGBTRIPLE)) % 4) % 4;
    int outpadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    //calculates size of image and file of outfile
    bf.bfSize = bi.biWidth*abs(bi.biHeight)*sizeof(RGBTRIPLE) + (outpadding*abs(bi.biHeight)) + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);  
    bi.biSizeImage = bf.bfSize - sizeof(BITMAPINFOHEADER) - sizeof(BITMAPFILEHEADER);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0; i < inheight; i++)
       
    {
        //loop to write infile scanline, i, to n lines in the outfile to magnify it
        for(int x = 0; x < n; x++)
        {   
            // iterate over pixels in scanline i
            for (int j = 0; j < inwidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
    
                // write RGB triple to outfile
                for (int k = 0 ; k < n; k++)
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
            
            //add padding to output file
            for (int k = 0; k < outpadding; k++)
                fputc(0x00, outptr);
               
            fseek(inptr, -(inwidth*sizeof(RGBTRIPLE)), SEEK_CUR);
            
        } 
        
        // skip over padding, if any
        fseek(inptr, padding + (inwidth*sizeof(RGBTRIPLE)) , SEEK_CUR);

        
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);
  
    // that's all folks
    return 0;
}
