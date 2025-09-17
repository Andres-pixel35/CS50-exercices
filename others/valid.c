#include <cs50.h>
#include <stdio.h>

void valid_triangle(float a, float b, float c);

int main(void)
{
    float x = get_float("Lenght 1: ");
    float y = get_float("Lenght 2: ");
    float z = get_float("Lenght 3: ");

    valid_triangle(x, y, z);
}

void valid_triangle(float a, float b, float c)
{
    if (a <= 0 || b <= 0 || c <= 0)
    {
        printf("False.\n");
    }
    else if (a + b > c && a + c > b && b + c > a)
    {
        printf("True.\n");
    }
    else
    {
        printf("False.\n");
    }
}
