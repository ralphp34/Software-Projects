//complete the C program
#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE * stream = fopen("input.txt", "w");

    if ((fopen("input.txt", "r")) == NULL)
    {
        fprintf(stderr, "ERROR: cannot open file\n");
    }
    
    fclose(stream);

    while (1)
    {
        int i;
        float f;
        int res = scanf("%d", &i);
        float res1 = scanf("%f", &f);
        if (res == 0)
        {
            printf("ERROR: Invalid input\n");
        }

        if (res1 == 0)
        {
            printf("ERROR: Invalid input\n");
        }

        if (i >= 3 && f < 3)
        {
            printf("i:%d f:%f i*f %f", i,f,(f*i));
        }
        else
        {
            printf("i:%d f:%d i*f %d", i,(int)f,(int)(f*i));
        }
    }
}