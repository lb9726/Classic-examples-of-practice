#include "../include/addrdata.h"

//改变终端显示参数函数
int getch()
{
 	int c = 0;
 	struct termios org_opts, new_opts;
    int res = 0;
    //-----  store old settings -----------
    res = tcgetattr(STDIN_FILENO, &org_opts);//获取与终端相关的参数
    assert(res == 0);
   //---- set new terminal parms --------
    memcpy(&new_opts, &org_opts, sizeof(new_opts));//拷贝结构体
 
    new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);//设置终端参数
    c=getchar();
    //------  restore old settings ---------
    res = tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);//还原终端设置
    assert(res == 0);
    return c;
}

//密码隐藏函数
void hiden(char pd[30])
{
	int i;
	while( 1 )
	{
 		for( i = 0;  ; i++)
 		{
 			pd[i] = getch();
 			if(pd[i] =='\n')
 			{
 				pd[i] = '\0';
 				break;
 			}
 			if(pd[i] == 127)
 			{
 				printf("\b \b");
 				i = i-2;
 			}
 			else
 				printf("*");
 			if(i < 0)
 				pd[0] = '\0';
 		}
 		break;
 	}
}

//随机数生成验证码
char * get_rand_str(int number)
{
	char *verify_code = (char *)malloc(sizeof(char)*10);
	memset(verify_code, 0, sizeof(char)*10);
	char str[63] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	int i, t;
	char ss[6];
	srand(time(NULL));
	for(i = 0;i < number; i++)
	{
		t = rand()%62;
		ss[i] = str[t];
	}
	ss[4]='\0';
	strcpy(verify_code, ss);
	printf("\033[;31m 请输入以下验证码, 区分大小写!!!:\033[0m");
	return verify_code;
}

//输入验证码调用函数
int input_checking()
{   
	int i = 0;
	int flag = 0;
	char check[11];
	char *check_code = (char *)malloc(sizeof(char)*10);
	memset(check_code, 0, sizeof(char)*10);
    while(i < 3)
    {
		strcpy( check_code, get_rand_str(4));
		printf(" %s  ", check_code);
    	scanf("%s", check);
    	getchar();
    	if( strcmp(check, check_code) == 0 )
    	{        
    		flag = 1;
     		break;
		}
		if(flag == 0)
		{
			printf(PURPLE"验证码输入错误, 请检查大小写!!!\n"NONE);
		}
		i++;
	}
	if(i == 3)
	{
		printf(BLUE"验证码输入错误3次, 自动退出系统!!!\n"NONE);
		exit(1);
	}
	free(check_code);
	check_code = NULL;
	return flag;
}

//模拟与服务器连接函数, 动态打印>>
void printdot()
{
	int i = 3;
	while(i)
	{
		printf(L_CYAN" >> >> "NONE);
		fflush(stdout);
		i--;
		usleep(500000);
	}
	printf("\n\n");
}

//获取当前系统时间
char * gettime()
{
	char *systime = (char *)malloc(sizeof(char)*30);
	char year[20], mon[10], day[10], hour[10], min[10], sec[10];
	time_t rawtime;
	struct tm *tm;
	time ( &rawtime );
	tm = localtime ( &rawtime );
	sprintf(year, "%d", tm->tm_year+1900);
	if( tm->tm_mon + 1 < 10)
		sprintf(mon, "0%d", tm->tm_mon+1);
	else
		sprintf(mon, "%d", tm->tm_mon+1);
	if( tm->tm_mday  < 10)
		sprintf(day, "0%d", tm->tm_mday);
	else
		sprintf(day, "%d", tm->tm_mday);
	if( tm->tm_hour < 10)
		sprintf(hour, "0%d", tm->tm_hour);
	else
		sprintf(hour, "%d", tm->tm_hour);
	if( tm->tm_min < 10)
		sprintf(min, "0%d", tm->tm_min);
	else
		sprintf(min, "%d", tm->tm_min);
	if( tm->tm_sec < 10)
		sprintf(sec, "0%d", tm->tm_sec);
	else
		sprintf(sec, "%d", tm->tm_sec);
	sprintf(systime, "%s-%s-%s-%s:%s:%s", year, mon, day, hour, min, sec);//printf("systime = %s\n", systime);
	return systime;
}

//判断分配空间是否成功，成功继续，不成功退出系统
void judge_allocate(STNODE *p)
{
	if(p == NULL)
	{
		printf(RED"空间分配失败，退出系统!!!\n"NONE);
		exit(-1);
	}
	else
		return;
}

/**********************************************************
功能:动态生成指针节点，尾插法。辅助read_file_use_fscanf函数的
使用:在read_file_use_fscanf函数中调用
传入参数:STNODE * 的头指针和 PERSONINFO people
返回值:void, 对地址进行操作，无须返回头节点
**********************************************************/

void generate_node(PERSONINFO people, STNODE *head)
{
	STNODE *p = (STNODE *)malloc(sizeof(STNODE));//1-1创建一个新结点p
    STNODE *tmp = head;
    while(tmp->next != NULL)  //将指针移动到链表的尾部，即最后一个元素的地方, 做尾插法操作
    	tmp = tmp->next;
    tmp->next = p;
    p->person = people;
    p->next = NULL;
	return ;
}

void generate_node_for_login(LOGMES people, Login_STNODE *head)
{
	Login_STNODE *p = (Login_STNODE *)malloc(sizeof(Login_STNODE));//1-1创建一个新结点p
    Login_STNODE *tmp = head;
    while(tmp->next != NULL)  //将指针移动到链表的尾部，即最后一个元素的地方, 做尾插法操作
    	tmp = tmp->next;
    tmp->next = p;
    p->person1 = people;
    p->next = NULL;
	return ;
}

/**********************************************************
功能:使用尾插法将查找到的信息的节点存入另外一个链表中
使用:在函数中调用
传入参数:STNODE * 的头指针和 STNODE *p
返回值:void, 对地址进行操作，无须返回头节点
**********************************************************/

void copy_node(STNODE *q, STNODE *head)
{
	STNODE *p = (STNODE *)malloc(sizeof(STNODE));//1-1创建一个新结点p
    STNODE *tmp = head;
    while(tmp->next != NULL)  //将指针移动到链表的尾部，即最后一个元素的地方, 做尾插法操作
    {	
    	tmp = tmp->next;
	}
    tmp->next = p;
    p->person = q->person;
    p->next = NULL;
	return ;
}

//文件判空函数
int jugde_file_isEmpty(char filename[25])
{
    int filepos = 0;
    FILE *file = fopen(filename, "rt");
    if(file == NULL)
    {
        printf("打开文件%s出错！\n", filename);
        exit(0);
    }
    fseek(file, 0, SEEK_END);//将文件指针放到文件尾部
    filepos = ftell(file);//报告文件距离文件开头的位移量，如果为0，则表示文件为空
    if(filepos == 0)
    {
    	fclose(file);
    	file = NULL;
        return 1;
    }
    else
    {
    	fclose(file);
    	file = NULL;
        return 0;
    }
}

/****************************************************
功能:使用fscanf函数读取文件，辅助readfiletolist函数的
使用:在readfiletolist函数的调用
传入参数:要读取的文件名和STNODE * 的头指针
返回值:void
*****************************************************/

void read_file_use_fscanf(char filename[30], STNODE *head)
{
	FILE *file = fopen(filename, "rb");
	PERSONINFO people;
	if(file == NULL)
    {
        printf("\033[;31m 文件(%s)打开错误!!\033[0m\n", filename);
        exit(0);
    }
    int flag = jugde_file_isEmpty(filename);
	while(!feof(file) && (!flag))
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
        	people.addtime);//从文件读入记录
        generate_node(people, head);//利用尾插法将文件中读取的信息临时存储在链表中
    }//end of while
    fclose(file);
    file = NULL;
}

//读信息到登录表中，从登录表中获取上次登录时间和次数
void  read_login_table(char filename[], Login_STNODE *head)
{
	FILE *file = fopen(filename, "rb");
	LOGMES people;
	if(file == NULL)
    {
        printf("\033[;31m 文件(%s)打开错误!!\033[0m\n", filename);
        exit(0);
    }
    int flag = jugde_file_isEmpty(filename);
	while(!feof(file) && (!flag))
    {
        fscanf(file, "%d %s %s %d %s\n", 
        	&people.id, 
        	people.name, 
        	people.passwd, 
        	&people.logincounts, 
        	people.lastlogintime
        	);//从文件读入记录
    	generate_node_for_login(people, head);
    }//end of while
    fclose(file);
    file = NULL;
}

/****************************************************
功能:能够实现读取文件的内容到动态链表中
使用:在管理员登录成功后调用，用来获取通讯录的信息
传入参数:char filename[30], 要读取的文件名
返回值:返回STNODE * 的头指针, 避免使用全局的头指针
*****************************************************/

STNODE * readfiletolist(char filename[30])
{
	STNODE *head = (STNODE *)malloc(sizeof(STNODE));
	head->next = NULL;
	read_file_use_fscanf(filename, head);
    return head;
}

Login_STNODE * readfiletolist_for_login(char filename[30])
{
	Login_STNODE *head = (Login_STNODE *)malloc(sizeof(Login_STNODE));
	head->next = NULL;
	read_login_table(filename, head);
    return head;
}

/*************************************
功能:销毁链表---砍头法
使用:在退出系统时调用, 回收系统资源
传入参数:STNODE *head
**************************************/

void Destroy_Linklist(STNODE *head)
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
	for(p; p != NULL;p = p->next)     //按编号升序排列
	{
		for(q = p->next; q != NULL; q = q->next)
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
	for(p; p != NULL; p = p->next)     //按编号降序排列
	{
		for(q = p->next; q != NULL; q = q->next)
			if(p->person.id<q->person.id)
			{
				tmp = p->person;
				p->person = q->person;
				q->person = tmp;
			}
	}
}

//将id编号存入整形数组中
void get_id_to_array(STNODE *head, int a[])
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
void array_sort_small_to_big(int a[], int n)
{
	int i, j, temp;
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
	int id = 1000;
	if(head->next == NULL)
	{
		return id;
	}
	int len = Get_Lines(head);            //获取记录条数
	int Lenarry[len];                    //记录条数作为数组长度
	get_id_to_array(head, Lenarry);       //将id存入数组中来
	array_sort_small_to_big(Lenarry, len);//进行一轮冒泡排序
	int i = 0;            //遍历生成第一个未使用的最小的id编号
	for(i = 0; i < len ; i++)
	{
		if(id == Lenarry[i])
		{
			id++;
		}
		else
		{//printf("%d\n", id);
			break;
		}
	}
	return id;
}

//处理键盘输入字符的函数，返回值为int型的
int input_digit(char li, char left, char right)
{
	char ch[50];
	//printf("请输入操作选项：%c 到 %c之间的数字!!\n", left, right);
	do
	{	
		fgets(ch, 49, stdin);
		li = ch[0];
		rewind(stdin);/*清空键盘缓冲区里的无用字符*/
		if(!(li >= left && li <= right))
			printf("\033[;31m您输入的操作选项有误，请重新输入!!\033[0m\n");
	}
	while(!(li >= left && li <= right));
	return li-'0';
}

//释放链表的需要删除的节点
STNODE * Delete_Node(STNODE *head, STNODE *temp)
{
	STNODE *s = head;
	STNODE *t = s->next;//printf("DeleteNode \n");
	while( t != NULL)
	{
		if(t == temp)   //如果找到相同地址就释放掉
		{
			s->next = t->next;
			free(t);
			t = NULL;
			return head;
		}
		else
		{
			s = t;      //把s往后挪一位
			t = s->next;//把t也往后挪
		}
	}
	return head;
}

//查询结果打印函数
void print_name_result(STNODE *head, int flag, int choice, char name[])
{
	if(flag == 0)
	{
		printf(GREEN"联系人中没有姓名叫 %s 的人!!!\n\n"NONE, name);
	}
	if(flag >= 1)
	{
		ShowInfo_In_order(head);
	}
	return ; 
}

//查询结果打印函数
void print_id_result(STNODE *head, int flag, int choice, int id)
{
	//printf("wai flag = %d\n", flag);
	if(flag == 0)
	{
		printf(GREEN"联系人中没有编号是 %d 的人!!!\n\n "NONE, id);
	}
	if(flag >= 1)
	{
		ShowInfo_In_order(head);
	}
	return ; 
}

//查询结果打印函数
void print_tel_result(STNODE *head, int flag, int choice, char tel[])
{
	//printf("wai flag = %d\n", flag);
	if(flag == 0)
	{
		printf(GREEN"联系人中没有号码是 %s 的人!!!\n\n "NONE, tel);
	}
	if(flag >= 1)
	{
		ShowInfo_In_order(head);
	}
	return ; 
}

//按姓名查找的函数, flag作为查找的依据，用来提示是否存在这个查询的姓名
STNODE *search_name_genratelinkst(STNODE *head, char pname[30], int *flag)
{
	STNODE *head1 = (STNODE *)malloc(sizeof(STNODE));
	head1->next = NULL;
	STNODE *p = head->next;
	while(p != NULL)
	{
		if(strcmp(p->person.name, pname) == 0)
		{
			copy_node(p, head1);//利用尾插法将节点的信息临时存储在链表中
			(*flag)++;// 传地址加的时候使用*flag++, 不能使用flag++，会出错的
		}
		p = p->next;
	}
	return head1;
}

//按号码查找的函数, flag作为查找的依据，用来提示是否存在这个查询的号码
STNODE *search_telephone_genratelinkst(STNODE *head, char tel[30], int *flag)
{
	STNODE *head1 = (STNODE *)malloc(sizeof(STNODE));
	head1->next = NULL;
	STNODE *p = head->next;
	while(p != NULL)
	{
		if(strcmp(p->person.telephone, tel) == 0)
		{
			copy_node(p, head1);//利用尾插法将节点的信息临时存储在链表中
			(*flag)++;// 传地址加的时候使用*flag++, 不能使用flag++，会出错的
			break;
		}
		p = p->next;
	}
	return head1;
}

//按编号查找的函数, flag作为查找的依据，用来提示是否存在这个查询的编号
STNODE *search_id_genratelinkst(STNODE *head, int id, int *flag)
{
	STNODE *head1 = (STNODE *)malloc(sizeof(STNODE));
	head1->next = NULL;
	STNODE *p = head->next;//printf("123\n");
	while(p != NULL)
	{//printf("serach id \n");
		if(p->person.id == id)
		{
			copy_node(p, head1);//利用尾插法将节点的信息临时存储在链表中
			(*flag)++;
			break;
		}
		p = p->next;
	}
	//printf("search_id_genratelinkst pass!\n");
	return head1;
}

/**********************************************
功能:按姓名查找并返回找到了的信息的地址
使用:在删除, 修改, 查找中都需要调用
传入参数:STNODE *head, char pname[30]
返回值：返回的是查找到的节点的地址，未找到返回NULL
**********************************************/

void show_modify_id(STNODE *head, int id, int choice)
{
	STNODE *head1 = NULL;
    int flag = 0;//printf("234 search_id_genratelinkst rukou\n");
 	head1 = search_id_genratelinkst(head, id, &flag);
	print_id_result(head1, flag, choice, id);	
}

/**********************************************
功能:按姓名查找并返回找到了的信息的地址
使用:在删除, 修改, 查找中都需要调用
传入参数:STNODE *head, char pname[30]
返回值：返回的是查找到的节点的地址，未找到返回NULL
**********************************************/

int show_modify_name(STNODE *head, char name[], int choice)
{
	STNODE *head1 = NULL;
    char ch[50];
    int flag = 0;
	head1 = search_name_genratelinkst(head, name, &flag);
    print_name_result(head1, flag, choice, name);
    return flag;
}

/**********************************************
功能:按姓名查找并返回找到了的信息的地址
使用:在修改联系人信息的函数之中需要调用
传入参数:STNODE *head, char pname[30]
返回值：返回的是查找到的节点的地址，未找到返回NULL
**********************************************/

STNODE *find_name(STNODE *head, char pname[30])
{
    STNODE *p = head->next;
    while(p != NULL)
    {
    	if(strcmp(p->person.name, pname) == 0)
		{
			return p;
		}
    	p = p->next;
    }
	return NULL;
}

/**********************************************
功能:按编号查找并返回地址
使用:修改联系人信息函数之中需要调用
传入参数:STNODE *head, int id
返回值：返回的是查找到的节点的地址，未找到返回NULL
**********************************************/

STNODE *find_ID(STNODE *head, int id)
{
    STNODE *p = head->next;
    while(p != NULL)
    {
    	if(p->person.id == id)
		{
			return p;
		}
    	p = p->next;
    }
	return NULL;
}

//按编号修改联系人的信息
STNODE *modify_id_info(STNODE *head, int id, int choice)
{
	STNODE *tmp = NULL;
	char ch;
	tmp = find_ID(head, id);
	show_modify_id(head, id, choice);
	if(tmp == NULL)
		return head;
	int confirm = 0;
	printf("\033[;31m是否确认修改? 1:表示确认修改 0:表示不修改!!!\033[0m\n");
	confirm = input_digit(ch, '0', '1');
	if(confirm == 1)
	{
		modify_ui(tmp);
		printf("\n修改联系人成功！！！\n");
		return head;
	}
	else
		return head;	
}

//处理出现同名的情况
STNODE * dealwith_same_name(STNODE *head, int flagnum, char name[30])
{
	int id;
	STNODE *tmp = NULL;
	if( flagnum == 1)
	{
		tmp = find_name(head, name);
		return tmp ;
	}
	if(flagnum >= 2)
	{	
		printf("\n因为出现重名情况，请输入编号进行操作 !!!\n");
		printf("输入联系人编号：");
		scanf("%d", &id);
		getchar();
		tmp = find_ID(head, id);
		if(tmp == NULL)
		{
			printf("没有姓名叫 %s 且编号为 %d 的联系人, 请确认后输入!!!\n", name, id);
			return tmp;
		}
		return tmp ;
	}
	if( tmp == NULL)
	{
		return tmp;
	} 
}

//查找用于删除的节点的地址
STNODE * find_for_delete(STNODE *head)
{
    STNODE *q=NULL;
    char name[30];
    char ch;
	int choice, id, flagnum;
    printf("请选择删除方式 1：按姓名删除  2：按编号删除\n");
    choice =  input_digit(ch, '1', '2');//等待键盘输入是一个数字1~2否则就一直等待用户输入
    switch(choice)
    {
    	case 1:
    		printf("\033[;34m请输入姓名\033[0m:");
			scanf("%s", name);
			getchar();
			flagnum = show_modify_name(head, name, choice);
    		q = dealwith_same_name(head, flagnum, name);
    		return q;
    		break;
		case 2:
			printf("\033[;34m请输入编号\033[0m:");
			scanf("%d", &id);
			getchar();//printf("id = %d\n", id);
			show_modify_id(head, id, choice);//printf("show_modify_id pass\n"); 
			q = find_ID(head, id);
			return q;
    		break;
    }
}

//写信息到登录表中，从登录表中获取上次登录时间和次数
void write_file(char filename[], Login_STNODE *head)
{
	FILE *file = fopen(filename, "wb");
	Login_STNODE *p = head->next;
	while(p != NULL)
	{
		fprintf(file, "%-20d %-17s %-17s %-17d %-17s \n", 
			p->person1.id, 
			p->person1.name, 
        	p->person1.passwd, 
        	p->person1.logincounts, 
        	p->person1.lastlogintime
        	);//写文件操作
        p = p->next;
    }
    fclose(file);
    file = NULL;
	return;
}

//登录时提示上次登录时间和登录次数, 首次登录提示首次登录
void login_inf(int id, char name[30], char pass[30])
{
	LOGMES person; 
	char stime[30] ;
	strcpy(stime, gettime());                                    //获取系统时间函数调用
	Login_STNODE *head = readfiletolist_for_login("logintable.txt");//从文件中读取登录人员的信息
	strcpy(person.lastlogintime, stime);
	Login_STNODE *p = head->next;
	printf(GREEN" 正在登录"NONE);
	printdot();
	while(p != NULL)
	{
		if((p->person1.logincounts == 0) && ( p->person1.id == id ) )
		{
			p->person1.logincounts ++;
			printf("\n\n\t%s\033[47;31m您好!您是首次登录!欢迎使用通讯录管理系统!!!\033[0m\n", name);
			strcpy(p->person1.lastlogintime, stime);//修改以前登录过的人登录时间和登录次数并且随后进行保存操作
			write_file("logintable.txt", head);
			sleep(1);
			return;
		}
		if((p->person1.logincounts > 0) && ( p->person1.id == id ) )
		{
			p->person1.logincounts ++;
			printf("\t%s\033[47;31m您好!您上次登录时间是\033[0m%s, \033[47;31m第\033[0m%d\033[47;31m次登录, 欢迎您的到来!\033[0m\n", p->person1.name, p->person1.lastlogintime, p->person1.logincounts);
			strcpy(p->person1.lastlogintime, stime);//修改以前登录过的人登录时间和登录次数并且随后进行保存操作
			write_file("logintable.txt", head);
			sleep(1);
			return;
		}
		p = p->next;
	}
}

//将链表中的信息保存到另一个链表中来
STNODE * save_node(STNODE *head)
{
	STNODE *new_head = (STNODE *)malloc(sizeof(STNODE));//1-1创建一个新结点p
	judge_allocate(new_head);
	new_head->next = NULL;
    STNODE *temp = head->next;
    while( temp != NULL)
    {
    	STNODE *p = (STNODE *)malloc(sizeof(STNODE));//1-1创建一个新结点p
    	judge_allocate(p);                            //判生成的结点是否为空，空就退出系统
    	STNODE *tmp = new_head;
    	while(tmp->next != NULL)  //将指针移动到链表的尾部，即最后一个元素的地方, 做尾插法操作
    		tmp = tmp->next;
    	tmp->next = p;
    	p->person = temp->person;
    	p->next = NULL;
    	temp = temp->next;
    }
    return new_head;
}


//显示联系人的三种方式，按编号从小到大，从大到小，按文件顺序
void showinfo_use_three_kinds(STNODE *head)
{
	int choice;
	char ch;
	printf("0:按添加顺序显示  1:按编号从小到大显示  2:按编号从大到小显示:");
	choice = input_digit(ch, '0', '2');
	switch(choice)
	{
		case 0:
			ShowInfo_In_order(head);
			break;
		case 1:
			linksort_small_to_big(head);
			ShowInfo_In_order(head);
			break;
		case 2:
			linksort_big_to_small(head);
			ShowInfo_In_order(head);
			break;
	}
}

void copy_group_node(STNODE *q)
{
	STNODE *p = (STNODE *)malloc(sizeof(STNODE));//1-1创建一个新结点p
	STNODE *head = (STNODE *)malloc(sizeof(STNODE));//1-1创建一个新结点p
	head->next = NULL;
    STNODE *tmp = head;//printf("enter copy_node\n");printf("head = %p\n", head);printf("tmp = %p\n", tmp);
    while(tmp->next != NULL)  //将指针移动到链表的尾部，即最后一个元素的地方, 做尾插法操作
    {	
    	tmp = tmp->next;
    }
    tmp->next = p;
    p->person = q->person;
    p->next = NULL;
	return ;
}

//处理群组显示联系人的信息
STNODE * deal_dif_groups(STNODE *head, char groups[])
{
	STNODE *p = head->next;
	STNODE *head1 = (STNODE *)malloc(sizeof(STNODE));
	head1->next = NULL;
	judge_allocate(head1);
	while( p != NULL)
	{
		if(strcmp(p->person.group, groups) == 0)
		{
			copy_node(p, head1);
		}
		p = p->next;
	}
	return head1;
}

//按群组显示联系人的信息"家人" "同学" "同事" "朋友"
void show_dif_groups(STNODE *head)
{
	STNODE *p = NULL;
	STNODE *q = NULL;
	STNODE *s = NULL;
	STNODE *t = NULL;
	int choice;
	char ch;
	printf("请选择按群组显示方式  0:家人  1:同学  2:同事  3:朋友  ");
	choice = input_digit(ch, '0', '3');
	switch(choice)
	{
		case 0:
			p = deal_dif_groups(head, "家人");
			ShowInfo_In_order(p);
			break;
		case 1:
			q = deal_dif_groups(head, "同学");
			ShowInfo_In_order(q);
			break;
		case 2:
			s = deal_dif_groups(head, "同事");
			ShowInfo_In_order(s);
			break;
		case 3:
			t = deal_dif_groups(head, "朋友");
			ShowInfo_In_order(t);
			break;
	}
}

/****************************************************
功能：保存删除人员的信息
使用：在删除之前进行保存
****************************************************/
void save_delete_info(STNODE *p)
{
	FILE *file;
	file = fopen("Deletepersoninfo.txt", "at");
	if(file == NULL)
	{
		printf("打开文件出错\n");
		return;
	}
	fprintf(file, "%-8d %-20s %-10s %-10s %-15s %-15s %-10s %-15s %15s\n", 
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

//保存文件的函数
void save_file(STNODE *head, char filename[30])
{
	STNODE *p = head->next;
	FILE *fp = fopen(filename, "wb");
	if(fp == NULL)
	{
		printf("\033[;31m打开文件%s出错\033[0m\n", filename);
		return ;
	}
	while(p != NULL)
	{	
		fprintf(fp, "%-8d %-20s %-10s %-10s %-15s %-15s %-10s %-15s %15s\n", 
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

//是否修改登录用户的相关信息
void comfirm_modify_user_info(Login_STNODE *tmp)
{
	char ch;
	int confirm = 0;
	printf("\033[;31m是否确认修改? 1:表示确认修改 0:表示不修改!!\033[0m\n");
	confirm = input_digit(ch, '0', '1');
	if(confirm == 1)
	{
		printf("\033[;34m请输入修改后的姓名：\033[0m");
		scanf("%s", tmp->person1.name);
		printf("\033[;34m请输入修改后的密码：\033[0m");
		scanf("%s", tmp->person1.passwd);
		printf("用户信息修改成功！\n");
	}
	return ;
}

//修改用户名和密码的函数, 传入的head形参是由ui层再由main传过来的登录表中的head头指针
void modify_uname_passwd(Login_STNODE *head, int idnum)
{
	Login_STNODE *p = head->next;
	Login_STNODE *tmp = NULL;
	while(p != NULL)
	{
		if(p->person1.id == idnum)
		{
			tmp = p;
			break;
		}
		p = p->next;
	}
	comfirm_modify_user_info(tmp);
	write_file("logintable.txt", head);
	return ;
}

//显示删除了的人员的信息
void show_delete_person_info()
{
	STNODE * head2 = NULL;
	head2 = readfiletolist("Deletepersoninfo.txt");
	ShowInfo_In_order(head2);
	return ;
}

//将fgets函数多存入的一个\n处理掉
void you_hua(char *p)
{
	while(*p != '\0')
	{	
		if(*p == '\n')
		{
		 	*p ='\0';
		 	break;
		}	
		p++;
	}
	return;
}

//判断出现非法字符串如年龄中出现字母和汉字等情况
int judge_islegal(char *q)
{
	int flag = 0;//printf("judge_islegal = %s\n", q);
	int len = 0;
	char *p = q;
	if(*p == '\0')
	{	
		flag = 1;
		return flag ;
	}
	while(*q != '\0')
	{
		
		if(*q >='0' && *q <= '9')
		{
			flag = 0;
		}
		else
		{
			flag = 1;
			return flag;
		}
		q++;
	}
	return flag;
}

//返回电话号码的位数
int return_len(char *p)
{
	int len = 0;
	int flag = 0;
	while(*p != '\0')
	{
		len ++;
		p++;
	}//printf("len = %d\n", len);
	if(len == 7 || len == 8 || len == 11)
	{
		return flag;
	}
	else
	{
		flag = 1;  //号码位数不对
		return flag;
	}
}

//判断输入联系方式时是否合法的函数
void string_to_int(char str[])
{
	int id = 0;
	int len;
	int flag;
	do
	{
		fgets(str, 30, stdin);
		you_hua(str);
		flag = judge_islegal(str);
		len = return_len(str);
		if(flag)
		{
			printf(CYAN"不能包含数字以外的其他字符，请重新输入!!!\n"NONE);
		}
		if(len)
		{
			printf(CYAN"号码的位数不对, 一般为7位，8位或者11位，请重新输入!!!\n"NONE);
		}
	}while(flag || len );
}

//将字符串转换成整形的数字
int return_int(char *p)
{
	int num = 0;
	int flag = 0;
	while(*p != '\0')
	{
		if(*p >= '0' && *p <= '9')
		{
			num = num * 10 + *p-'0';
			p ++;
		}
		else
		{
			num = 0;
			break;
		}
	}
	if(num > 90)
	{
		flag = 1;
		return flag;
	}
	if(num > 0 && num <= 90)
	{
		return 0;
	}
	if(num == 0) 
	{
		return -1;
	}
}

//判断年龄的合法性函数
void age_legal(char str[])
{
	int len = 0;
	int flag;
	do
	{
		fgets(str, 30, stdin);
		you_hua(str);
		flag = judge_islegal(str);
		len = return_int(str);
		if(len == 1)
		{
			printf(RED"年龄过大, 不太符合实际情况!!!\n"NONE);
		}
		if(len == -1)
		{
			printf(BLUE"不能包含数字以外的其他字符，请重新输入!!!\n"NONE);
		}
	}while(flag || len );
}

//群组选择
void choose_group(char group[])
{
	char ch;
	int choose_num ;
	printf("请输入群组编号, 1:家人 2:同学 3:同事 4:朋友");
	printf("  ");
	choose_num = input_digit(ch, '1', '4');
	if(choose_num == 1)
	{
		strcpy(group, "家人");
	}
	if(choose_num == 2)
	{
		strcpy(group, "同学");
	}
	if(choose_num == 3)
	{
		strcpy(group, "同事");
	}
	if(choose_num == 4)
	{
		strcpy(group, "朋友");
	}
}

//邮箱格式判别函数, 判断字符串中是否存在 ".", com, cn, @等符号
int check_com_cn(char *s, char *t)
{
	int n, aflag = 0, dotflag = 0;
	char *p, *r;
	n = 0;
	p = s;
	r = t;
	while(*p != '\0')
	{
		if(*r == *p)
		{
			r++;
			if(*r == '\0')
			{
				n++;
				r = t;//r=&t[0];//当前的一轮比较完之后, r重新指向t的首地址进行下一轮比较
			}
		}
		if(*p == '.')
		{
			dotflag ++;
		}
		if(*p == '@')
		{
			aflag ++;
		}
		p++;
	}
	if(n >= 1 && dotflag >= 1 && aflag >= 1)
		return 0; //返回0邮箱格式合法
	else 
		return 1;//返回1邮箱格式不合法，后续循环
}

//检查邮箱的合法性
void check_mails(char str[])
{
	int com_flag = 0, cn_flag = 0;
	int flag = 0;
	do
	{
		fgets(str, 30, stdin);
		you_hua(str);
		com_flag = check_com_cn(str, "com");
		cn_flag = check_com_cn(str, "cn");
		if(com_flag && cn_flag)
		{
			printf("邮箱格式不正确，应含有@ . com或cn, 请重新输入!!!\n");
		}
	}while(com_flag && cn_flag);
}

/****************************************************
功能:自己定义的计算包含中文字符的字符串的长度
使用:在GainColumnMaxLength函数中用
传入参数:char *p
返回值:int 类型的字符串长度
*****************************************************/
//求字符串长度的函数，这是解决问题的关键，可以简化思路
int My_Strlen(char *p)
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
void Init_Aarry(char *name[], char *str[], int *length[], int a, int n)
{
	int i = 0;
	for(i = 0;i < a*n; i++)
	{
		name[i] = (char *)malloc(sizeof(char *)*100);
		memset(name[i], 0, sizeof(char *)*100);
		length[i] = (int *)malloc(sizeof(int *)*20);
	}
	for(i = 0;i < a; i++)
	{
		str[i] = (char *)malloc(sizeof(char *)*300);
		memset(str[i], 0, sizeof(char *)*300);
	}
}

//整齐打印文件内容的整合函数
void ShowInfo_In_order(STNODE *head)
{
	int a = 1 + Get_Lines(head);//读取员工信息并且存入字符串数组中来, 返回记录的行数
	int n = 9;
	char *name[a*n];     //定义二维字符串数组
	char *str[a];        //定义二位字符串数组
	int *length[a*n];    //定义一个计数的数组
	int max[n];          //存储每一列最大值的
	int erwei[a][n];     //二维整形数组, 存储空格数目的
	Init_Aarry(name, str, length, a, n);  //初始化数组，分配空间
	int i = Append_Column(name);      //将列名加入字符串数组中
	ReadInfo_toArray(name, i, head);    //读取链表信息到数组中来
	Gain_ColumnMaxLength(name, length, max, erwei, a*n, n);//同下
	Get_Max(erwei, length, max, a*n, n);      //获取每一列的最大宽度
	Add_Blank(name, length, a*n, n);        //不足的填补空格使之居中
	PrintInfo_Into_Table(name, str, max, a, n);//打印函数调用
	Free_Space(name, str, length, a, a*n); 
	//回收系统资源函数, 使用时发现打印多次时调用这个函数会出现乱码，因此就不调用了，让系统自行回收资源
}

//获取记录的条数
int Get_Lines(STNODE *head)
{
	
	int a=0;
	STNODE *p = head->next;
	while(p != NULL)
	{
		a++;
		p =  p->next;
	}//printf("a = %d\n", a);
	return a;
}

//将列名存入数组之中来，再打印文件信息
int Append_Column(char *array[])
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

//int类型的转化成字符串的类型的函数
char * Int_Form_String(int num)
{
	char *s = malloc(sizeof(char)* 30);
	memset(s, 0, sizeof(char)* 30);
	sprintf(s, "%d", num);
	return s;
}

//读取动态链表中的信息并且存入字符串数组中来
void ReadInfo_toArray(char *array[], int i, STNODE *head)
{
	STNODE *p = head->next;
	while(p != NULL)
	{
		
		{
			strcpy(array[i], Int_Form_String(p->person.id)); i++;
			strcpy(array[i], p->person.name);  i++;
			strcpy(array[i], p->person.sex);  i++;
			strcpy(array[i], p->person.age);  i++;
			strcpy(array[i], p->person.telephone); i++;
			strcpy(array[i], p->person.address); i++;
			strcpy(array[i], p->person.group); i++;
			strcpy(array[i], p->person.mails); i++;
			strcpy(array[i], p->person.addtime); i++;
		}     
		p = p->next;
	}
}

//获取数组的每一列的最大宽度
void Gain_ColumnMaxLength(char *array[], int *length[], int max[], int erwei[][9], int c, int n)
{
	int i, j;
	
	for(i = 0;i < c; i++)
	{
		*length[i] = My_Strlen(array[i]);	
	}

	for(i = 0; i < c/n; i++)
		for(j = 0; j < n; j++)
		{
			erwei[i][j] = *length[i*n+j];//一维数组转二维数组
		}
}

//获取数组每一列的最大值函数
int Get_Max(int erwei[][9], int *length[], int max[], int c, int n)
{
	int big, i = 0, j = 0;
	//获取数组每一列的最大值big
	for(j = 0; j < n; j++)
	{
		big = erwei[0][j];
		
		for(i = 0; i < c/n; i++)
		{ 
			if(big < erwei[i][j])  //i, j不要写反了列作为外循环次数
			{	
				big = erwei[i][j];
			}
		}
		max[j] = big;//printf("max[%d]=%d\n", j, max[j]);
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

//逐个遍历不够长度的填补空格, 其中n表示列的数量，c表示数组的长度, 使得字符串能够居中
void Add_Blank(char *array[], int *length[], int c, int n)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int m = 0;
	char blank[200];
	for( i = 0; i < c; i++)
	{
		memset(blank, 0, 200);//因为strcat连接字符串的，不清空的话空格会越来越多
		if((*length[i] + 4) % 2 == 0)   //处理居中的方法，分奇数和偶数个空格数目进行
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
void Linking(char *array[], char *str[], int a, int n)
{
	int i = 0;
	int j = 0;
	for(i = 0; i < a; i++)
	{
		for(j = 0; j < n; j++)
		{
			strcat(str[i], "|");
			strcat(str[i], array[i*n+j]);
		}
		sprintf(str[i], "%s|", str[i]);
	}
}

//整齐打印数组中的内容，呈现表格, 其中n表示列的数量，a表示记录的条数，也就是行数
void PrintInfo_Into_Table(char *array[], char *str[], int max[], int a, int n)
{
	int i = 0;
	int j = 0;
	int k = 0;
	Linking(array, str, a, n);
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
		if(i == 0)
			printf(L_RED"\n%s\n"NONE, str[i]);
		else
			printf("\n%s\n", str[i]);
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
void Free_Space(char *name[], char *str[], int *length[], int a, int n)
{	
	int i = 0;
	for(i = 0;i < n; i++)
	{
		free(name[i]);
		name[i] = NULL;
		free(length[i]);
		length[i] = NULL;
	}
	for(i = 0;i < a; i++)
	{
		memset(str[i], 0, sizeof(char *)*300);
		free(str[i]);
		str[i] = NULL;
	}
}









