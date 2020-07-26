//recovers JPEGs from a forensic image

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK_SIZE 512
#define FILE_NAME_SIZE 8
#define TRUE 1
#define FALSE 0


typedef uint8_t BYTE; 

char new_jpeg(BYTE buffer[]);

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        fprintf(stderr, "missing command-line argument\n");
        return 1;
    }

    else if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 2;
    }

    char *infile = *(argv + 1);
    FILE *inptr = fopen(infile, "r"); //arv[1]
    if (!inptr) //file==NULL
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 3;
    }

    // Read first three bytes
    BYTE buffer[BLOCK_SIZE];

    char file_count = 0;
    char first_jpeg_found = FALSE;
    FILE *outptr = NULL;
    while (fread(buffer, BLOCK_SIZE, 1, inptr))
    {
        //Check first four bytes
        if (new_jpeg(buffer))
        {
            if (!first_jpeg_found)
            {
                first_jpeg_found = TRUE;
            }
            else
            {
                fclose(outptr);
            }

            char outfile[FILE_NAME_SIZE];
            sprintf(outfile, "%03i.jpg", file_count++);
            outptr = fopen(outfile, "w");
            
            if (!outptr) //file==NULL
            {
                fclose(outptr);
                fprintf(stderr, "Could not open %s.\n", outfile);
                return 5;
            }
            fwrite(buffer, BLOCK_SIZE, 1, outptr);
        }
        
        else
        {
            if (first_jpeg_found)
            {
                fwrite(buffer, BLOCK_SIZE, 1, outptr);
            }

        }
        
    }
    
    fclose(outptr);
    fclose(inptr);


}

char new_jpeg(BYTE buffer[])
{
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xF0) == 0xE0)
    {    
        return TRUE;
    }
    return FALSE;
}
