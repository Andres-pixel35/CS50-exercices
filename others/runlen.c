#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool checkInput(char *a, int len);
int counter(char *input, int track, int len);
char *convertlowercase(char *input, int len);

// 46 because the longest word in english has 45 char and one extra for the '\0'
const int LENGTH = 46;

int main(void)
{
    char *input = malloc(LENGTH * sizeof(char));
    if (input == NULL)
    {
        printf("Could not allocate memory.\n");
        return 1;
    }

    printf("Input: ");
    scanf("%45s", input);

    int len = strlen(input);

    // checks that the input is alright to use it.

    if (checkInput(input, len) == false)
    {
        printf("Usage: Only alphabetical.\n");
        free(input);
        return 2;
    }

    // convert the word to lowercase
    convertlowercase(input, len);

    // print the char and how many times it was repeated consecutively.
    int track = 0;

    printf("[");

    do
    {
        int number = counter(input, track, len);

        track = track + number;

        printf("(\"%c\", %d)", input[track - number], number);

        if (input[track] != '\0')
        {
            printf(", ");
        }
    }
    while (input[track] != '\0');

    printf("]\n");

    free(input);

    return 0;
}

// it makes sure that the whole input isalpha
bool checkInput(char *a, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (!isalpha(a[i]))
        {
            return false;
        }
    }

    return true;
}

// Count how many characters are repeated consecutively and return the number
int counter(char *input, int track, int len)
{

    int a = 0;

    for (int i = track; i < len - 1; i++)
    {
        if (input[i] == input[i + 1])
        {
            a++;
        }

        else
        {
            break;
        }
    }

    return a + 1;
}

// turns out each char from the input to lowercase
char *convertlowercase(char *input, int len)
{

    for (int i = 0; i < len; i++)
    {
        input[i] = tolower(input[i]);
    }

    return input;
}
