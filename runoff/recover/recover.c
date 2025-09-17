#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover nameofthefile.\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open the file.\n");
        return 1;
    }

    unsigned char buffer[BLOCK_SIZE];
    char filename[8];
    int count_jpg = 0;
    sprintf(filename, "%03i.jpg", count_jpg);
    FILE *output = fopen(filename, "w");
    if (output == NULL)
    {
        printf("Could not open the file.\n");
        fclose(input);
        return 1;
    }

    while (fread(buffer, BLOCK_SIZE, 1, input) >= 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            fclose(output);
            sprintf(filename, "%03i.jpg", count_jpg);
            output = fopen(filename, "w");
            count_jpg++;
            fwrite(buffer, BLOCK_SIZE, 1, output);
        }

        else
        {
            fwrite(buffer, BLOCK_SIZE, 1, output);
        }
    }
    fclose(input);
    fclose(output);
}
