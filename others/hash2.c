#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <wctype.h>
#include <time.h>
#include <ctype.h>

void freeTable(void);
int calculateAge(int a, int b, int c);
void printTable(void);

#define TABLE_SIZE 10
#define HASH_MULTIPLIER 31

typedef struct node
{
    char *name;
    int age;
    char *sex;
    struct node *next;
}
node;

void check(node *(*search_fun)(char *), char *a);

// it duplicates the name and the sex in order to don't change it in its address.
char *my_dup(const char *s)
{
    if (s == NULL)
    {
        return NULL;
    }

    char *dup = malloc(strlen(s) + 1);
    if (dup == NULL)
    {
        printf("Could not allocate memory for dup\n");
        return NULL;
    }
    else
    {
        strcpy(dup, s);
    }
    return dup;
}

// create a hashtable
node *hashtable[TABLE_SIZE];

// it gives to the name an unique index to store at the hashtable.
unsigned int hash(char *name)
{
    unsigned int hashvalue = 0;
    while (*name != '\0')
    {
        hashvalue = (hashvalue * HASH_MULTIPLIER) + towlower(*name);
        name++;
    }
    return hashvalue % TABLE_SIZE;
}

// stores the information from the user to the hashtable and
// in case of colition it creates a linked list to handle it.
int insert(char *name, int age, char *sex)
{
    unsigned int index = hash(name);
    node *newnode = malloc(sizeof(node));
    if (newnode == NULL)
    {
        printf("Could not allocate memory for the newnode\n");
        return 23;
    }
    newnode->name = my_dup(name);
    if (newnode->name == NULL)
    {
        return 23;
    }
    newnode->age = age;

    newnode->sex = my_dup(sex);
    if (newnode->sex == NULL)
    {
        free(newnode->name);
        free(newnode);
        return 23;
    }
    newnode->next = hashtable[index];
    hashtable[index] = newnode;
    return 0;
}

// search by the name either the user write the name in lowercase or uppercase.
// and handle when colition searching through all the linked list.
node *search(char *name)
{
    unsigned int index = hash(name);
    node *current = hashtable[index];
    while (current != NULL)
    {
        if (strcasecmp(current->name, name) == 0)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// free the memory allocate.
void freeTable(void)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        node *current = hashtable[i];
        while (current != NULL)
        {
            node *tmp = current;
            current = current->next;
            free(tmp->name);
            free(tmp->sex);
            free(tmp);
        }
    }
}

int main(void)
{
    // the enough memory for a single name
    char *name = malloc(21 * sizeof(char));
    if (name == NULL)
    {
        printf("Could not allocate memory for name.\n");
        return 1;
    }
    int day, month, year;
    // enough memory for male or female with the '\0'
    char *sex = malloc(10 * sizeof(char));
    if (sex == NULL)
    {
        printf("Could not allocate memory for sex.\n");
        free(name);
        return 2;
    }

    // iterates over and over to fullfil the hashtable. it should be TABLE_SIZE intead of 1
    // but when checking it's better just one time to don't get tired
    for (int i = 0; i < 1; i++)
    {
        printf("Name: ");
        scanf("%20s", name);

        printf("Enter your birth date (DD/MM/YYYY): ");
        scanf("%d %d %d", &day, &month, &year);

        printf("Sex: ");
        scanf("%9s", sex);

        if(insert(name, (calculateAge(day, month, year)), sex) == 23)
        {
            freeTable();
            free(sex);
            free(name);
            return 3;
        }
    }

    check(search, "andres");

    printTable();

    freeTable();
    free(name);
    free(sex);

    return 0;
}

// it takes the data gave before and calculate the age. it return the actual age to the current day.
int calculateAge(int a, int b, int c)
{
    int current_day, current_month, current_year;

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    current_day = tm.tm_mday;
    current_month = tm.tm_mon + 1;
    current_year = tm.tm_year + 1900;

    int age = current_year - c;

    if (b > current_month || (b == current_month && a > current_day))
    {
        age--;
    }

    return age;
}

//print all the hashtable with all the data store
void printTable(void)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        printf("Index %d: ", i);
        node *current = hashtable[i];

        if (current == NULL)
        {
            printf("Empty\n");
        }
        else
        {
            while (current != NULL)
            {
                printf("-> [Name: %s, Age: %d, Sex: %s] ", current->name, current->age, current->sex);
                current = current->next;
            }
            printf("\n");
        }
    }
}

void check(node *(*search_fun)(char *), char *a)
{
    node *tem = search_fun(a);
    if (tem != NULL)
    {
        printf("Name: %s, age: %d, sex: %s.\n", tem->name, tem->age, tem->sex);
    }
    else
    {
        printf("Person not found.\n");
    }
}
