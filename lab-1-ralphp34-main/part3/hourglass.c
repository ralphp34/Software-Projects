//complete this program
//complete this program
#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("$ ./hourglass\n");
    int n;
    printf("Enter a number: \n");
    scanf("%d", &n);

    if (n % 2 == 0)
    {
        int count1 = n;
        for (int i = 0; i < n/2; i++)
        {
            for (int j = 0; j < i; j++)
            {
                printf(" ");
            }
            for (int j = 0; j < count1; j++)
            {
                printf("*");
            }
            printf("\n");
            count1 = count1 - 2;
        }
        int count2 = 2;
        for (int i = 0; i < n/2; i++)
        {
            for (int j = 0; j < (n/2) - 1 - i; j++)
            {
                printf(" ");
            }
            for (int j = 0; j < count2; j++)
            {
                printf("*");
            }
            printf("\n");
            count2 = count2 + 2; 
        }
    }

    else 
    {
        int b = n;
        for (int i = 0; i < (n/2); i++)
        {
            for (int j = 0; j < i; j++)
            {
                printf(" ");
            }
            for (int j =0 ; j < b; j++)
            {
                printf("*");
            }
            printf("\n");
            b = b - 2;
        }

        for (int i = 0; i < n/2; i++)
        {
            printf(" ");
        }
        printf("*\n");

        int c = 2;
        for (int i = 0; i < n/2; i++)
        {
            for (int j = 0; j < (n/2)- 1 - i; j++)
            {
                printf(" ");
            }
            for (int j = 0; j < c; j++)
            {
                printf("*");
            }
            printf("*\n");
            c = c + 2;
        }
    }

}
