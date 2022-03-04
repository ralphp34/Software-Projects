//complete the C program
#include <stdio.h>

int main()
{
    int num;
    printf("Enter a number: \n");
    scanf("%d", &num);
    if (num <= 0)
    {
        printf("Houston, we have a problem\n");
    }

    printf("Lift off in...");
    for (int i = 0; i < num; i++)
    {
        printf("%d", num - i);
        printf("\n");

    }
        printf("\n");
        printf("        | \n");
        printf("       / \\ \n");
        printf("      / _ \\ \n");
        printf("     |.o '.| \n");
        printf("     |'._.'| \n");
        printf("     |     | \n");
        printf("   ,'|  |  |`. \n");
        printf("  /  |  |  |  \\ \n");
        printf("  |,-'--|--'-.| \n");

}