#include"addrdata.h"


//获取当前系统时间
char * gettime()
{
	char *systime = (char *)malloc(sizeof(char)*30);
	char year[20],mon[10],day[10],hour[10],min[10],sec[10];
	time_t rawtime;
	struct tm *tm;
	time ( &rawtime );
	tm = localtime ( &rawtime );
	sprintf(year,"%d",tm->tm_year+1900);
	if(tm->tm_mon + 1 < 10)
		sprintf(mon,"0%d",tm->tm_mon+1);
	else
		sprintf(mon,"%d",tm->tm_mon+1);
	if(tm->tm_mday  < 10)
		sprintf(day,"0%d",tm->tm_mday);
	else
		sprintf(day,"%d",tm->tm_mday);
	if(tm->tm_hour < 10)
		sprintf(hour,"0%d",tm->tm_hour);
	else
		sprintf(hour,"%d",tm->tm_hour);
	if(tm->tm_min < 10)
		sprintf(min,"0%d",tm->tm_min);
	else
		sprintf(min,"%d",tm->tm_min);
	if(tm->tm_sec < 10)
		sprintf(sec,"0%d",tm->tm_sec);
	else
		sprintf(sec,"%d",tm->tm_sec);
	sprintf(systime,"%s-%s-%s %s:%s:%s",year,mon,day,hour,min,sec);//printf("systime = %s\n",systime);
	return systime;
}

/**********************************************************
功能:动态生成指针节点，尾插法。辅助read_file_use_fscanf函数的
使用:在read_file_use_fscanf函数中调用
传入参数:STNODE * 的头指针和 PERSONINFO people
返回值:void,对地址进行操作，无须返回头节点
**********************************************************/

void generate_node(PERSONINFO people,STNODE *head)
{
	STNODE *p = (STNODE *)malloc(sizeof(STNODE));//1-1创建一个新结点p
    STNODE *tmp = head;
    while(tmp->next != NULL)  //将指针移动到链表的尾部，即最后一个元素的地方,做尾插法操作
    	tmp = tmp->next;
    tmp->next = p;
    p->person = people;
    p->next = NULL;
	return ;
}
/**********************************************************
功能:使用尾插法将查找到的信息的节点存入另外一个链表中
使用:在函数中调用
传入参数:STNODE * 的头指针和 STNODE *p
返回值:void,对地址进行操作，无须返回头节点
**********************************************************/

void copy_node(STNODE *q,STNODE *head)
{
	STNODE *p = (STNODE *)malloc(sizeof(STNODE));//1-1创建一个新结点p
    STNODE *tmp = head;
    while(tmp->next != NULL)  //将指针移动到链表的尾部，即最后一个元素的地方,做尾插法操作
    	tmp = tmp->next;
    tmp->next = p;
    p->person = q->person;
    p->next = NULL;
	return ;
}

/****************************************************
功能:使用fscanf函数读取文件，辅助readfiletolist函数的
使用:在readfiletolist函数的调用
传入参数:要读取的文件名和STNODE * 的头指针
返回值:void
*****************************************************/

void read_file_use_fscanf(char filename[30],STNODE *head)
{
	FILE *file = fopen(filename,"rb");
	PERSONINFO people;
	if(file == NULL)
    {
        printf("\033[;31m 文件(%s)打开错误!!\033[0m\n",filename);
        return;
    }
	while(!feof(file))
    {
        fscanf(file,"%d %s %s %s %s %s %s %s %s\n",
        	&people.id,
        	people.name,
        	people.sex,
        	people.age,
        	people.telephone,
        	people.address,
        	people.group,
        	people.mails,
        	people.addtime);//从文件读入记录
        generate_node(people,head);//利用尾插法将文件中读取的信息临时存储在链表中
    }//end of while
    file = NULL;
}

/****************************************************
功能:能够实现读取文件的内容到动态链表中
使用:在管理员登录成功后调用，用来获取通讯录的信息
传入参数:char filename[30],要读取的文件名
返回值:返回STNODE * 的头指针,避免使用全局的头指针
*****************************************************/

STNODE * readfiletolist(char filename[30])
{
	STNODE *head = (STNODE *)malloc(sizeof(STNODE));
	head->next == NULL;
	read_file_use_fscanf(filename,head);
    return head;
}

/****************************************************
功能:
使用:
传入参数:
返回值:
*****************************************************/
void print(STNODE *head)
{	
	STNODE *p = head->next;
	while(p != NULL)
	{	
		printf("\t%-10d %-10s %-10s %-10s %-10s %-10s %-10s %-10s %10s\n",
			p->person.id,
        	p->person.name,
        	p->person.sex,
        	p->person.age,
        	p->person.telephone,
        	p->person.address,
        	p->person.group,
        	p->person.mails,
        	p->person.addtime);
		p = p->next;
	}
}

//保存文件的函数
void savefile(STNODE *head,char filename[30])
{
	STNODE *p = head->next;
	FILE *fp = fopen(filename,"wb");
	if(fp == NULL)
	{
		printf("\033[;31m打开文件%s出错\033[0m\n",filename);
		return ;
	}
	while(p != NULL)
	{	
		fprintf(fp,"%-8d %-20s %-10s %-10s %-15s %-15s %-10s %-15s %15s\n",
			p->person.id,
        	p->person.name,
        	p->person.sex,
        	p->person.age,
        	p->person.telephone,
        	p->person.address,
        	p->person.group,
        	p->person.mails,
        	p->person.addtime);
		p = p->next;
	}
	printf("\033[;31m信息保存成功！\033[0m\n");
	return ;
}

/*************************************
功能:销毁链表---砍头法
使用:在退出系统时调用,回收系统资源
传入参数:STNODE *head
**************************************/
void DestroyLinklist(STNODE *head)
{
    STNODE *q = (STNODE *)malloc(sizeof(STNODE));
    q = head->next;
    while(q != NULL)
    {
    	head->next = q->next;
    	free(q);
    	q = head->next;
     } 
}

//按编号从小到大排序
void linksort_small_to_big(STNODE *head)
{
	STNODE *p = head->next;
	STNODE *q = NULL;
	PERSONINFO tmp;
	for(p;p != NULL;p = p->next)     //按编号升序排列
	{
		for(q = p->next;q != NULL;q = q->next)
			if(p->person.id > q->person.id)
			{
				tmp = p->person;
				p->person = q->person;
				q->person = tmp;
			}
	}
}

//按编号从大到小排序
void linksort_big_to_small(STNODE *head)
{
	STNODE *p = head->next;
	STNODE *q = NULL;
	PERSONINFO tmp;
	for(p;p != NULL;p = p->next)     //按编号降序排列
	{
		for(q = p->next;q != NULL;q = q->next)
			if(p->person.id<q->person.id)
			{
				tmp = p->person;
				p->person = q->person;
				q->person = tmp;
			}
	}
}

//将id编号存入整形数组中
void get_id_to_array(STNODE *head,int a[])
{
	STNODE *p = head->next;
	int i = 0;
	while(p != NULL)
	{
		a[i] = p->person.id;
		i++;
		p = p->next;
	}
}

//数组排序从小到大，冒泡排序
void array_sort_small_to_big(int a[],int n)
{
	int i,j,temp;
	for(i = 0; i < n-1; i++ ) //外循环的趟数是数组个数减一
	{
		for(j = 0; j < n-i-1; j++)//每进行一次外循环内循环就减一
		{
			if(a[j] > a[j+1])//每一次外层循环内层循环都需要把相邻位置的两个数进行比较
			{
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
	}
}

//遍历生成第一个不存在的最小的id编号
int get_min_id(STNODE *head)
{
	int id=1000;
	if(head->next == NULL)
	{
		return id;
	}
	int len = GetLines(head);
	int Lenarry[len];
	get_id_to_array(head,Lenarry);
	array_sort_small_to_big(Lenarry,len);
	int i = 0;            //遍历生成第一个未使用的最小的id编号
	for(i = 0; i < len ; i++)
	{
		if(id == Lenarry[i])
		{
			id++;
		}
		else
		{//printf("%d\n",id);
			break;
		}
	}
	return id;
}

//处理键盘输入字符的函数，返回值为int型的
int inputdigit(char li,char left,char right)
{
	char ch[50];
	//printf("请输入操作选项：%c 到 %c之间的数字!!\n",left,right);
	do
	{
		fgets(ch,49,stdin);
		li = ch[0];
		rewind(stdin);/*清空键盘缓冲区里的无用字符*/
		if(!(li >= left && li <= right))
			printf("\033[;31m您输入的操作选项有误，请重新输入!!\033[0m\n");
	}
	while(!(li >= left && li <= right));
	return li-'0';
}
/*
//删除链表节点的函数
void DeleteNode(STNODE *head,STNODE *q)
{
    STNODE *p = head;
    while(p->next != NULL)
    {
         if(p->next == q)//比较地址,相同则找到了要删除的结点
         {
             STNODE *s = p->next;//保存要删除结点的地址
             p->next = p->next->next;//链接删除节点的前一个结点和后一个结点
             free(s);
             printf("\033[;31m 删除成功!!\033[0m\n");
             s=NULL;
             return;
         }
         p = p->next;
    }
}
*/

STNODE * DeleteNode(STNODE *head,STNODE *temp)
{
	STNODE *s = head;
	STNODE *t = s->next;//printf("DeleteNode \n");
	while( t != NULL)
	{
		if(t == temp)
		{
			s->next = t->next;
			free(t);
			t = NULL;
			return head;
		}
		else
		{
			s = t;
			t = s->next;
		}
	}
	return head;
}

/****************************************************
功能：保存删除人员的信息
使用：在删除之前进行保存
****************************************************/
void savedeleteinfo(STNODE *p)
{
	FILE *file;
	file=fopen("Deletepersoninfo.txt","at");
	if(file == NULL)
	{
		printf("打开文件出错\n");
		return;
	}
	fprintf(file,"%-8d %-20s %-10s %-10s %-15s %-15s %-10s %-15s %15s\n",
			p->person.id,
        	p->person.name,
        	p->person.sex,
        	p->person.age,
        	p->person.telephone,
        	p->person.address,
        	p->person.group,
        	p->person.mails,
        	p->person.addtime);
	fclose(file);
	return;
}

/****************************************************
功能:自己定义的计算包含中文字符的字符串的长度
使用:在GainColumnMaxLength函数中用
传入参数:char *p
返回值:int 类型的字符串长度
*****************************************************/
//求字符串长度的函数，这是解决问题的关键，可以简化思路
int MyStrlen(char *p)
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
		p++;//printf("1111  ");printf("len = %d\n",len);
	}
	size = len - i*4/3;//系统和编码不同，后面的参数也不同，请因地制宜！
	//printf("i = %d\n",i);
	return size;
}

//初始化分配空间的函数
void InitAarry(char *name[],char *str[],int *length[],int a,int n)
{
	int i = 0;//printf("into InitAarry!\n");
	for(i = 0;i < a*n; i++)
	{
		name[i] = (char *)malloc(sizeof(char *)*100);//printf("name[%d]=%p\n",i,name[i]);
		length[i] = (int *)malloc(sizeof(int *)*20);//printf("length[%d]=%p\n",i,length[i]);
	}
	for(i = 0;i < a; i++)
	{
		str[i] = (char *)malloc(sizeof(char *)*300);//printf("name[%d]=%p\n",i,name[i]);
	}
}

//整齐打印文件内容的整合函数
void ShowInfo_In_order(STNODE *head)
{
	int a = 1 + GetLines(head);//读取员工信息并且存入字符串数组中来,返回记录的行数
	int n = 9;
	char *name[a*n];     //定义二维字符串数组
	char *str[a];        //定义二位字符串数组
	int *length[a*n];    //定义一个计数的数组
	int max[n];          //存储每一列最大值的
	int erwei[a][n];     //二维整形数组,存储空格数目的
	//printf("before InitAarry\n");
	InitAarry(name,str,length,a,n);  //初始化数组，分配空间
	int i = AppendColumn(name);      //将列名加入字符串数组中
	ReadInfotoArray(name,i,head);    //读取链表信息到数组中来
	GainColumnMaxLength(name,length,max,erwei,a*n,n);//同下
	GetMax(erwei,length,max,a*n,n);      //获取每一列的最大宽度
	AddBlank(name, length,a*n,n);        //不足的填补空格使之居中
	PrintInfoIntoTable(name,str,max,a,n);//打印函数调用
	//FreeSpace(name,str,length,a,a*n); 
	//回收系统资源函数,使用时发现打印多次时调用这个函数会出现乱码，因此就不调用了，让系统自行回收资源
}

//获取记录的条数
int GetLines(STNODE *head)
{
	
	int a=0;
	STNODE *p = head->next;
	while(p != NULL)
	{
		a++;
		p =  p->next;
	}//printf("a = %d\n",a);
	return a;
}

//将列名存入数组之中来，再打印文件信息
int AppendColumn(char *array[])
{
	int i = 0;
	{
		strcpy(array[i],"编号");  i++;
		strcpy(array[i],"姓名"); i++;
		strcpy(array[i],"性别");  i++;
		strcpy(array[i],"年龄");  i++;
		strcpy(array[i],"联系电话"); i++;
		strcpy(array[i],"家庭住址"); i++;
		strcpy(array[i],"群组"); i++;
		strcpy(array[i],"邮箱"); i++;
		strcpy(array[i],"添加日期"); i++;
	}
	return i;
}

//int类型的转化成字符串的类型的函数
char * int_form_string(int num)
{
	char *s = malloc(sizeof(char)* 30);
	sprintf(s,"%d",num);
	return s;
}

//读取动态链表中的信息并且存入字符串数组中来
void ReadInfotoArray(char *array[],int i,STNODE *head)
{
	STNODE *p = head->next;
	while(p != NULL)
	{
		
		{
			strcpy(array[i],int_form_string(p->person.id)); i++;
			strcpy(array[i],p->person.name);  i++;
			strcpy(array[i],p->person.sex);  i++;
			strcpy(array[i],p->person.age);  i++;
			strcpy(array[i],p->person.telephone); i++;
			strcpy(array[i],p->person.address); i++;
			strcpy(array[i],p->person.group); i++;
			strcpy(array[i],p->person.mails); i++;
			strcpy(array[i],p->person.addtime); i++;
		}//printf("i=%d\n",i);      
		p = p->next;
	}
}

//获取数组的每一列的最大宽度
void GainColumnMaxLength(char *array[],int *length[],int max[],int erwei[][9],int c,int n)
{
	int i,j;
	
	for(i = 0;i < c; i++)
	{
		*length[i] = MyStrlen(array[i]);	
	}

	for(i = 0; i < c/n; i++)
		for(j = 0; j < n; j++)
		{
			erwei[i][j] = *length[i*n+j];//一维数组转二维数组
		}
}

//获取数组每一列的最大值函数
int GetMax(int erwei[][9],int *length[],int max[],int c,int n)
{
	int big,i = 0,j = 0;
	//获取数组每一列的最大值big
	for(j = 0; j < n; j++)
	{
		big = erwei[0][j];
		
		for(i = 0; i < c/n; i++)
		{ 
			if(big < erwei[i][j])  //i,j不要写反了列作为外循环次数
			{	
				big = erwei[i][j];
			}
		}
		max[j] = big;//printf("max[%d]=%d\n",j,max[j]);
	}
	for(j = 0; j < n; j++)
	{
		for(i = 0; i < c/n; i++)
		{ 
			erwei[i][j] = max[j] - erwei[i][j]; //计算出每一列的空格的数目存入数组中
		}
	}
	
	for(i = 0; i < c/n;i++)
		for(j = 0; j < n;j++)
		{
			*length[i*n+j] = erwei[i][j];//二维数组转一维数组
		}
}

/*
memset是计算机中C/C++语言函数。
将s所指向的某一块内存中的前n个字节的内容全部设置为ch指定的ASCII值， 
第一个值为指定的内存地址，块的大小由第三个参数指定，
这个函数通常为新申请的内存做初始化工作， 其返回值为指向s的指针
void *memset(void *s, int ch, size_t n);
*/

//逐个遍历不够长度的填补空格,其中n表示列的数量，c表示数组的长度,使得字符串能够居中
void AddBlank(char *array[], int *length[],int c,int n)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int m = 0;
	char *blank;
	blank = (char *)malloc(sizeof(char *)*100);
	for( i = 0; i < c; i++)
	{
		if((*length[i] + 4)%2 == 0)
		{
			for(k = 0; k < (*length[i] + 4)/2; k++)
			{
				strcat(blank," ");
			}
			strcat(blank,array[i]);
			for(m = 0; m < (*length[i] + 4)/2; m++)
			{
				strcat(blank," ");
			}
			strcpy(array[i],blank);
		}
		else
		{
			for(k = 0; k < (*length[i] + 4)/2+1; k++)
			{
				strcat(blank," ");
			}
			strcat(blank,array[i]);
			for(m = 0; m < (*length[i] + 3)-(*length[i] + 4)/2; m++)
			{
				strcat(blank," ");
			}
			strcpy(array[i],blank);
		}
		memset(blank,0,sizeof(char *)*100);//因为strcat连接字符串的，不清空的话空格会越来越多
	}
}

//将|和文件中每一行的记录连接起来,其中n表示列的数量，a表示记录的条数，也就是行数
void linking(char *array[],char *str[],int a,int n)
{
	int i = 0;
	int j = 0;
	for(i = 0; i < a; i++)
	{
		for(j = 0; j < n; j++)
		{
			strcat(str[i],"|");
			strcat(str[i],array[i*n+j]);
		}
		sprintf(str[i],"%s|",str[i]);
	}
}

//整齐打印数组中的内容，呈现表格,其中n表示列的数量，a表示记录的条数，也就是行数
void PrintInfoIntoTable(char *array[],char *str[],int max[],int a,int n)
{
	int i = 0;
	int j = 0;
	int k = 0;
	linking(array,str,a,n);
	for(i = 0;i < n; i++)  //+4是想增长一些宽度，打印时好看一点
	{
		max[i] = max[i] + 4;
	}
	for(i = 0; i < a ; i++)
	{
		for(j = 0; j < n; j++)
		{
			printf("+");         //先打印+----+的一列再打印str[i]的内容
			for(k = 0;k < max[j]; k++)
			{
				printf("-");
			}
		}
		printf("+");
		printf("\n%s\n",str[i]);
	}	
	for(i = 0; i < 1 ; i++)
	{
		for(j = 0; j < n; j++)
		{
			printf("+");
			for(k = 0;k < max[j]; k++)
			{
				printf("-");
			}
		}
		printf("+\n");
	}
}

//回收系统资源
void FreeSpace(char *name[],char *str[],int *length[],int a,int n)
{	
	int i = 0;
	for(i = 0;i < n; i++)
	{
		//printf("name[%d]=%p\n",i,name[i]);
		//free(*(p+i));printf("name[%d]=%p\n",i,name[i]);printf("%s\n",name[i]);
		free(name[i]);
		name[i] = NULL;
		free(length[i]);
		length[i] = NULL;
	}
	for(i = 0;i < a; i++)
	{
		memset(str[i],0,sizeof(char *)*300);
		free(str[i]);
		str[i] = NULL;
	}
}









