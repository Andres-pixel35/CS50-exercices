#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void freeTable(void);

#define TABLE_SIZE 10
char *fail = "fail";

// Structure for a node in the linked list
typedef struct Node
{
    char *key;
    int value;
    struct Node *next;
} Node;

char *my_strdup(const char *s)
{
    char *dup = malloc(strlen(s) + 1); // Allocate memory
    if (dup == NULL)
    {
        printf("Could not allocate memory\n");
        return fail;
    }
    else
    {
        strcpy(dup, s); // Copy string
    }
    return dup;
}

// Hash table array
Node *hashTable[TABLE_SIZE];

// Hash function
unsigned int hash(char *key)
{
    unsigned int hashValue = 0;
    while (*key != '\0')
    {
        hashValue = (hashValue * 31) + *key;
        key++;
    }
    return hashValue % TABLE_SIZE;
}

// Insert key-value pair into the hash table
void insert(char *key, int value)
{
    unsigned int index = hash(key);
    Node *newNode = (malloc(sizeof(Node)));
    if (newNode == NULL)
    {
        printf("Could not allocate memory\n");
        freeTable();
        exit(2);
    }
    newNode->key = my_strdup(key);
    if (strcmp(newNode->key, fail) == 0)
    {
        freeTable();
        exit(1);
    }
    newNode->value = value;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

// Search for a value by key. If it doesn't find anything, it will return -1.
int search(char *key)
{
    unsigned int index = hash(key);
    Node *current = hashTable[index];
    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            return current->value;
        }
        current = current->next;
    }
    return -1;
}

// Free allocated memory
void freeTable(void)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        Node *current = hashTable[i];
        while (current != NULL)
        {
            Node *temp = current;
            current = current->next;
            free(temp->name);
            free(temp);
        }
    }
}

// Test the hash table
int main(void)
{
    insert("apple", 10);
    insert("banana", 20);
    insert("grape", 30);
    insert("mandarine", 2);
    insert("hello", 5);

    printf("Value for 'apple': %d\n", search("apple"));
    printf("Value for 'banana': %d\n", search("banana"));
    printf("Value for 'grape': %d\n", search("grape"));
    printf("Value for 'hello': %d\n", search("hello"));

    freeTable();
    return 0;
}
