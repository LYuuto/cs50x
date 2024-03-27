#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //check arg
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    FILE* input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open the file\n");
        return 1;
    }

    //storing read data
    BYTE buffer[512];

    //output file
    FILE* img = NULL;

    //to name the output
    int imagecount = 0;
    char* filename = malloc(8 * sizeof(char));

    while (fread(&buffer, 512, 1, input))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //create file name
            sprintf(filename, "%03i.jpg", imagecount);

            //making file with names
            img = fopen(filename, "w");
            imagecount++;
        }

        //fwrite if the img pointer has a name
        if (img != NULL)
        {
            fwrite(&buffer, 512, 1, img);
        }
    }

    free(filename);
    fclose(input);
    fclose(img);
}