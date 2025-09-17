// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <wctype.h>

#include "dictionary.h"

int createNode(const char *buffer);

#define HASH_MULTIPLIER 101
unsigned int size_count = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Choose number of buckets in hash table
const unsigned int N = 101;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int index = hash(word);
    node *current = table[index];

    while (current != NULL)
    {
        if (strcasecmp(current->word, word) == 0)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hashvalue = 0;

    while (*word != '\0')
    {
        hashvalue = (hashvalue * HASH_MULTIPLIER) + towlower(*word);
        word++;
    }

    return hashvalue % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        printf("Could not open the file\n");
        unload();
        return false;
    }

    char buffer[LENGTH + 1];
    while (fscanf(source, "%s", buffer) != EOF)
    {
        if (createNode(buffer) == 23)
        {
            fclose(source);
            unload();
            return false;
        }
        size_count++;
    }

    fclose(source);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int size = size_count;
    if (size == 0)
    {
        return 0;
    }
    return size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *current = table[i];
        while (current != NULL)
        {
            node *tmp = current;
            current = current->next;
            free(tmp);
        }
    }
    return true;
}

// it stores each work into the table
int createNode(const char *buffer)
{
    unsigned int index = hash(buffer);
    node *newnode = malloc(sizeof(node));
    if (newnode == NULL)
    {
        printf("Could not allocate memory for new node.\n");
        return 23;
    }
    strcpy(newnode->word, buffer);
    newnode->next = table[index];
    table[index] = newnode;

    return 0;
}
