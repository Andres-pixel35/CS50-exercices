#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    srandom(time(0));

    int x = random();
    int x2 = random();
    int x3 = random();

    char *word = "Resultados";

    FILE *output = fopen(word, "a");
    if (output == NULL)
    {
        printf("Could not create the file\n");
        return 1;
    }

    fprintf(output, "%i\n", x);
    fprintf(output, "%i\n", x2);
    fprintf(output, "%i\n", x3);

    fclose(output);

    return 0;
}
