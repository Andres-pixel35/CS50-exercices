#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wctype.h>

bool isalphabetic(char *a);
bool isunique(char *a);
char swap(char input, char *key);

const int LENGTH = 26;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    else if (strlen(argv[1]) != LENGTH)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    else if (isalphabetic(argv[1]) == false)
    {
        printf("Key must be only letters.\n");
        return 1;
    }

    else if (isunique(argv[1]) == false)
    {
        printf("The key must include all the alphabetic letters.\n");
        return 1;
    }

    string plaintext = get_string("Plaintext: ");
    int len = strlen(plaintext);
    char ciphertext[len + 1];

    for (int i = 0; i < len; i++)
    {
        ciphertext[i] = swap(plaintext[i], argv[1]);
    }
    ciphertext[len] = '\0';

    printf("ciphertext: %s\n", ciphertext);
}

bool isalphabetic(char *a)
{
    for (int i = 0; i < LENGTH; i++)
    {
        if (isalpha(a[i]) == 0)
        {
            return false;
        }
    }

    return true;
}

bool isunique(char *a)
{
    int letters[LENGTH] = {0};
    int index;

    for (int i = 0; i < LENGTH; i++)
    {
        index = tolower(a[i]) - 'a';

        if (letters[index] != 0)
        {
            return false;
        }

        letters[index] = 1;
    }

    return true;
}

char swap(char input, char *key)
{
    int index;

    if (isupper(input))
    {
        index = input - 'A';

        return toupper(key[index]);
    }

    else if (islower(input))
    {
        index = input - 'a';

        return tolower(key[index]);
    }

    else
    {
        return input;
    }
}
