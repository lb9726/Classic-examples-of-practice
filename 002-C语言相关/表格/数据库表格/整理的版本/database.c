/*                      前言    
MyStrlen(char *p)是自己重新写的计算长度的函数，因为系统的strlen求出的中文字符
在不同的系统和不同的编码情况下的之都是不相同的，所以在ubuntu和windows下的打印的
strlen求出的中文字符的长度不一定相同，例如：ubuntu 14.04 64位操作系统下打印的一个
中文字符的长度为3而实际上确实只占了两个字符的宽度，导致了我们这些追求完美的程序猿们
打印表格时老是出现对不齐，（好吧！我就是其中的一只）因此奋发图强，想要写出一个可以比拟
数据库的自适应打印整齐表格的功能，可是纵观网上给出的示例仅仅是处理了不包括中文字符的例子
，作为中国人，连文字都被外国人歧视这是我所不能忍受的，因此写出了这个可以解决包含中文字符，
并且可以整齐打印出表格函数接口来供我驱使，这其中最关键的部分是发现问题并且想出对策，将一个复
杂的问题细化，分步解决是我的编程思想之一。我们要坚信中华民族是世界上最聪明的种族之一，是一个五
千年文化都不曾中断的国度，我们更要坚信，只有想不到的没有做不到的，如果连想都不敢想，那和木鱼有什
么分别在这里我要感谢那位帮助我完成这段代码的大神，我在困惑的时候，和他交流了思想，是他点拨我写出了
Mystrlen函数的，从而顺利解决问题的。还要感谢我的以前的室友是他给我提供了fsanf（）函数的使用方法的例子
，才能让我编写代码的周期变短。虽然代码完全是我自己写出来的，但是没有他们的帮助，我也不会如此顺利的完成，
感谢这些给我提供帮助的巨人们。因个人能力有限，可能写的代码比较挫，但好歹我也完成了自己最初的设想，这也是
我绞尽脑汁，呕心沥血的作品，虽然享受了成功后的喜悦，但我没有骄傲，因为我是站在巨人的肩膀上的，没有他们，我
们的代码也没有任何意义，我想说，知识是全人类的，只是我们思考问题的方式不一样而已。我会在合适的时候将我的代码分
享给大家的！写完代码的那一刻，我感受到了兴奋，站在晴朗的天空下，享受着阳光的沐浴，即便这是冬天，我也感觉到温暖，
因为温暖就是阳光的味道！此刻，我的心也是暖暖的！               ---------一只刚就业的程序猿（libo）内心深处的独白！
*/

/*
功能简介：本程序实现了从文件中读取文件内容，然后可以模拟出数据库的格式整齐的打印到终端（控制台上）
功能看似简单，但是实现起来确实有一定的难度，这其中要用到的功能，需要经过一步步细化，分解才能实现
至少我是这么感觉的，最重要的是有想法，没有做不到的，只有想不到的！奋斗吧！骚年！当然代码还是有很多
地方不太好的，本人能力有限，才疏学浅，江郎才尽！至于优化方面的，就请有需要的同志们自行修改，写出更优秀的代码吧！
*/

#include "database.h"

int  main()
{
	DefineAarryandStorageInfo(); //调用函数接口实现功能
	return 0;
}

//自己定义的求字符串长度的函数，这是解决问题的关键，可以简化思路
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

void InitAarry(char *name[],char *str[],int *length[],int a,int n)
{
	int i=0;
	for(i=0;i<a*n;i++)
	{
		name[i]=(char *)malloc(sizeof(char *)*80);//printf("name[%d]=%p\n",i,name[i]);
		length[i]=(int *)malloc(sizeof(int *)*20);//printf("length[%d]=%p\n",i,length[i]);
	}
	for(i=0;i<a;i++)
	{
		str[i]=(char *)malloc(sizeof(char *)*300);//printf("name[%d]=%p\n",i,name[i]);
	}
}

//整齐打印文件内容的整合函数
void DefineAarryandStorageInfo()
{
	int a = 1 + GetLines("职工管理系统.txt");//读取员工信息并且存入字符串数组中来,返回记录的行数
	int n = 8;
	char *name[a*n];     //定义二维字符串数组
	char *str[a];        //定义二位字符串数组
	int *length[a*n];    //定义一个计数的数组
	int max[n];          //存储每一列最大值的
	int erwei[a][n];     //二维整形数组,存储空格数目的
	InitAarry(name,str,length,a,n);
	int i = AppendColumn(name);
	ReadInfotoArray(name,i);//PrintInfo(name,a*n,n);
	GainColumnMaxLength(name,length,max,erwei,a*n,n);
	GetMax(erwei,length,max,a*n,n);
	AddBlank(name, length,a*n,n);
	//PrintInfo(name,a*n,n);
	PrintInfoIntoTable(name,str,max,a,n);
	FreeSpace(name,str,length,a,a*n);//PrintInfo(name,a*n,n);
}

//获取记录的条数
int GetLines(char filename[30])
{
	FILE *fp;
	int a=0;
	WORKERS worker;
	fp=fopen(filename, "rb");
	if(fp == NULL)
	{
		printf("open file %s failed !\n",filename);
		return -1;
	}
	while(!feof(fp))
	{
		fscanf(fp, "%s %s %s %s %s %s %s %s\n",
				worker.Name,
				worker.Num,
				worker.Sex,
				worker.Age,
				worker.Rank,
				worker.Department,
				worker.Salary,
				worker.Passwd);//从文件读入记录   
		a++;
	}
	//printf("记录的条数为 a=%d\n",a);
	fclose(fp);
	fp=NULL;
	return a;
}
//将列名存入数组之中来，再打印文件信息
int AppendColumn(char *array[])
{
	int i=0;
	{
		strcpy(array[i],"姓名"); i++;
		strcpy(array[i],"编号");  i++;
		strcpy(array[i],"性别");  i++;
		strcpy(array[i],"年龄");  i++;
		strcpy(array[i],"级别"); i++;
		strcpy(array[i],"部门"); i++;
		strcpy(array[i],"当月薪水"); i++;
		strcpy(array[i],"密码"); i++;
	}
	return i;
}
//读取员工信息并且存入字符串数组中来
void ReadInfotoArray(char *array[],int i)
{
	WORKERS worker;
	FILE *fp;												  //指向文件的指针
	if((fp = fopen("职工管理系统.txt", "rb")) == NULL)		  //打开文件
	{
		printf("can not open file\n");	  					  //不能打开
 		exit(0);
	}
	
	while(!feof(fp))
	{
		fscanf(fp, "%s %s %s %s %s %s %s %s\n",
				worker.Name,
				worker.Num,
				worker.Sex,
				worker.Age,
				worker.Rank,
				worker.Department,
				worker.Salary,
				worker.Passwd);//从文件读入记录,下面存入二维数组中
		{
			strcpy(array[i],worker.Name); i++;
			strcpy(array[i],worker.Num);  i++;
			strcpy(array[i],worker.Sex);  i++;
			strcpy(array[i],worker.Age);  i++;
			strcpy(array[i],worker.Rank); i++;
			strcpy(array[i],worker.Department); i++;
			strcpy(array[i],worker.Salary); i++;
			strcpy(array[i],worker.Passwd); i++;
		}//printf("i=%d\n",i);      
	}
	fclose(fp);//printf("length = %d\n",strlen(array[1]));
}

//获取数组的每一列的最大宽度
void GainColumnMaxLength(char *array[],int *length[],int max[],int erwei[][8],int c,int n)
{
	int i,j;
	
	for(i=0;i<c;i++)
	{
		*length[i] = MyStrlen(array[i]);	
	}

	for(i = 0; i < c/n;i++)
		for(j = 0; j < n;j++)
		{
			erwei[i][j] = *length[i*n+j];//一维数组转二维数组
		}
/*	printf("erwei\n");		
	for(i = 0; i < c/n;i++)
		for(j = 0; j < n;j++)
		{
			printf("%-4d",erwei[i][j]);
			if(j == n-1)
				printf("\n");
		}
	printf("length\n");
	for(i = 0; i < c; i++)
	{
		printf("%-4d",*length[i]);
		if(i%n==(n-1))
			printf("\n");
	}
	*/
}

//获取数组每一列的最大值函数
int GetMax(int erwei[][8],int *length[],int max[],int c,int n)
{
	int big,i=0,j=0;
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
	/*
	printf("max ====\n");
	for(j = 0; j < n; j++)
		printf("%-4d",max[j]);
	printf("\n");
	
	printf("new===erwei\n");
	for(i = 0; i < c/n; i++)
	{
		for(j = 0; j < n; j++)
		{ 
			printf("%-4d",erwei[i][j]);
			if(j == (n-1))
				printf("\n"); 
		}
	}
	printf("\n");
	*/
	for(i = 0; i < c/n;i++)
		for(j = 0; j < n;j++)
		{
			*length[i*n+j] = erwei[i][j];//二维数组转一维数组
		}
		/*
	printf("new length\n");		
	for(i = 0; i < c; i++)
	{
		printf("%-4d",*length[i]);
		if(i%n==(n-1))
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

//逐个遍历不够长度的填补空格,其中n表示列的数量，c表示数组的长度
void AddBlank(char *array[], int *length[],int c,int n)
{
	int i = 0;
	int j = 0;
	int k = 0;
	char *blank;
	blank = (char *)malloc(sizeof(char *)*30);
	for( i = 0; i < c; i++)
	{
		for(k = 0; k < *length[i] + 4; k++)
		{
			strcat(blank," ");
		}
		strcat(array[i],blank);
		memset(blank,0,sizeof(char *)*30);//因为strcat连接字符串的，不清空的话空格会越来越多
	}
}
/*
//打印数组中的内容
void PrintInfo(char *array[],int c,int n)
{
	int i=0;
	for(i=0;i<c;i++)
	{
		printf("%-7s",array[i]);
		if(i%n==(n-1))
			printf("\n");
	}		
}
*/
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
			//strcat(str[i],"|");
			//sprintf(str[i],"\n|%s%s%s%s%s%s%s%s%s|",array[i*n+0],array[i*n+0]);
		}
		sprintf(str[i],"%s|",str[i]);
		//memset(blank,0,sizeof(char *)*30);
		//printf("%s\n",str[i]);
	}
}
//整齐打印数组中的内容，呈现表格,其中n表示列的数量，a表示记录的条数，也就是行数
void PrintInfoIntoTable(char *array[],char *str[],int max[],int a,int n)
{
	int i = 0;
	int j = 0;
	int k = 0;
	linking(array,str,a,n);
	for(i=0;i<n;i++)  //+4是想增长一些宽度，打印时好看一点
	{
		max[i] = max[i] + 4;
	}
	for(i = 0; i < a ; i++)
	{
		for(j = 0; j < n; j++)
		{
			printf("+");
			for(k = 0;k < max[j]; k++)
			{
				printf("-");
			}
			//printf("|");//printf("\n");
		    //printf("%-s",array[i*n+j]);
		}
		printf("+");
		printf("\n%s",str[i]);//printf("%-s",array[i*n+j]);
		printf("\n");
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
			//printf("|");//printf("\n");
		    //printf("%-s",array[i*n+j]);
		}
		printf("+\n");
	}
}

//回收系统资源
void FreeSpace(char *name[],char *str[],int *length[],int a,int n)
{	
	int i = 0;
	for(i=0;i<n;i++)
	{
		//printf("name[%d]=%p\n",i,name[i]);
		//free(*(p+i));printf("name[%d]=%p\n",i,name[i]);printf("%s\n",name[i]);
		free(name[i]);
		name[i] = NULL;
		free(length[i]);
		length[i] = NULL;
	}
	for(i=0;i<a;i++)
	{
		free(str[i]);
		str[i] = NULL;
	}
}







