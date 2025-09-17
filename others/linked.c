#include <stdio.h>
#include <stdlib.h>

// Definición de la estructura del nodo
typedef struct Node
{
    int data;
    struct Node *next;
}
Node;

// Función para crear un nuevo nodo
Node *createNode(int data)
{
    Node *newNode = (malloc(sizeof(Node)));
    if (newNode == NULL)
    {
        printf("Could not alocate memory\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Función para imprimir la lista enlazada
void printList(Node *head)
{
    Node *current = head;
    while (current != NULL)
    {
        printf("%d \n", current->data);
        current = current->next;
    }
}

// Función para liberar la memoria de la lista enlazada
void freeList(Node *head)
{
    Node *current = head;
    while (current != NULL)
    {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

int main()
{
    Node *head = NULL;
    Node *tail = NULL;

    // Crear lista enlazada del 1 al 10
    for (int i = 1; i <= 20; i++)
    {
        Node *newNode = createNode(i);
        if (head == NULL)
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

    // Imprimir la lista
    printList(head);

    // Liberar memoria
    freeList(head);

    return 0;
}
