#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#define LENGTH 46

char *reverse(char *a);

int main(void)
{
    char *word = malloc(LENGTH * sizeof(char));
    if (word == NULL)
    {
        printf("Could not allocate memory.\n");
        return 1;
    }

    printf("Word: ");
    scanf("%s", word);

    if (strlen(word) > LENGTH - 1)
    {
        printf("The max length is 45\n");
        return 2;
    }

    char *backwards = reverse(word);

    if (backwards == NULL)
    {
        free(word);
        return 3;
    }

    else if (strcasecmp(backwards, word) == 0)
    {
        printf("The word: %s/%s is a palindrome.\n", word, backwards);
    }
    else
    {
        printf("The word: %s/%s is not a palindrome.\n", word, backwards);
    }

    free(backwards);
    free(word);
    return 0;
}

char *reverse(char *a)
{
    char *newWord = malloc(LENGTH * sizeof(char));
    if (newWord == NULL)
    {
        printf("Could not allocate memory.\n");
        return NULL;
    }

    int len = strlen(a);

    strcpy(newWord, a);

    for (int i = 0; i < len/2; i++)
    {
        char tmp = newWord[i];
        newWord[i] = newWord[len - i - 1];
        newWord[len - i - 1] = tmp;
    }

    return newWord;
}
