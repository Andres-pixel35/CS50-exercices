#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool digits_only(string s);
char rotate(char a, int b);
// only accepts 1 input and it have to be a integer, not couting the first that is ./caesar
int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else if (digits_only(argv[1]) == false)
    {
        printf("Usage: ./caesar key\n");
        return 2;
    }
    else if (digits_only(argv[1]) == true)
    {
        int key = atoi(argv[1]);
        string plaintext = get_string("plaintext: ");
        int lenght = strlen(plaintext);
        char ciphertext[lenght + 1];
        for (int i = 0; i < lenght; i++)
        {
            ciphertext[i] = rotate(plaintext[i], key);
        }
        ciphertext[lenght] = '\0';
        printf("ciphertext: %s\n", ciphertext);
    }
}
// make sure that the string have only digits
bool digits_only(string s)
{
    int lenght = strlen(s);
    for (int i = 0; i < lenght; i++)
    {
        if (isdigit(s[i]) == 0)
        {
            return false;
        }
    }
    return true;
}
// rotate the char b times
char rotate(char a, int b)
{
    char c;
    if (isupper(a))
    {
        c = ((a - 'A' + b) % 26) + 'A';
    }
    else if (islower(a))
    {
        c = ((a - 'a' + b) % 26) + 'a';
    }
    else
    {
        c = a;
    }
    return c;
}
