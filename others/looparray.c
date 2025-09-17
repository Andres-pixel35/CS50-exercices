#include <stdio.h>

int main(void)
{
    int values[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (int i = 0; i < 20; i++)
    {
        int indice = i % 10;
        printf("Values[%i] = %i\n", indice, values[indice]);
    }
}
