#include "formatPrintf.h"
/*
int main()
{
    STNODE *head = NULL;
    head = readFileToList("test.txt");
    showInfoInorder(head); // 调用函数接口实现功能
    destroyLinklist(head); // 释放链表分配的资源
    return 0;
}
*/
/****************************************************
功能:自己定义的计算包含中文字符的字符串的长度
使用:在gainColumnMaxLength函数中用
传入参数:char *p
返回值:int 类型的字符串长度
*****************************************************/
//求字符串长度的函数，这是解决问题的关键
int myStrLen(char *p)
{
    int len = 0;
    int size = 0;
    int i = 0;
    while(*p != '\0')
    {
        if(*p >= 0 && *p <= 127)
        {
            len = len + 1;
        }
        else
        {
            len = len + 2;
            i++;
        }
        p++;//printf("1111  ");printf("len = %d\n", len);
    }
    size = len - i*4/3;//系统和编码不同，后面的参数也不同，请因地制宜！
    //printf("i = %d\n", i);
    return size;
}

//初始化分配空间的函数
void initAarry(char *name[], char *str[], int *length[], int a, int n)
{
    int i = 0;
    for(i = 0; i < a*n; i++)
    {
        name[i] = (char *)malloc(sizeof(char)*100);
        memset(name[i], 0, sizeof(char)*100);
        length[i] = (int *)malloc(sizeof(int )*20);
    }
    for(i = 0; i < a; i++)
    {
        str[i] = (char *)malloc(sizeof(char *)*300);
        memset(str[i], 0, sizeof(char *)*300);
    }
}

//整齐打印文件内容的整合函数
void showInfoInorder(STNODE *head)
{
    int a = 1 + getLines(head); //读取员工信息并且存入字符串数组中来, 返回记录的行数
    int n = 9;
    char *name[a*n];     //定义二维字符串数组
    char *str[a];        //定义二位字符串数组
    int *length[a*n];    //定义一个计数的数组
    int max[n];          //存储每一列最大值的
    int erwei[a][n];     //二维整形数组, 存储空格数目的
    initAarry(name, str, length, a, n);  //初始化数组，分配空间
    int i = appendColumn(name);        //将列名加入字符串数组中
    readInfoToArray(name, i, head);    //读取链表信息到数组中来
    gainColumnMaxLength(name, length, max, erwei, a*n, n); //同下
    getMax(erwei, length, max, a*n, n);      //获取每一列的最大宽度
    addBlank(name, length, a*n, n);          //不足的填补空格使之居中
    printInfoIntoTable(name, str, max, a, n); //打印函数调用
    freeSpace(name, str, length, a, a*n);   //回收系统资源函数,
}

//获取记录的条数
int getLines(STNODE *head)
{
    int a = 0;
    STNODE *p = head->next;
    while(NULL != p)
    {
        a++;
        p =  p->next;
    }//printf("a = %d\n",a);
    return a;
}

//将列名存入数组之中来，再打印文件信息
int appendColumn(char *array[])
{
    int i = 0;
    {
        strcpy(array[i], "编号");  i++;
        strcpy(array[i], "姓名"); i++;
        strcpy(array[i], "性别");  i++;
        strcpy(array[i], "年龄");  i++;
        strcpy(array[i], "联系电话"); i++;
        strcpy(array[i], "家庭住址"); i++;
        strcpy(array[i], "群组"); i++;
        strcpy(array[i], "邮箱"); i++;
        strcpy(array[i], "添加日期"); i++;
    }
    return i;
}

// 生成新的链表结点
void generateNode(PERSONINFO people, STNODE *head)
{
    STNODE *p = (STNODE *)malloc(sizeof(STNODE)); //1-1创建一个新结点p
    STNODE *tmp = head;
    while(NULL != tmp->next)  //将指针移动到链表的尾部，即最后一个元素的地方,做尾插法操作
        tmp = tmp->next;
    tmp->next = p;
    p->next = NULL;
    p->person = people;
    return ;
}

// 读取文件内容到链表之中
void readFileUseFscanf(char filename[30], STNODE *head)
{
    FILE *file = fopen(filename, "rb");
    PERSONINFO people;
    if(NULL == file)
    {
        printf("\033[;31m 文件(%s)打开错误!!\033[0m\n",filename);
        return;
    }
    while(!feof(file))
    {
        fscanf(file, "%d %s %s %s %s %s %s %s %s\n",
               &people.id,
               people.name,
               people.sex,
               people.age,
               people.telephone,
               people.address,
               people.group,
               people.mails,
               people.addtime); //从文件读入记录,下面存入链表中
        generateNode(people, head); //利用尾插法将文件中读取的信息临时存储在链表中
    }//end of while
    fclose(file);
    file = NULL;
}

// 返回读取到文件信息的链表的头指针
STNODE * readFileToList(char filename[30])
{
    STNODE *head = (STNODE *)malloc(sizeof(STNODE));
    head->next = NULL;
    readFileUseFscanf(filename, head);  // 使用fscanf函数读取文件
    return head;
}

// 将int的id数字转化为字符串
char * intFormString(int num)
{
    char *s = malloc(sizeof(char)* 30);
    memset(s, 0, sizeof(char)* 30);
    sprintf(s, "%d", num);
    return s;
}

//读取员工信息并且存入字符串数组中来
void readInfoToArray(char *array[], int i, STNODE *head)
{
    STNODE *p = head->next;
    while(NULL != p)
    {
        {
            char *s = intFormString(p->person.id);
            strcpy(array[i], s); i++;
            free(s);
            s = NULL;
            strcpy(array[i], p->person.name);  i++;
            strcpy(array[i], p->person.sex);  i++;
            strcpy(array[i], p->person.age);  i++;
            strcpy(array[i], p->person.telephone); i++;
            strcpy(array[i], p->person.address); i++;
            strcpy(array[i], p->person.group); i++;
            strcpy(array[i], p->person.mails); i++;
            strcpy(array[i], p->person.addtime); i++;
        }//printf("i=%d\n",i);
        p = p->next;
    }
}

//获取数组的每一列的最大宽度
void gainColumnMaxLength(char *array[], int *length[], int max[], int erwei[][9], int c, int n)
{
    int i, j;

    for(i = 0; i < c; i++)
    {
        *length[i] = myStrLen(array[i]);
    }

    for(i = 0; i < c/n; i++)
    {
        for(j = 0; j < n; j++)
        {
            erwei[i][j] = *length[i*n+j];//一维数组转二维数组
        }
    }
        
    //    printf("erwei\n");
    //    for(i = 0; i < c/n;i++)
    //        for(j = 0; j < n;j++)
    //        {
    //            printf("%-4d",erwei[i][j]);
    //            if(j == n-1)
    //                printf("\n");
    //        }
    //    printf("length\n");
    //    for(i = 0; i < c; i++)
    //    {
    //        printf("%-4d",*length[i]);
    //        if(i%n==(n-1))
    //            printf("\n");
    //    }
}

//获取数组每一列的最大值函数
int getMax(int erwei[][9], int *length[], int max[], int c, int n)
{
    int big, row = 0, column = 0;
    //获取数组每一列的最大值big
    for(column = 0; column < n; column++)
    {
        big = erwei[0][column];

        for(row = 0; row < c/n; row++)
        {
            if(big < erwei[row][column])  //row, column不要写反了列作为外循环次数
            {
                big = erwei[row][column];
            }
        }
        max[column] = big;//printf("max[%d]=%d\n", column, max[column]);
    }
    for(column = 0; column < n; column++)
    {
        for(row = 0; row < c/n; row++)
        {
            erwei[row][column] = max[column] - erwei[row][column]; //计算出每一列的空格的数目存入数组中
        }
    }
    /*
    printf("max ====\n");
    for(column = 0; column < n; column++)
        printf("%-4d",max[column]);
    printf("\n");

    printf("new===erwei\n");
    for(row = 0; row < c/n; row++)
    {
        for(column = 0; column < n; column++)
        {
            printf("%-4d",erwei[row][column]);
            if(column == (n-1))
                printf("\n");
        }
    }
    printf("\n");
    */
    for(row = 0; row < c/n; row++)
        for(column = 0; column < n;column++)
        {
            *length[row*n+column] = erwei[row][column];//二维数组转一维数组
        }
    /*
    printf("new length\n");
    for(row = 0; row < c; row++)
    {
        printf("%-4d",*length[row]);
        if(row%n == (n-1))
            printf("\n");
    }
*/
}

/*
memset是计算机中C/C++语言函数。
将s所指向的某一块内存中的前n个字节的内容全部设置为ch指定的ASCII值， 
第一个值为指定的内存地址，块的大小由第三个参数指定，
这个函数通常为新申请的内存做初始化工作， 其返回值为指向s的指针
void *memset(void *s, int ch, size_t n);
*/

//逐个遍历不够长度的填补空格, 其中n表示列的数量，c表示数组的长度, 使得字符串能够居中
void addBlank(char *array[], int *length[], int c, int n)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int m = 0;
    char blank[200];
    for( i = 0; i < c; i++)
    {
        memset(blank, 0, 200);//因为strcat连接字符串的，不清空的话空格会越来越多
        if(0 == (*length[i] + 4) % 2)   //处理居中的方法，分奇数和偶数个空格数目进行
        {
            for(k = 0; k < (*length[i] + 4)/2; k++)
            {
                strcat(blank, " ");
            }
            strcat(blank, array[i]);
            for(m = 0; m < (*length[i] + 4)/2; m++)
            {
                strcat(blank, " ");
            }
            strcpy(array[i], blank);
        }
        else
        {
            for(k = 0; k < (*length[i] + 4)/2+1; k++)
            {
                strcat(blank, " ");
            }
            strcat(blank, array[i]);
            for(m = 0; m < (*length[i] + 3)-(*length[i] + 4)/2; m++)
            {
                strcat(blank, " ");
            }
            strcpy(array[i], blank);
        }
    }
}

//将|和文件中每一行的记录连接起来, 其中n表示列的数量，a表示记录的条数，也就是行数
void linking(char *array[], char *str[], int a, int n)
{
    int i = 0;
    int j = 0;
    for(i = 0; i < a; i++)
    {
        for(j = 0; j < n; j++)
        {
            strcat(str[i], "|");
            strcat(str[i], array[i*n+j]);
            //strcat(str[i],"|");
            //sprintf(str[i],"\n|%s%s%s%s%s%s%s%s%s|",array[i*n+0],array[i*n+0]);
        }
        sprintf(str[i], "%s|", str[i]);
        //memset(blank,0,sizeof(char *)*30);
        //printf("%s\n",str[i]);
    }
}

//整齐打印数组中的内容，呈现表格, 其中n表示列的数量，a表示记录的条数，也就是行数
void printInfoIntoTable(char *array[], char *str[], int max[], int a, int column)
{
    int i = 0;
    int j = 0;
    int k = 0;
    linking(array, str, a, column);
    for(i = 0; i < column; i++)  //+4是想增长一些宽度，打印时好看一点
    {
        max[i] = max[i] + 4;
    }
    for(i = 0; i < a ; i++)
    {
        for(j = 0; j < column; j++)
        {
            printf("+");         //先打印+----+的一列再打印str[i]的内容
            for(k = 0; k < max[j]; k++)
            {
                printf("-");
            }
        }
        printf("+");
        if(0 == i)
            printf(L_RED"\n%s\n"NONE, str[i]);
        else
            printf("\n%s\n", str[i]);
    }
    for(i = 0; i < 1 ; i++)
    {
        for(j = 0; j < column; j++)
        {
            printf("+");
            for(k = 0; k < max[j]; k++)
            {
                printf("-");
            }
            //printf("%-s",array[i*n+j]);
        }
        printf("+\n");
    }
}

// destroy linklist 释放链表
//void destroyLinklist(STNODE *head)
//{
//    STNODE *tmp = head;
//    STNODE *tmp_next;
//    while(NULL != tmp)
//    {
//        printf("%p->", tmp);
//        tmp = tmp->next;
//    }
//    printf("\n");
//    tmp = head;
//    if (NULL != tmp)
//    {
//        tmp_next = tmp->next;
//    }
//    else
//    {
//        return;
//    }
//    while (NULL != tmp_next)
//    {
//        printf("tmp = %p ", tmp);
//        printf("tmp_next = %p \n", tmp_next);
//        free(tmp);
//        tmp = NULL;
//        tmp = tmp_next;
//        tmp_next = tmp_next->next;
//    }
//    return;
//}

// destroy linklist 释放链表
void destroyLinklist(STNODE *head)
{
    STNODE *phead = head;
    STNODE *tmp;
    while(NULL != phead)
    {
        tmp = phead;         // 将第一个结点赋值给tmp，即将释放掉
        phead = phead->next; // 更改phead为下一个结点，即将free掉上一个结点
        free(tmp);
        tmp = NULL;          // 为了防止野指针，最好置为NULL
    }
}

//回收系统资源，对于手动malloc的所有资源需要手动free掉
void freeSpace(char *name[], char *str[], int *length[], int a, int n)
{	
    int i = 0;
    for(i = 0; i < n; i++)
    {
        //printf("name[%d]=%p\n",i,name[i]);
        //free(*(p+i));printf("name[%d]=%p\n",i,name[i]);printf("%s\n",name[i]);
        free(name[i]);
        name[i] = NULL;
        free(length[i]);
        length[i] = NULL;
    }
    for(i = 0; i < a; i++)
    {
        memset(str[i], 0, sizeof(char *)*300);
        free(str[i]);
        str[i] = NULL;
    }
}



