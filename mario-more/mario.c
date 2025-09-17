#include <cs50.h>
#include <stdio.h>

void print_empty(int space);
void print_row(int bricks);
void print_top(int top);

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // print_top(height);
    // printf("\n");

    for (int i = 0, a = height; i < height && a > 0; i++, a--)
    {
        print_empty(a - 1);
        print_row(i + 1);
        printf("  ");
        print_row(i + 1);
        printf("\n");
    }
}

void print_row(int bricks)
{
    for (int i = 0; i < bricks; i++)
    {
        printf("#");
    }
}

void print_empty(int space)
{
    for (int a = space; a > 0; a--)
    {
        printf(" ");
    }
}

// void print_top(int top)
// {
   // for (int t = 0; t < top; t++)
    //{
    //    printf(" ");
    //}
    //printf("#");
//}
