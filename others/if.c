#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    int ID;
    printf("Please write your ID: ");
    scanf("%d", &ID);

    if (ID == 500)
    {
        int PW;
        printf("Write your password: ");
        scanf("%d", &PW);
        if (PW == 123)
        {
            printf("Welcome master.\n");
        }
        else
        {
            printf("Wrong password.\n");
        }
    }
     else
     {
        printf("Wrong ID.\n");
     }
     return 0;
}
