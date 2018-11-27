#include"Linklist.h"
// 等待键盘输入是一个数字0~1否则就一直等待用户输入
int inputdigit01(char ch)
{
	do
	{
		ch=getchar();
	}
	while(!(ch>='0'&&ch<='1'));
	return ch-'0';
}

// 等待键盘输入是一个数字0~2否则就一直等待用户输入
int inputdigit02(char ch)
{
	do
	{
		ch=getchar();
	}
	while(!(ch>='0'&&ch<='2'));
	return ch-'0';
}
// 等待键盘输入是一个数字1~2否则就一直等待用户输入
int inputdigit12(char ch)
{
	do
	{
		ch=getchar();
	}
	while(!(ch>='1'&&ch<='2'));
	return ch-'0';
}
// 等待键盘输入是一个数字0~3否则就一直等待用户输入
int inputdigit03(char ch)
{
	do
	{
		ch=getchar();
	}
	while(!(ch>='0'&&ch<='3'));
	return ch-'0';
}

// 等待键盘输入是一个数字0~5否则就一直等待用户输入
int inputdigit05(char ch)
{
	do
	{
		ch=getchar();
	}
	while(!(ch>='0'&&ch<='5'));
	return ch-'0';
}

// 等待键盘输入是一个数字0~6否则就一直等待用户输入
int inputdigit06(char ch)
{
	do
	{
		ch=getchar();
	}
	while(!(ch>='0'&&ch<='6'));
	return ch-'0';
}

// 等待键盘输入是一个数字0~8否则就一直等待用户输入
int inputdigit08(char ch)
{
	do
	{
		ch=getchar();
	}
	while(!(ch>='0'&&ch<='8'));
	return ch-'0';
}

int getch()
{
 int c=0;
 struct termios org_opts, new_opts;
    int res=0;
    //-----  store old settings -----------
     res=tcgetattr(STDIN_FILENO, &org_opts);//获取与终端相关的参数
     assert(res==0);
   //---- set new terminal parms --------
  memcpy(&new_opts, &org_opts, sizeof(new_opts));//拷贝结构体
 
  new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);
  tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);//设置终端参数
  c=getchar();
   //------  restore old settings ---------
  res=tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);//还原终端设置
  assert(res==0);
  return c;
}
//密码隐藏函数
void hiden(char pd[30])
{
	int i;
	while(1)
	{
 		for(i=0;;i++)
 		{
 			pd[i]=getch();
 			if(pd[i]=='\n')
 			{
 				pd[i]='\0';
 				break;
 			}
 			if(pd[i]==127)
 			{
 				printf("\b \b");
 				i=i-2;
 			}
 			else
 				printf("*");
 			if(i<0)
 				pd[0]='\0';
 		}
 		break;
 	}
}
//随机数生成验证码
void get_rand_str(int number)
{
	char str[63] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	int i,t;
	char ss[6];
	srand(time(NULL));
	for(i=0;i<number;i++)
	{
		t=rand()%62;
		ss[i]=str[t];
	}
	ss[4]='\0';
	strcpy(checknum,ss);
	printf("\033[;31m 请输入以下验证码:\033[0m");
}

//输入验证码调用函数
int iputchecking()
{   int i=0;
	int flag=0;
	char check[10];
    while(i<3)
    {
		get_rand_str(4); 
		puts(checknum);
    	scanf("%s",check);
    	if(strcmp(check,checknum)==0)
    	{        
    		flag=1;
     		break;
		}
		i++;
	}
	if(i==3)
		exit(1);
	return flag;
}

//模拟与服务器连接函数,动态打印>>
void printdot()
{
	int i = 3;
	while(i)
	{
		printf(" >> ");
		fflush(stdout);
		i--;
		sleep(1);
	}
	printf("\n");
}

//性别选择
void chosex(int d)
{
	if(d==0)
		strcpy(SEX,"女");
	if(d==1)
		strcpy(SEX,"男");
}

//添加人员时的职称选择
void chopos(char pos[30],int d)//由登录的人的职称限定他可以添加的人员信息
{
	if(strcmp(pos,"boss")==0)
	{
		if(d==0)
			strcpy(POS,"经理");
		else if(d==1)
			strcpy(POS,"销售经理");
		else if(d==2)
			strcpy(POS,"技术人员");
		else if(d==3)
			strcpy(POS,"销售人员");
	}
	else if(strcmp(pos,"经理")==0)
	{
		strcpy(POS,"技术人员");
		
	}
	else if(strcmp(pos,"销售经理")==0)
	{
		strcpy(POS,"销售人员");
	}
}
//部门选择
void depart(PERSONINFO e)
{
	if(strcmp(e.position,"经理")==0||strcmp(e.position,"技术人员")==0)
	{
		strcpy(DEP,"技术部");
	}
	if(strcmp(e.position,"销售经理")==0 ||strcmp(e.position,"销售人员")==0)
	{
		strcpy(DEP,"销售部");
	}
}

//级别选择
void gradechoice(PERSONINFO e)
{
	if(strcmp(e.position,"技术人员")==0 || strcmp(e.position,"销售人员")==0)
	{
		strcpy(GRD,"3"); 
	}
	if(strcmp(e.position,"经理")==0 || strcmp(e.position,"销售经理")==0)
	{
		strcpy(GRD,"2"); 
	}
}

//上级选择
void leaderchoice(PERSONINFO e)
{	
	if(strcmp(e.position,"技术人员")==0) 
	{
		strcpy(LEA,"经理"); 
	}
	if(strcmp(e.position,"销售人员")==0)
	{
		strcpy(LEA,"销售经理"); 
	}
	if(strcmp(e.position,"经理")==0 || strcmp(e.position,"销售经理")==0)
	{
		strcpy(LEA,"boss"); 
	}
}
//固定工资
double stablesal(PERSONINFO e)
{	
	double stablesalary;
	if(strcmp(e.position,"技术人员")==0) 
	{
		stablesalary=0; 
	}
	if(strcmp(e.position,"销售人员")==0)
	{
		stablesalary=0; 
	}
	if(strcmp(e.position,"经理")==0 )
	{
		stablesalary=20000; 
	}
	if( strcmp(e.position,"销售经理")==0)
	{
		stablesalary=5000; 
	}
	return stablesalary;
}

//工作时间
int wtime(PERSONINFO e)
{	
	int worktime;
	if(strcmp(e.position,"技术人员")==0) 
	{
		worktime=8; 
	}
	if(strcmp(e.position,"销售人员")==0)
	{
		worktime=0; 
	}
	if(strcmp(e.position,"经理")==0 )
	{
		worktime=0; 
	}
	if( strcmp(e.position,"销售经理")==0)
	{
		worktime=0; 
	}
	return worktime;
}

//单位时间报酬
int treward(PERSONINFO e)
{	
	if(strcmp(e.position,"技术人员")==0) 
	{
		e.timereward=50; 
	}
	if(strcmp(e.position,"销售人员")==0)
	{
		e.timereward=0; 
	}
	if(strcmp(e.position,"经理")==0 )
	{
		e.timereward=0; 
	}
	if( strcmp(e.position,"销售经理")==0)
	{
		e.timereward=0; 
	}
	return e.timereward;
}

//提成
double tic(PERSONINFO e)
{	
	if(strcmp(e.position,"技术人员")==0) 
	{
		e.ticheng=0; 
	}
	if(strcmp(e.position,"销售人员")==0)
	{
		e.ticheng=0.012; 
	}
	if(strcmp(e.position,"经理")==0 )
	{
		e.ticheng=0; 
	}
	if( strcmp(e.position,"销售经理")==0)
	{
		e.ticheng=0.01; 
	}
	return e.ticheng;
}

/******************************
功能:将链表中的信息保存到文件中
使用:在退出系统之前调用保存函数
传入参数:STNODE *head
******************************/
void save(STNODE *head)
{
	FILE *file;
	STNODE *p=head->next;
	file=fopen("personinfo.txt","w");
	if(file == NULL)
	{
		printf("\033[;31m 文件打开错误!!\033[0m\n");
		return;
	}
    while(p!=NULL)  //因为是以w的形式打开的文件，所以不论是否修改，都要重写文件
    {
         fwrite(&(p->person),sizeof(PERSONINFO),1,file);
         p=p->next;
    }
}

/******************************************
功能:读文件自动生成ID编号
使用:在添加人员时自动生成ID
传入参数:STNODE *head
******************************************/
/*
int readfileID(STNODE *head)
{
    STNODE *p=head->next;
    int bianhaoID;
    if(p==NULL)
    {
        return 1000;
    }
    bianhaoID=p->person.id;
    while(p->next!=NULL)
    {	
    	if(p->next->person.id>bianhaoID)
    		bianhaoID=p->next->person.id;
    	p=p->next;	
    }
    bianhaoID=bianhaoID+1;
    printf("%d\n",bianhaoID);
    return bianhaoID;
 }
 */
//遍历生成第一个不存在的最小的id编号
int readfileID(STNODE *head)
{
	STNODE *p=head->next;
	STNODE *q=NULL;
	int id=1000;
	PERSONINFO tmp;
	if(p==NULL)
	{
		return id;
	}
	for(p;p!=NULL;p=p->next)     //按id升序排列
	{
		for(q=p->next;q!=NULL;q=q->next)
			if(p->person.id>q->person.id)
			{
				tmp=p->person;
				p->person=q->person;
				q->person=tmp;
			}
	}
	STNODE *q1=head->next;
	while(q1!=NULL)            //遍历生成第一个不存在的最小的id编号
	{
		if(id==q1->person.id)
		{
			id++;
			q1=q1->next;
		}
		else
		{//printf("%d\n",id);
			break;
		}
	}
	return id;
}

/*************************************
功能:销毁链表---砍头法
使用:在退出系统操作时调用,回收系统资源
传入参数:STNODE *head
**************************************/
void DestroyLinklist(STNODE *head)
{
    STNODE *q=(STNODE *)malloc(sizeof (STNODE));
    q=head->next;
    while(q!=NULL)
    {
    	head->next=q->next;
    	free(q);
    	q=head->next;
     } 
}

/****************************************************
功能:读文件内容到链表的子函数
使用:在登录函数中需要调用,用来匹配登录人员信息是否正确
传入参数:char filename[30],要读取的文件名
*****************************************************/
STNODE * readfiletolist(char filename[30])
{
	STNODE *head=(STNODE *)malloc(sizeof(STNODE));
	head->next==NULL;
	PERSONINFO people;
	FILE *file=fopen(filename,"rt");
    if(file==NULL)
    {
        printf("\033[;31m 文件打开错误!!\033[0m\n");
        return;
    }
    else
    {
        while((fread(&people,sizeof(PERSONINFO),1,file))==1)//利用尾插法将文件中读取的信息临时存储在链表中
        {
            STNODE *p=(STNODE *)malloc(sizeof(STNODE));//1-1创建一个新结点p
                STNODE *tmp=head;
                while(tmp->next!=NULL)  //将指针移动到链表的尾部，即最后一个元素的地方,做尾插法操作
                    tmp=tmp->next;
                tmp->next=p;
                p->next=NULL;
                p->person=people;
        }//end of while   
    }// end of else
    return head;
}

/**************************************************
功能:释放链表的结点子函数
使用:在进行删除操作时使用
传入参数:STNODE *head,STNODE *q,头结点和要删除的结点
***************************************************/
STNODE * DeleteNode(STNODE *head,STNODE *q)
{
    STNODE *p=head;
    while(p->next!=NULL)
    {
         if(p->next==q)//比较地址,相同则找到了要删除的结点
         {
             STNODE *s=p->next;//保存要删除结点的地址
             p->next=p->next->next;//链接删除节点的前一个结点和后一个结点
             free(s);
             printf("\033[;31m 删除成功!!\033[0m\n");
             s=NULL;
             return head;
         }
         p=p->next;
    }
    if(p==q)//删除最后一个结点,置最后一个结点为空即可
    {
    	p=NULL;
    	printf("\033[;31m 删除成功!!\033[0m\n");
    }
    return head;
}


//返回主界面函数
void rethome()
{
	printf("\n按任意键回车后返回主界面 !!!\n");
	while(getchar() == '\n');
}

//打印信息函数
void print(PERSONINFO person)
{
	printf("%-8s%-12s%-11s%-9s%-6s%-12s%-16s%-12s%-s","\t编号","   姓名"," 密码","性别","职"," 称"," 部  门"," 等级","上级\n\n");
    printf("\t%d\t%-9s\t%-6s\t%-8s\t%-14s\t%-11s\t%s\t%-10s\n",
        person.id,person.name,person.passwd,person.sex,person.position,person.department,person.grade,person.leader);  
}

/**********************************************
功能:按姓名查找并返回找到了的信息的地址
使用:在删除,修改,查找中都需要调用
传入参数:STNODE *head,char name[30]
**********************************************/
STNODE *findname(STNODE *head,char name[30],char pos[30])
{
    STNODE *p=head->next;
    while(p!=NULL)
    {
    	if(strcmp(name,p->person.name)==0)
    	{
    		if(strcmp(pos,"boss")==0)
    		{
    			print(p->person);//打印信息
    			return p;
    		}
    		else if(strcmp(pos,"经理")==0 && strcmp(p->person.leader,"经理")==0)
    		{
    			print(p->person);//打印信息
    			return p;
    		}
    		else if(strcmp(pos,"销售经理")==0 && strcmp(p->person.leader,"销售经理")==0)
    		{
    			print(p->person);//打印信息
    			return p;
    		}
    	}
    	p=p->next;
    }
    if(strcmp(pos,"boss")==0)
    	printf("\033[;31m 文件中没有姓名是%s的人员的信息!!!\033[0m\n",name);
    else if(strcmp(pos,"经理")==0)
    	printf("\033[;31m 文件中没有姓名是%s的技术人员信息!!!\033[0m\n",name);
    else if(strcmp(pos,"销售经理")==0)
    	printf("\033[;31m 文件中没有姓名是%s的销售人员信息!!!\033[0m\n",name);
	return NULL;
}

/**********************************************
功能:按编号查找并返回地址
使用:修改,删除,查找中需要调用
传入参数:STNODE *head,int bianhao
**********************************************/
STNODE *findID(STNODE *head,int bianhao,char pos[30])
{
    STNODE *p=head->next;
    while(p!=NULL)
    {
    	if(bianhao==p->person.id)
    	{
    		if(strcmp(pos,"boss")==0)
    		{
    			print(p->person);//打印信息
    			return p;
    		}
    		else if(strcmp(pos,"经理")==0 && strcmp(p->person.leader,"经理")==0)
    		{
    			print(p->person);//打印信息
    			return p;
    		}
    		else if(strcmp(pos,"销售经理")==0 && strcmp(p->person.leader,"销售经理")==0)
    		{
    			print(p->person);//打印信息
    			return p;
    		}
    	}
    	p=p->next;
    }
    if(strcmp(pos,"boss")==0)
    	printf("\033[;31m文件中没有编号是%d的人员的信息!!!\033[0m\n",bianhao);
    else if(strcmp(pos,"经理")==0)
    	printf("\033[;31m文件中没有编号是%d的技术人员信息!!!\033[0m\n",bianhao);
    else if(strcmp(pos,"销售经理")==0)
    	printf("\033[;31m文件中没有编号是%d的销售人员信息!!!\033[0m\n",bianhao);
	return NULL;
}

/*******************************************
功能:按名字或编号删除调用的子函数
使用:在ui层删除中进行调用
传入参数:STNODE *head
*******************************************/
STNODE * findfordelete(STNODE *head,char pos[30])
{
    STNODE *q=NULL;
    char word[30];
    char ch;
	int choice,id;
    printf("请输入choice的值 1：按姓名删除  2：按编号删除\n");
    choice=inputdigit12(ch);//等待键盘输入是一个数字1~2否则就一直等待用户输入
    switch(choice)
    {
    	case 1:
    		printf("\033[;34m请输入姓名\033[0m:");
			scanf("%s",word);
    		q=findname(head,word,pos);
    		return q;
    		break;
		case 2:
			printf("\033[;34m请输入编号\033[0m:");
			scanf("%d",&id);
			q=findID(head,id,pos);
			return q;
    		break;
    }
}

//按名字或编号查找的函数
STNODE * findformodify(STNODE *head,char pos[30])
{
    STNODE *q=NULL;
    char word[30];
    char ch;
	int choice,id;
    printf("请输入修改方式 1：按姓名修改  2：按编号修改\n");
    choice=inputdigit12(ch);//等待键盘输入是一个数字1~2否则就一直等待用户输入
    switch(choice)
    {
    	case 1:
    		printf("\033[;34m请输入姓名\033[0m:");
			scanf("%s",word);
    		q=findname(head,word,pos);
    		return q;
    		break;
		case 2:
			printf("\033[;34m请输入编号\033[0m:");
			scanf("%d",&id);
			q=findID(head,id,pos);
			return q;
    		break;
    }
}
            
//添加人员信息
STNODE * AdddicinfoUI(STNODE *head,char pos[30])
{
	int d;char ch;int choice=1;char man[300];
	while(choice)
	{
	STNODE *p=(STNODE*)malloc(sizeof(STNODE));//1-1创建一个新结点p
    STNODE *tmp = head;
    p->person.id=readfileID(head);//自动生成id
    while(tmp->next!=NULL)//将指针移动到链表的尾部，即最后一个元素的地方
    	tmp=tmp->next;
    tmp->next=p;
    p->next=NULL;
//	p->person.id=readfileID(head);
	printf("请输入人员姓名:");
    scanf("%s",p->person.name);
    fflush(stdin);
    printf("请输入登录密码:");
    scanf("%s",p->person.passwd);
    fflush(stdin);
    printf("请输入人员性别: 1:男 0:女 ");
    d=inputdigit01(ch);//只能输入0,1 否则等待
    chosex(d);
    strcpy(p->person.sex,SEX);
    printf("请输入人员职称: 0:经理 1:销售经理 2:技术人员 3:销售人员 :");
    d=inputdigit03(ch);//只能输入0,3 否则等待
    chopos(pos,d);
    strcpy(p->person.position,POS);                              //职称
    depart(p->person);
	strcpy(p->person.department,DEP);                            //部门
	gradechoice(p->person);
	strcpy(p->person.grade,GRD);                                 //等级
	leaderchoice(p->person);
	strcpy(p->person.leader,LEA);                                //上级
	p->person.stasalary=stablesal(p->person);                    //固定工资
	p->person.worktime=wtime(p->person);                         //工作时间
	p->person.timereward=treward(p->person);                     //单位时间报酬
	p->person.ticheng=tic(p->person);                            //各类人员提成
	p->person.zonge=0;                                           //销售总额
	strcpy(p->person.performance,"一般");                        //人员表现
	p->person.latertimes=0;                                      //迟到次数
	p->person.salary=0;                                          //最终工资
	strcpy(p->person.beizhu,"此人员工资备注暂为空");              //工资备注
	printf("是否继续添加? 1:继续  0:不继续:");
	choice=inputdigit01(ch);//只能输入0,1 否则等待
	printf("%d,%s,%s,%s,%s,%s,%s,%s,%lf,%d,%lf,%lf,%lf,%s,%d,%lf,%s\n",p->person.id,p->person.name,p->person.passwd,p->person.sex,p->person.position,p->person.department,p->person.grade,p->person.leader,p->person.stasalary,p->person.worktime,p->person.timereward,p->person.ticheng,p->person.zonge,p->person.performance,p->person.latertimes,p->person.salary,p->person.beizhu);
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
	file=fopen("./Deletepersoninfo.txt","at");
	if(file==NULL)
	{
		printf("打开文件出错\n");
		return;
	}
	fwrite(&(p->person),sizeof(PERSONINFO),1,file);//向文件中追加一条纪录
	fclose(file);
	return;
}

//删除人员信息
STNODE * deletedicinfo(STNODE *head,char pos[30])
{
	STNODE *t=NULL;
	char ch;
	int confirm=0;

	t = findfordelete(head,pos);//查找到了要删除的地址
	if(t == NULL)
		return head;//地址为空时直接返回head
	printf("是否确认删除? 1:表示确认删除 0:表示不删除!!! \n");
	confirm = inputdigit01(ch);//等待键盘输入是一个数字0~1否则就一直等待用户输入
	if(confirm == 1)
	{
		savedeleteinfo(t);
		head=DeleteNode(head,t);
		return head;
	}
	else
		return head;				
}

//修改人员信息函数
STNODE *Modifydicinfo(STNODE *head,char pos[30])
{
	STNODE *tmp = NULL;
	char ch;
	tmp = findformodify(head,pos);
	if(tmp==NULL)
		return head;
	int confirm = 0;
	printf("\033[;31m是否确认修改? 1:表示确认修改 0:表示不修改!!!\033[0m\n");
	confirm=inputdigit01(ch);
	if(confirm == 1)
	{
		printf("\033[;36m请输入修改后的编号\033[0m：");
		scanf("%d",&tmp->person.id);
		printf("\033[;36m请输入修改后的姓名\033[0m：");
		scanf("%s",tmp->person.name);
		fflush(stdin);
		printf("\033[;36m请输入修改后的密码\033[0m：");
		scanf("%s",tmp->person.passwd);
		fflush(stdin);
		printf("\033[;36m请输入修改后的性别\033[0m：");
		scanf("%s",tmp->person.sex);
		fflush(stdin);
		printf("\033[;36m请输入修改后的职称\033[0m：");
		scanf("%s",tmp->person.position);
		fflush(stdin);
		printf("\033[;36m请输入修改后的部门\033[0m：");
		scanf("%s",tmp->person.department);
		fflush(stdin);
		printf("\033[;36m请输入修改后的等级\033[0m：");
		scanf("%s",tmp->person.grade);
		fflush(stdin);
		return head;
	}
	else
		return head;	
}

//按名字或编号查找的函数
void searchnameorID(STNODE *head,char pos[30])
{
    STNODE *q=NULL;
    char word[30];
    char ch;
	int choice,id,choice1=1;
	while(choice1)
	{
    printf("\033[;31m请选择查找方式 1：按姓名查找  2：按编号查找\033[0m\n");
    choice=inputdigit12(ch);//等待键盘输入是一个数字1~2否则就一直等待用户输入
    switch(choice)
    {
    	case 1:
    		printf("\033[;34m请输入人员姓名:\033[0m");
			scanf("%s",word);
    		q=findname(head,word,pos);
    		break;
		case 2:
			printf("\033[;34m请输入人员编号:\033[0m");
			scanf("%d",&id);
			q=findID(head,id,pos);
    		break;
    }
    printf("\033[;31m是否继续查找? 1:继续 0:不继续 :\033[0m");
    choice1=inputdigit01(ch);
    }
}

void prit(STNODE *p)
{
	while(p!=NULL)//读取数据并打印  //\t可以消除空格的影响重新对齐
    {
		printf("\t%d\t%-9s\t%-6s\t%-8s\t%-14s\t%-11s\t%s\t%-10s\n",
        p->person.id,p->person.name,p->person.passwd,p->person.sex,p->person.position,p->person.department,p->person.grade,p->person.leader);         
       p=p->next;
    }
}

//读文件并且打印数据的函数
void showdicinfo(STNODE *head,char pos[30])
{
    STNODE *p=head->next;
    if(p==NULL)
    {
    	printf("\t\033[;31m人员表中中的信息为空,请先添加信息 !!!\033[0m\n");
    }
    printf("\t\t\t\t\t\t人员信息如下");
     printf("\n\t=====================================================================================\n");
    printf("%-8s%-12s%-11s%-9s%-6s%-12s%-16s%-12s%-s","\t编号","   姓名"," 密码","性别"," 职"," 称"," 部  门"," 等级","上级\n\n");
    if(strcmp(pos,"boss")==0)
    { 
    	prit(p);
    }
    else if(strcmp(pos,"经理")==0)
    {
    	while(p!=NULL)//读取数据并打印  //\t可以消除空格的影响重新对齐
    	{
    	    if(strcmp(p->person.leader,"经理")==0)
    	    {
				printf("\t%d\t%-9s\t%-6s\t%-8s\t%-14s\t%-11s\t%s\t%-10s\n",
        		p->person.id,p->person.name,p->person.passwd,p->person.sex,p->person.position,p->person.department,p->person.grade,p->person.leader);         
       		}
       		p=p->next;
    }        
    }
    else if(strcmp(pos,"销售经理")==0)
    {	 
    	while(p!=NULL)//读取数据并打印  //\t可以消除空格的影响重新对齐
    	{
    	if(strcmp(p->person.leader,"销售经理")==0)
    	{
			printf("\t%d\t%-9s\t%-6s\t%-8s\t%-14s\t%-11s\t%s\t%-10s\n",
        	p->person.id,p->person.name,p->person.passwd,p->person.sex,p->person.position,p->person.department,p->person.grade,p->person.leader);         
        }
        p=p->next;
   	   }        
    }
    printf("\n\t=====================================================================================\n");
    return;
}

/**********************************
功能:技术人员或销售人员查看自己的信息
使用:在技术人员或销售人员查看时调用
***********************************/
void showselfinfo(STNODE *head,int idnum)
{
	STNODE *p=head->next;
	 printf("\n\t=====================================================================================\n");
	printf("%-8s%-12s%-11s%-9s%-6s%-12s%-16s%-12s%-s","\t编号","   姓名"," 密码","性别"," 职"," 称"," 部  门"," 等级","上级\n\n");
	while(p!=NULL)
	{
		if(p->person.id==idnum)
		{
			printf("\t%d\t%-9s\t%-6s\t%-8s\t%-14s\t%-11s\t%s\t%-10s\n",
        	p->person.id,p->person.name,p->person.passwd,p->person.sex,p->person.position,p->person.department,p->person.grade,p->person.leader);   
		}
		p=p->next;
	}
	 printf("\n\t=====================================================================================\n");
}

/************************************
功能:技术人员或销售人员修改自己的信息
使用:在技术人员或销售人员修改信息时调用
************************************/
STNODE *Modselfinfo(STNODE *head,int idnum)
{
	STNODE *tmp = NULL;
	STNODE *p=head->next;
	while(p!=NULL)
	{
		if(p->person.id==idnum)
		{	
			tmp=p;
			break;
		}
		p=p->next;
	}
	char ch;
	int confirm = 0;
	printf("\033[;31m是否确认修改? 1:表示确认修改 0:表示不修改!!\033[0m\n");
	confirm=inputdigit01(ch);
	if(confirm == 1)
	{
		printf("\033[;34m请输入修改后的姓名：\033[0m");
		scanf("%s",tmp->person.name);
		fflush(stdin);
		printf("\033[;34m请输入修改后的密码：\033[0m");
		scanf("%s",tmp->person.passwd);
		fflush(stdin);
		printf("\033[;34m请输入修改后的性别：\033[0m");
		scanf("%s",tmp->person.sex);
		fflush(stdin);
		return head;
	}
	else
		return head;	
}

//读取删除了的人员的函数
void showdeleteinfo(char pos[30])
{
	PERSONINFO person;
    FILE *file;
    int filepos=0;
    file=fopen("./Deletepersoninfo.txt","rt");
    if(file==NULL)
    {
    	printf("打开文件出错!\n");
    	return;
    }
    fseek(file,0,SEEK_END);
    filepos=ftell(file);		//报告文件距离文件开头的位移量,为0,怎文件为空
    if(filepos==0)
    {
    	printf("\033[;31m暂时没有被删除的人员的纪录!!\033[0m\n");
    	return;
    }
    rewind(file);				//使得文件指针指向文件首部
    fread(&person,sizeof(PERSONINFO),1,file);
    printf("\t\t\t\t\t\t\033[;31m删除的人员信息如下\033[0m");
    printf("\n\t=====================================================================================\n");
    printf("%-8s%-12s%-11s%-9s%-6s%-12s%-16s%-12s%-s","\t编号","   姓名"," 密码","性别"," 职"," 称"," 部  门"," 等级","上级\n\n");
    if(strcmp(pos,"boss")==0)
    { 
    	while(!feof(file))
    	{
    		printf("\t%d\t%-9s\t%-6s\t%-8s\t%-14s\t%-11s\t%s\t%-10s\n",
        		person.id,person.name,person.passwd,person.sex,person.position,person.department,person.grade,person.leader);
        	fread(&person,sizeof(PERSONINFO),1,file);   
    	}
    	fclose(file);
    	file=NULL;
    }
    else if(strcmp(pos,"经理")==0)
    {
    	while(!feof(file))
    	{
    	    if(strcmp(person.leader,"经理")==0)
    	    {
    			printf("\t%d\t%-9s\t%-6s\t%-8s\t%-14s\t%-11s\t%s\t%-10s\n",
        		person.id,person.name,person.passwd,person.sex,person.position,person.department,person.grade,person.leader);
        	} 
        	fread(&person,sizeof(PERSONINFO),1,file);  
    	}
    	fclose(file);
    	file=NULL;
    }        
    else if(strcmp(pos,"销售经理")==0)
    {	 
    	while(!feof(file))
    	{
    	    if(strcmp(person.leader,"销售经理")==0)
    	    {
    			printf("\t%d\t%-9s\t%-6s\t%-8s\t%-14s\t%-11s\t%s\t%-10s\n",
        		person.id,person.name,person.passwd,person.sex,person.position,person.department,person.grade,person.leader);
        	} 
        	fread(&person,sizeof(PERSONINFO),1,file);  
    	}
    	fclose(file);
    	file=NULL;	    
    }
     printf("\n\t=====================================================================================\n");
    return;
}

/************************************
功能:退出前保存操作并且回收系统资源
使用:在选0退出系统之前进行调用
************************************/
void confirmsave(STNODE *head)
{
	int confirm=0;
	char ch;
	printf("\033[;31m是否保存? 1:表示确认保存 0:表示不保存 !\033[0m\n");
	confirm=inputdigit01(ch);
	if(confirm == 1)
	{
		save(head);
		printf("\033[;31m信息保存成功!\n\033[0m");
		printf("\033[;31mpress any key to exit...!!\n\033[0m");
		while(getchar() == '\n');
			printf("\n\033[;31m已安全退出系统,谢谢使用!!\n\033[0m");
		DestroyLinklist(head);//销毁此链表并且回收系统资源退出
		exit(0);
	}
	else
	{
		printf("\n\033[;31m已安全退出系统,谢谢使用!!\n\033[0m");
		DestroyLinklist(head);//销毁此链表并且回收系统资源退出
		exit(0);
		
	}
}

//获取当前系统时间
void gettime()
{
	time_t rawtime;
	struct tm *tm;
	time ( &rawtime );
	tm = localtime( &rawtime );
	sprintf(stime1,"%d-%d-%d %d:%d:%d",tm->tm_year+1900,tm->tm_mon+1,tm->tm_mday,tm->tm_hour,tm->tm_min,tm->tm_sec);
}

/****************************************************
功能:读文件内容到链表的子函数
使用:在登录函数中需要调用,用来匹配登录人员信息是否正确
传入参数:char filename[30],要读取的文件名
*****************************************************/
STNODE1 * readfiletolist1(char filename[30])
{
	STNODE1 *head=(STNODE1 *)malloc(sizeof(STNODE1));
	head->next==NULL;
	LOGMES people;
	FILE *file=fopen(filename,"rt");
    if(file==NULL)
    {
        printf("打开文件出错！\n");
        return;
    }
    else
    {
        while((fread(&people,sizeof(LOGMES),1,file))==1)//利用尾插法将文件中读取的信息临时存储在链表中
        {
            STNODE1 *p=(STNODE1 *)malloc(sizeof(STNODE1));//1-1创建一个新结点p
                STNODE1 *tmp=head;
                while(tmp->next!=NULL)  //将指针移动到链表的尾部，即最后一个元素的地方,做尾插法操作
                    tmp=tmp->next;
                tmp->next=p;
                p->next=NULL;
                p->person1=people;
        }//end of while   
    }// end of else
    fclose(file);
    return head;
}

/******************************
功能:将链表中的信息保存到文件中
使用:在退出系统之前调用保存函数
传入参数:STNODE *head
******************************/
void save1(STNODE1 *head)
{
	FILE *file;
	STNODE1 *p=head->next;
	file=fopen("./logintable.txt","w");
	if(file == NULL)
	{
		printf("文件打开错误!!\n");
		return;
	}
    while(p!=NULL)  //因为是以w的形式打开的文件，所以不论是否修改，都要重写文件
    {
         fwrite(&(p->person1),sizeof(LOGMES),1,file);
         p=p->next;
    }
    fclose(file);
}

//文件追加函数
void appentext(char filename[30],int id,char name[30],char pass[30],char last[30],int lotimes)
{
	FILE *fp;
	LOGMES person;
	person.id=id;
	strcpy(person.name,name);
	strcpy(person.passwd,pass);
	strcpy(person.lastlogintime,last);
	person.logincounts=lotimes;
	fp=fopen(filename,"at");
	if(fp==NULL)
	{
		printf("打开登录信息表出错!!\n");
		return;
	}
	fwrite(&person,sizeof(LOGMES),1,fp);
	fclose(fp);
}

//登录时提示上次登录时间和登录次数,首次登录提示首次登录
void logininf(int id,char name[30],char pass[30])
{
	LOGMES person;
	gettime();                                       //获取系统时间函数调用
	STNODE1 *head=readfiletolist1("./logintable.txt");//从文件中读取登录人员的信息
	person.id=id;
	strcpy(person.name,name);
	strcpy(person.passwd,pass);
	strcpy(person.lastlogintime,stime1);
	person.logincounts=1;
	
	STNODE1 *p=head->next;
	if(p==NULL)
	{
		printf("%s\033[47;31m您好!您是首次登录!欢迎您的到来!\033[0m\n",name);
		appentext("./logintable.txt",id,name,pass,person.lastlogintime,1);
		sleep(4);
		return;
	}
	while(p!=NULL)
	{
		if(id==p->person1.id)
		{
			p->person1.logincounts++;
			printf("%s\033[47;31m您好!您上次登录时间是\033[0m%s,\033[47;31m第\033[0m%d\033[47;31m次登录,欢迎您的到来!\033[0m\n",p->person1.name,p->person1.lastlogintime,p->person1.logincounts);
			strcpy(p->person1.lastlogintime,stime1);//修改以前登录过的人登录时间和登录次数并且随后进行保存操作
			save1(head);
			sleep(4);
			return;
		}
		p=p->next;
	}
	if(p==NULL)
	{
		printf("%s\033[47;31m您好!您是首次登录!欢迎您的到来!\033[0m\n",name);
		appentext("./logintable.txt",id,name,pass,person.lastlogintime,1);//将第一次登录系统的人员信息追加到文件中
		sleep(4);
		return;
	}
}
/*
//工资按照职称,表现,迟到次数计算最终工资
void judgesalary(PERSONINFO e)
{
	char bz[100];
	if(strcmp(e.position,"经理")==0)
	{
		if(strcmp(e.performance,"一般")==0)
		{
			if(e.latertimes>=3)
			{	
				e.salary=e.stasalary-100;
				sprintf(bz,"表现一般,迟到%d次,扣除工资100元",e.latertimes);
				strcpy(e.beizhu,bz);
			}
			else
			{
				e.salary=e.stasalary;
				sprintf(bz,"表现一般,迟到少于三次,不扣工资,也没有奖励!");
				strcpy(e.beizhu,bz);
			}
		}
		if(strcmp(e.performance,"优秀")==0)
		{	
			e.salary=e.stasalary+500;
			sprintf(bz,"表现优秀,奖励工资500元,再接再厉!");	
			strcpy(e.beizhu,bz);
		}
	}
	else if(strcmp(e.position,"销售经理")==0)
	{
		if(strcmp(e.performance,"一般")==0)
		{
			if(e.latertimes>=3)
			{	
				e.salary=e.stasalary+e.zonge*e.ticheng-100;
				sprintf(bz,"表现一般,迟到%d次,扣除工资100,提成加上%.0lf",e.latertimes,e.zonge*e.ticheng);
				strcpy(e.beizhu,bz);
			}
			else
			{
				e.salary=e.stasalary+e.zonge*e.ticheng;
				sprintf(bz,"表现一般,迟到少于三次,不扣工资,提成加%.0lf",e.zonge*e.ticheng);
				strcpy(e.beizhu,bz);
			}
		}
		if(strcmp(e.performance,"优秀")==0)
		{	
			e.salary=e.stasalary+e.zonge*e.ticheng+500;
			sprintf(bz,"表现优秀,奖励500元,提成加上%.0lf,再接再厉!",e.zonge*e.ticheng);
			strcpy(e.beizhu,bz);
		}
		
	}
	else if(strcmp(e.position,"技术人员")==0)
	{
		if(strcmp(e.performance,"一般")==0)
		{ 
			if(e.latertimes>=3)
			{	
				e.salary=e.worktime*e.timereward*30-100;
				sprintf(bz,"表现一般,迟到%d次,扣除工资100",e.latertimes);
				strcpy(e.beizhu,bz);
			}
			else
			{   
				e.salary=e.worktime*e.timereward*30;
				sprintf(bz,"表现一般,迟到少于三次,不扣工资,也没有奖励!");
				strcpy(e.beizhu,bz);
			}
		}
		if(strcmp(e.performance,"优秀")==0)
		{	
			e.salary=e.worktime*e.timereward*30+500;
			sprintf(bz,"表现优秀,奖励500元,再接再厉!!");
			strcpy(e.beizhu,bz);
		}
		
	}
	else if(strcmp(e.position,"销售人员")==0)
	{
		if(strcmp(e.performance,"一般")==0)
		{
			if(e.latertimes>=3)
			{	
				e.salary=e.ticheng*e.zonge-100;
				sprintf(bz,"表现一般,迟到%d次,扣除工资100,提成加上%.0lf",e.latertimes,e.ticheng*e.zonge);
				strcpy(e.beizhu,bz);
			}
			else
			{
				e.salary=e.ticheng*e.zonge;
				sprintf(bz,"表现一般,迟到少于三次,不扣工资,提成加%.0lf",e.ticheng*e.zonge);
				strcpy(e.beizhu,bz);
			}
		}
		if(strcmp(e.performance,"优秀")==0)
		{	
			e.salary=e.ticheng*e.zonge+500;
			sprintf(bz,"表现优秀,奖励500元,再接再厉!!");
			strcpy(e.beizhu,bz);
		}
	}
	printf("%d,%s,%.0lf,%.0lf,%.0lf,%s\n",e.id,e.name,e.stasalary,e.zonge,e.salary,e.beizhu);
}

*/
//对工资的操作需要修改对应地址下面的内容,所以采用传地址的方式操作上面的方法void judgesalary(PERSONINFO e)只能在本函数内部修改,出了函数之后就不行了
void judgesalary(STNODE *p)
{
	char bz[100];
	if(strcmp(p->person.position,"经理")==0)
	{
		if(strcmp(p->person.performance,"一般")==0)
		{
			if(p->person.latertimes>=3)
			{	
				p->person.salary=p->person.stasalary-100;
				sprintf(bz,"表现一般,迟到%d次,扣除工资100元",p->person.latertimes);
				strcpy(p->person.beizhu,bz);
			}
			else
			{
				p->person.salary=p->person.stasalary;
				sprintf(bz,"表现一般,迟到少于三次,不扣工资,也没有奖励!");
				strcpy(p->person.beizhu,bz);
			}
		}
		if(strcmp(p->person.performance,"优秀")==0)
		{	
			p->person.salary=p->person.stasalary+500;
			sprintf(bz,"表现优秀,奖励工资500元,再接再厉!");	
			strcpy(p->person.beizhu,bz);
		}
	}
	else if(strcmp(p->person.position,"销售经理")==0)
	{
		if(strcmp(p->person.performance,"一般")==0)
		{
			if(p->person.latertimes>=3)
			{	
				p->person.salary=p->person.stasalary+p->person.zonge*p->person.ticheng-100;
				sprintf(bz,"表现一般,迟到%d次,扣除工资100,提成加上%.0lf",p->person.latertimes,p->person.zonge*p->person.ticheng);
				strcpy(p->person.beizhu,bz);
			}
			else
			{
				p->person.salary=p->person.stasalary+p->person.zonge*p->person.ticheng;
				sprintf(bz,"表现一般,迟到少于三次,不扣工资,提成加%.0lf",p->person.zonge*p->person.ticheng);
				strcpy(p->person.beizhu,bz);
			}
		}
		if(strcmp(p->person.performance,"优秀")==0)
		{	
			p->person.salary=p->person.stasalary+p->person.zonge*p->person.ticheng+500;
			sprintf(bz,"表现优秀,奖励500元,提成加上%.0lf,再接再厉!",p->person.zonge*p->person.ticheng);
			strcpy(p->person.beizhu,bz);
		}
		
	}
	else if(strcmp(p->person.position,"技术人员")==0)
	{
		if(strcmp(p->person.performance,"一般")==0)
		{ 
			if(p->person.latertimes>=3)
			{	
				p->person.salary=p->person.worktime*p->person.timereward*30-100;
				sprintf(bz,"表现一般,迟到%d次,扣除工资100",p->person.latertimes);
				strcpy(p->person.beizhu,bz);
			}
			else
			{   
				p->person.salary=p->person.worktime*p->person.timereward*30;
				sprintf(bz,"表现一般,迟到少于三次,不扣工资,也没有奖励!");
				strcpy(p->person.beizhu,bz);
			}
		}
		if(strcmp(p->person.performance,"优秀")==0)
		{	
			p->person.salary=p->person.worktime*p->person.timereward*30+500;
			sprintf(bz,"表现优秀,奖励500元,再接再厉!!");
			strcpy(p->person.beizhu,bz);
		}
		
	}
	else if(strcmp(p->person.position,"销售人员")==0)
	{
		if(strcmp(p->person.performance,"一般")==0)
		{
			if(p->person.latertimes>=3)
			{	
				p->person.salary=p->person.ticheng*p->person.zonge-100;
				sprintf(bz,"表现一般,迟到%d次,扣除工资100,提成加上%.0lf",p->person.latertimes,p->person.ticheng*p->person.zonge);
				strcpy(p->person.beizhu,bz);
			}
			else
			{
				p->person.salary=p->person.ticheng*p->person.zonge;
				sprintf(bz,"表现一般,迟到少于三次,不扣工资,提成加%.0lf",p->person.ticheng*p->person.zonge);
				strcpy(p->person.beizhu,bz);
			}
		}
		if(strcmp(p->person.performance,"优秀")==0)
		{	
			p->person.salary=p->person.ticheng*p->person.zonge+500;
			sprintf(bz,"表现优秀,奖励500元,再接再厉!!");
			strcpy(p->person.beizhu,bz);
		}
	}
//	printf("%d,%s,%.0lf,%.0lf,%.0lf,%s\n",p->person.id,p->person.name,p->person.stasalary,p->person.zonge,p->person.salary,p->person.beizhu);
}




















