#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "recover.h"

/*
Get all jpeg images from a raw file in FAT format (data is written in 512 bytes block).
Usage: ./recover [rawFilePath]
Output images are saved to an 'output' dir in the same level as the recover script.
*/
int _main(char *argv[]) {
    // read in raw file
    char *infile = argv[1];
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL) {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }

    BYTE block[512];  // each FAT block is 512 bytes
    int count = 0; // number of images found
    char outpath[15]; // string to store the output file path

    FILE *outptr;

    int nread;
    bool first = false;
    while (true) {
        nread = fread(block, 512, 1, inptr);
        // reached end of file
        if (nread == 0) {
            break;
        }
        // not the beginning of an image, writing to output file if already open image,
        // this is to discard the bytes before finding the first image
        if (block[0] != 0xff || block[1] != 0xd8 || block[2] != 0xff || (block[3] & 0xf0) != 0xe0) {
            if (first) {
                fwrite(block, 512, 1, outptr);
            }
        }
        // met a new image or first image
        else {
            count++;
            sprintf(outpath, "output/%03d.jpg", count);
            outptr = fopen(outpath, "w");
            if (outptr == NULL) {
                fprintf(stderr, "Could not open output file %s.\n", outpath);
                fclose(inptr);
                return 4;
            }
            if (!first) {
                first=true;
                
            }
            else {
                // after first image
                fclose(outptr);
            };
            fwrite(block, 512, 1, outptr);
        }
    } 
    
    fclose(outptr);
    fclose(inptr);
    return 0;
}

int main(int argc, char *argv[])
{
    return _main(argv);
}
