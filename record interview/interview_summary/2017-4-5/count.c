#include<stdio.h>
#include<stdlib.h>
#include<string.h>

static int totalwords = 0;
int count_Maxlength(char filename[], int len[])
{
    FILE *fp = fopen(filename, "r");
    int maxlength = 0;
    int i = 0;
    char str_arr[100];
    int length[100] = {0};
    char ch;
    if (NULL == fp)
    {
        printf("open file = %s error !\n", filename);
    }   
    ch = fgetc(fp);
    while (EOF != ch)
    {
        if (' ' != ch && '\n' != ch && '\t' != ch)
        {
            str_arr[i++] = ch;
        }
        else
        {
            str_arr[i] = '\0';
            printf("i = %d\n", i);
            printf("%s\n", str_arr);
            len[strlen(str_arr)]++;
            if (i > maxlength)
                maxlength = i;
            i = 0;
            if (ch == '\n')
                printf("\n");
            totalwords ++;
        }
        ch = fgetc(fp);
    }
    return maxlength;
}

int main()
{
    int a[100] = {0};
    int j = count_Maxlength("test_word.txt", a);
    printf("j = %d\n", j);
    printf("len\tcount\n");
    int i = 0;
    for (i = 1; i <= j; i++)
    {
        printf("%d\t%d\n", i, a[i]);
    }
    printf("totalwords = %d\n", totalwords);
    return 0;
}









