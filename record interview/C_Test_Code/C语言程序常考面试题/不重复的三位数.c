#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<time.h>

int main()
{
    int i,j,k;
    int h = 0;
    for(i = 1; i < 5; i++)
    {
        for (j = 1; j < 5; j++)
        {
            for (k = 1; k < 5; k++)
            {
                if (i != j && i != k && j != k)
                {
                    printf("%d %d %d\n",i,j,k);
                    h++;
                }
            }
        }
    }
    printf("h = %d\n", h);
    return 0;
}
