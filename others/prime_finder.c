#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// the number must be greater than 1
#define MIN_VALUE 1

#define BUFFER_SIZE 11 // 10 character for the number + \0.

// this is the first prime that will be print in each number
#define FIRST_PRIME 2

bool all_numbers(char input[]);
bool is_prime(int number, int *total);

int main(void)
{
    // how the input must be
    printf(
        "Usage: You must write an integer greater than 1 without spaces nor letters in base 10.\n");

    // I'll use a char [] because I want to check out that the input is an integer
    char buffer[BUFFER_SIZE];

    int number = 0;

    // loop of the input while the user writes nonsense
    do
    {
        do
        {
            printf("Number: ");
            scanf("%10s", buffer);

            if (!all_numbers(buffer))
            {
                printf("The input must be an integer.\n");
            }
        }
        while (!all_numbers(buffer));

        number = atoi(buffer);

        if (number <= MIN_VALUE)
        {
            printf("The number must be greater than %d.\n", MIN_VALUE);
        }
    }
    while (number <= MIN_VALUE);

    printf("Prime numbers between %d and %d:", MIN_VALUE, number);

    int totalPrimes = 0;
    bool first = true;

    // here each number between 1 and the input pass through the function and
    // prints every prime number
    for (int i = FIRST_PRIME; i <= number; i++)
    {
        if (is_prime(i, &totalPrimes))
        {
            if (!first)
            {
                printf(",");
            }
            printf(" %d", i);
            first = false;
        }
    }

    printf(".\n");

    printf("The amount of prime numbers between %d and %d is: %d\n", MIN_VALUE, number,
           totalPrimes);

    return 0;
}

// this function checks whether the input is an integer or not.
bool all_numbers(char input[])
{
    int len = strlen(input);

    for (int i = 0; i < len; i++)
    {
        if (!isdigit(input[i]))
        {
            return false;
        }
    }
    return true;
}

// this function will check the number to verify whether is a prime number or not.
// the function will return the true it is a prime number
// otherwise it will return false
// the algorithm used is trial division using 6k ± 1 optimisation
// and it will keep track of how many primes are with total.
bool is_prime(int number, int *total)
{
    if (number <= 3)
    {
        *total = *total + 1;
        return true;
    }

    if (number % 2 == 0 || number % 3 == 0)
    {
        return false;
    }

    for (int i = 5; i * i <= number; i += 6)
    {
        if (number % i == 0 || number % (i + 2) == 0)
        {
            return false;
        }
    }

    *total = *total + 1;
    return true;
}
