#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countdigits(long n);
int luhnalgorithm(char a[]);

int main(void)
{
    long input;
    printf("Number: ");
    scanf("%ld", &input);

    if (countdigits(input) < 13 || countdigits(input) > 16)
    {
        printf("INVALID\n");
        return 0;
    }

    char str[countdigits(input) + 1];
    sprintf(str, "%ld", input);

    int check = luhnalgorithm(str);

    if ((check % 10) == 0)
    {
        if (str[0] == '3')
        {
            if ((str[1] == '4' || str[1] == '7') && strlen(str) == 15)
            {
                printf("AMEX\n");
                return 0;
            }
            else
            {
                printf("INVALID\n");
                return 0;
            }
        }

        else if (str[0] == '5')
        {
            if ((str[1] == '1' || str[1] == '2' || str[1] == '3' || str[1] == '4' || str[1] == '5') && strlen(str) == 16)
            {
                printf("MASTERCARD\n");
                return 0;
            }
            else
            {
                printf("INVALID\n");
                return 0;
            }
        }

        else if (str[0] == '4')
        {
            if (strlen(str) == 13 || strlen(str) == 16)
            {
                printf("VISA\n");
                return 0;
            }
            else
            {
                printf("INVALID\n");
                return 0;
            }
        }
    }
    else
    {
        printf("INVALID\n");
        return 0;
    }
}

int countdigits(long n)
{

    int count = 0;
    do
    {
        long division = n / 10;
        count++;
        n = division;
    }
    while (n != 0);

    return count;
}

int luhnalgorithm(char a[])
{
    int len = strlen(a);

    int sum = 0;

    for (int i = len - 2; i >= 0; i = i - 2)
    {
        int n = (a[i] - '0') * 2;

        if (n > 9)
        {
            int h = n / 10;
            int j = (n % 10);

            sum = sum + (h + j);
        }

        else
        {
            sum = sum + n;
        }
    }

    for (int i = len - 1; i >= 0; i = i - 2)
    {
        int l = (a[i] - '0');

        sum = sum + l;
    }

    return sum;
}
