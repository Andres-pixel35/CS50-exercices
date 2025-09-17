#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH_NAME 50
#define MIN_NOTE 0
#define MAX_NOTE 10

typedef struct student
{
    char name[MAX_LENGTH_NAME];
    int age;
    float note;
}
student;

int is_all_letters(char *a);
float average_note(student *list, int number);

int main(void)
{
    int numberOfStudents;
    printf("How many students do you want to record? ");
    if (scanf("%d", &numberOfStudents) != 1 || numberOfStudents <= 0)
    {
        printf("You must enter a valid number of students.\n");
        return 3;
    }

    student *list = malloc(numberOfStudents * sizeof(student));
    if (list == NULL)
    {
        printf("Could not allocate memory for the student.\n");
        return 1;
    }

    FILE *students = fopen("students.txt", "w");
    if (students == NULL)
    {
        printf("Could not open the file.\n");
        free(list);
        return 4;
    }

    for (int i = 0; i < numberOfStudents; i++)
    {
        printf("Name: ");
        scanf(" %50[^\n]", list[i].name);

        if (strlen(list[i].name) > MAX_LENGTH_NAME || strlen(list[i].name) == 0)
        {
            printf("The name must be between 1 and 50 words.\n");
            fclose(students);
            free(list);
            return 3;
        }
        else if (!is_all_letters(list[i].name))
        {
            printf("The name must only contain letter.\n");
            fclose(students);
            free(list);
            return 3;
        }

        printf("Age: ");
        if (scanf("%d", &list[i].age) != 1 || list[i].age < 0)
        {
            printf("You must enter a valid age.\n");
            fclose(students);
            free(list);
            return 3;
        }

        printf("Note: ");
        if (scanf("%f", &list[i].note) != 1 || list[i].note < MIN_NOTE || list[i].note > MAX_NOTE)
        {
            printf("The note must be between 0.0 and 10.0.\n");
            fclose(students);
            free(list);
            return 3;
        }

        fprintf(students, "Student number %d:\nName: %s.\nAge: %d.\nNote: %.1f.\n", i + 1,
                list[i].name, list[i].age, list[i].note);

        while (getchar() != '\n');
    }

    float averageNote = average_note(list, numberOfStudents);

    for (int i = 0; i < numberOfStudents; i++)
    {
        printf("%s is %d years old and has a note of %.1f.\n", list[i].name, list[i].age,
               list[i].note);
    }

    printf("And the average note of the students is: %.1f.\n", averageNote);

    fclose(students);
    free(list);
    return 0;
}

int is_all_letters(char *a)
{
    for (int i = 0; a[i] != '\0'; i++)
    {
        if (!isalpha(a[i]) && a[i] != ' ')
        {
            return 0;
        }
    }

    return 1;
}

float average_note(student *list, int number)
{
    float track = 0;

    for (int i = 0; i < number; i++)
    {
        track = list[i].note + track;
    }

    float average = track / number;

    return average;
}
