#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Definir ssize_t si no está disponible
#ifndef _SSIZE_T_DEFINED
typedef long ssize_t;
#define _SSIZE_T_DEFINED
#endif

// Implementación manual de `getline()`
ssize_t my_getline(char **lineptr, size_t *n, FILE *stream)
{
    if (*lineptr == NULL || *n == 0)
    {
        *n = 128; // Tamaño inicial del buffer
        *lineptr = malloc(*n);
        if (*lineptr == NULL)
        {
            return -1; // Error al asignar memoria
        }
    }

    size_t i = 0;
    int c;

    while ((c = fgetc(stream)) != EOF && c != '\n')
    {
        if (i >= *n - 1)
        {
            *n *= 2; // Duplicar el tamaño del buffer
            char *temp = realloc(*lineptr, *n);
            if (temp == NULL)
            {
                return -1; // Error de memoria
            }
            *lineptr = temp;
        }
        (*lineptr)[i++] = c;
    }

    if (c == EOF && i == 0)
    {
        return -1; // Fin del archivo sin leer nada
    }

    (*lineptr)[i] = '\0';
    return i;
}

// Función que verifica si la línea contiene "NL" en mayúsculas, pero no "nl" en minúsculas
int contains_NL_only(const char *line)
{
    int found_NL = 0;
    for (size_t i = 0; line[i] != '\0'; i++)
    {
        if (line[i] == 'N' && line[i + 1] == 'L')
        {
            found_NL = 1; // Encontró "NL" en mayúsculas
        }
        else if (line[i] == 'n' && line[i + 1] == 'l')
        {
            return 0; // Encontró "nl" en minúsculas, descartar la línea
        }
    }
    return found_NL;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: ./searcher <file> <word>\n");
        return 1;
    }

    char *word = argv[2];
    int check_NL = (strcmp(word, "NL") == 0); // Bandera para activar la lógica especial de "NL"

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open the file.\n");
        return 2;
    }

    FILE *output = fopen(word, "w");
    if (output == NULL)
    {
        printf("Could not create output file.\n");
        fclose(file);
        return 4;
    }

    char *buffer = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = my_getline(&buffer, &len, file)) != -1)
    {
        if (check_NL)
        {
            if (contains_NL_only(buffer))
            {
                fprintf(output, "%s\n", buffer);
            }
        }
        else
        {
            if (strstr(buffer, word) != NULL)
            {
                fprintf(output, "%s\n", buffer);
            }
        }
    }

    fclose(file);
    fclose(output);
    free(buffer);

    printf("Search complete. Results saved in file: %s\n", word);
    return 0;
}
