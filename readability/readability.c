#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int num_letters(string text);
int num_words(string text);
int num_sentences(string text);

// values of the coleman-liau index
const float value1 = 0.0588;
const float value2 = 0.296;
const float value3 = 15.8;

int main(void)
{
    // keep asking to the user for a word while the input is a space or a number or is less than two words.
    string text;
    do
    {
        text = get_string("Text: ");
    }
    while (isdigit(text[0]) || num_letters(text) < 2 || isspace(text[0]));

    // take the number of each one
    float letters = num_letters(text);
    float words = num_words(text);
    float sentences = num_sentences(text);

    // it calcultes the value of the letter and sentences each 100 words
    float value_letters = (letters / words) * 100;
    float value_sentences = (sentences / words) * 100;

    int cl = round(value1 * value_letters - value2 * value_sentences - value3);

    if (cl < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (cl > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", cl);
    }
}

// calculate how many letters are in the text
int num_letters(string text)
{
    int num_letter = 0;
    int len = strlen(text);

    for (int i = 0; i < len; i++)
    {
        if (isalpha(text[i]))
        {
            num_letter++;
        }
    }
    return num_letter;
}

// calculate how many words are in the text
int num_words(string text)
{
    int num_words = 0;
    int len = strlen(text);

    for (int i = 0; i < len; i++)
    {
        if (isblank(text[i]) && isblank(text[i - 1]) == 0)
        {
            num_words++;
        }
    }
    return num_words + 1;
}

// calculate how many sentences are in the text
int num_sentences(string text)
{
    int num_sentences = 0;
    int len = strlen(text);

    for (int i = 0; i < len; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            num_sentences++;
        }
    }
    return num_sentences;
}
