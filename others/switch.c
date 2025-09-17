#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    int id;
    int PW;
    printf("Please write your id: ");
    scanf("%d", &id);

    switch (id)
    {
        case 500:
        printf("Password: ");
        scanf("%d", &PW);
        switch (PW)
        {
            case 123:
            printf("Welcome dear friend.\n");
            return 0;

            default:
            {
                printf("Wrong password.\n");
                return 0;
            }
        }
         default:
         {
            printf("Wrong ID.\n");
         }

    }
    return 0;
}
