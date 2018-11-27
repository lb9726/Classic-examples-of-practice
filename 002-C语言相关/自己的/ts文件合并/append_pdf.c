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
        {   
            fputc(str, destFp);
        }
        else 
        {
            break;
        }
    }
    fclose(srcFp);
    fclose(destFp);
    srcFp = NULL;
    destFp = NULL;
    return;
}

void intToString(char *string, int i)
{
    sprintf(string, "%s%d%s","C++参考大全第四版_", i,".pdf");
    printf("string = %s\n", string);
}
int main(int argc, char *argv[])
{
    int i;
    char *srcfilename = (char *)malloc(80);
    memset(srcfilename, 0, 80);
    if (argc < 3)
    {
        printf("请输入2个参数以确定起始和终止！\n");
        return -1;
    }
    int start = atoi(argv[1]);
    int end = atoi(argv[2]);
    printf("argv[0] = %s, argv[1] = %s\n", argv[1], argv[2]);
    printf("start = %d, end = %d\n", start, end);
    if (start >= end)
    {
        printf("参数大小有误，前者要比后者小\n");
        return -2;
    }
    char *desfilename = (char *)malloc(100);
    /*
    char *desfilename = (char *)malloc(sizeof(100));
    start = 0, end = 1
app: malloc.c:2374: sysmalloc: Assertion `(old_top == (((mbinptr) (((char *) &((av)->bins[((1) - 1) * 2])) - __builtin_offsetof (struct malloc_chunk, fd)))) && old_size == 0) || ((unsigned long) (old_size) >= (unsigned long)((((__builtin_offsetof (struct malloc_chunk, fd_nextsize))+((2 *(sizeof(size_t))) - 1)) & ~((2 *(sizeof(size_t))) - 1))) && ((old_top)->size & 0x1) && ((unsigned long) old_end & pagemask) == 0)' failed.
Aborted (core dumped)

    */
    memset(desfilename, 0, 100);
    sprintf(desfilename, "%s%d%s", "C++参考大全第四版_", start,"合并.pdf");
    printf("desfilename = %s\n", desfilename);
    for(i = start; i <= end; i++)
    {
        intToString(srcfilename, i);
        fileAppend(srcfilename, desfilename);
    }
    free(srcfilename);
    srcfilename = NULL;
    
    free(desfilename);
    desfilename = NULL;
    return 0;
}
