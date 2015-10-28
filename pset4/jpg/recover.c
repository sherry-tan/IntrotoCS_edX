/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define BLOCK 512
typedef uint8_t BYTE;


int main(void)
{
    //open input file
    FILE* card = fopen("card.raw","r");
    FILE* img = NULL;
    BYTE  buffer[512];
    char filename[8];
    int n = -1;
    
    if (card == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }
   
   
   
   while(!(feof(card)))
   {    
        //reads block of data from card
        fread(buffer, BLOCK, 1, card);
        
        //checks first 4 bytes of block for JPG signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3]==0xe0 || buffer[3]==0xe1))
        {
            //closes the current output file if one is open. 
            if (img!=NULL)
                fclose(img);
                
            //opens new file to write next image to
            n++;
            sprintf(filename, "%03d.jpg", n);
            img = fopen(filename, "w");
        }
        
        //writes block only if there is an open output file 
        if(img!=NULL && !(feof(card)))
            fwrite(buffer,BLOCK,1,img);
  
    }
    
    fclose(img);
    fclose(card);
    return 0;
}
   
   
   
   
   
   
   
