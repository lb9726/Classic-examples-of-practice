#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#define MAXNUM 569
#define MAXNUM 3
void fileAppend(const char *srcFilename, const char *destFilename)
{
    FILE *srcFp = fopen(srcFilename, "rb");
    FILE *destFp = fopen(destFilename, "ab");
    char str;
    if (NULL == srcFp)
    {
        printf("open file %s error\n", srcFilename);
        exit(1);
    }
    if (NULL == destFp)
    {
        printf("open file %s error\n", destFilename);
        exit(1);
    }
    while(1)
    {
        str = fgetc(srcFp);
//        if (str != EOF)
        if(!feof(srcFp))
            fputc(str, destFp);
        else 
            break;
    }
    fclose(srcFp);
    fclose(destFp);
    srcFp = NULL;
    destFp = NULL;
    return;
}

void intToString(char *string, int i)
{
    sprintf(string, "%d%s", i,".txt");
    printf("string = %s\n", string);
}
int main()
{
    int i;
    char *srcfilename = (char *)malloc(sizeof(10));
    for(i = 0; i < MAXNUM; i++)
    {
        intToString(srcfilename, i);
        fileAppend(srcfilename, "new.txt");
    }
    return 0;
}
