#include<stdio.h>
#include<stdlib.h>
#include<string.h>

static int totalwords = 0;

int judge_add(char pre, char cur)
{
    int flag = 0;
    /*
    if (pre == ' ')
    {
        if (cur != '\n' && cur != '\t')
        {
            flag = 1;
        }
    }
    else if (pre == '\n')
    {
        if (cur != ' ' && cur != '\t')
        {
            flag = 1;
        }
    }
    else if (pre == '\t')
    {
        if (cur != '\n' && cur != ' ')
        {
            flag = 1;
        }
    }
    else if (cur == ' ')
    {
        if (pre != '\t' && pre != '\n')
        {
            flag = 1;
        }
    }
    else if (cur == '\n')
    {
        if (pre != '\t' && pre != ' ')
        {
            flag = 1;
        }
    }
    else if (cur == '\t')
    {
        if (pre != ' ' && pre != '\n')
        {
            flag = 1;
        }
    }*/
    if ((pre == ' ' || pre == '\t') && (cur == ' ' || cur == '\t'))
    {
        flag = 1;
    }
    return flag;
}

int count_Maxlength(char filename[], int len[])
{
    FILE *fp = fopen(filename, "r");
    int maxlength = 0;
    int i = 0;
    char str_arr[100];
    int length[100] = {0};
    char ch;
    char pre_ch, cur_ch;
    if (NULL == fp)
    {
        printf("open file = %s error !\n", filename);
        exit(0);
    }   
    cur_ch = fgetc(fp);
    while (EOF != cur_ch)
    {
        if (' ' != cur_ch && '\n' != cur_ch && '\t' != cur_ch)
        {
            str_arr[i++] = cur_ch;
        }
        else
        {
            str_arr[i] = '\0';
            printf("i = %d\n", i);
            printf("%s\n", str_arr);
            len[strlen(str_arr)]++;
            if (pre_ch != cur_ch )
            {   
                if (!judge_add(pre_ch, cur_ch))
                {
                    printf("pre_ch = %c, cur_ch = %c\n", pre_ch, cur_ch);
                    totalwords ++;
                    printf("totalwords = %d\n", totalwords);
                }
            }
            if (i > maxlength)
                maxlength = i;
            i = 0;
            if (ch == '\n')
                printf("\n");
        }
        pre_ch = cur_ch;
        cur_ch = fgetc(fp);
    }
    return maxlength;
}
/*
int new_count_Maxlength(char filename[], int len[])
{
    FILE *fp = fopen(filename, "r");
    int maxlength = 0;
    int i = 0;
    char str_arr[100];
    int length[100] = {0};
    char ch;
    char pre_ch, cur_ch;
    int flag = 0;
    if (NULL == fp)
    {
        printf("open file = %s error !\n", filename);
        exit(0);
    }   
    cur_ch = fgetc(fp);
    while (EOF != cur_ch)
    {
        if (' ' == cur_ch || '\n' == cur_ch || '\t' == cur_ch)
        {
            flag = 0;
            str_arr[i] = '\0';
            printf("i = %d\n", i);
            printf("%s\n", str_arr);
            if (i > maxlength)
                maxlength = j;
            i = 0;
        }
        else
        {
            str_arr[i++] = cur_ch;
            flag = 1;
            
        }
        pre_ch = cur_ch;
        cur_ch = fgetc(fp);
    }
    return maxlength;
}
*/

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






