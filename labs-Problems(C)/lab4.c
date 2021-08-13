#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;
typedef uint16_t BBYTE;
//typedef uint16_t == 2*BYTE


const int HEADER = 44;


int main(int argc, char *inpu[])
{
    float mult = atof(inpu[3]);
    if (argc != 4)
    {
        return 1;
    }
    FILE *file0 = fopen(inpu[1], "r");
    FILE *file = fopen(inpu[2], "w");
    if(file0 == NULL || file == NULL)
    {
        return 1;
    }
    BYTE header[HEADER];

    fread(header, HEADER, 1, file0);
    fwrite(header, HEADER, 1, file);
    
    BBYTE endf;
    
    while(fread(&endf, sizeof(BBYTE), 1, file0))
    {
        endf *= mult;
        fwrite(&endf, sizeof(BBYTE), 1, file);
    }
    
    fclose(file0);
    fclose(file);
    }
