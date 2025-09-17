#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node* next;
}
node;

void freelist(node* head)
{
    node* current = head;
    while (current != NULL)
    {
        node* tmp = current;
        current = current->next;
        free(tmp);
    }
}

node* createnode(int data)
{
    node* newNode = malloc(sizeof(node));
    if (newNode == NULL)
    {
        printf("Could not allocate memory\n");
        return NULL;
    }
     newNode->data = data;
     newNode->next = NULL;
     return newNode;
}

void printlist(node* head)
{
    node* current = head;
    while (current != NULL)
    {
        printf("%d\n", current->data);
        current = current->next;
    }
}


int main(int argc, char* argv[])
{
    node* head = NULL;
    node* tail = NULL;

    if (argc != 4)
    {
        printf("Usage: ./linked2 value1 value2 value3\n");
        return 1;
    }

    for (int a = 1; a < argc; a++)
    {
        char* endptr;
        strtol(argv[a], &endptr, 10);

        if (*endptr != '\0')
        {
            printf("Must use only integers.\n");
            return 2;
        }
    }


    for (int i = 1; i < argc; i++)
    {
        node* newNode = createnode(atoi(argv[i]));

        if (newNode == NULL)
        {
            freelist(head);
            return 3;
        }

        else if (head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }

    printlist(head);
    freelist(head);

    return 0;
}

