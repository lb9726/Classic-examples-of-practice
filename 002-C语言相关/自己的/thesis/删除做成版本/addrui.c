#include"addrui.h"

int user_loginUI()
{
	return 0 ;
}

//添加联系人界面
PERSONINFO add_info(STNODE *head)
{
	PERSONINFO people;
	printf("**********************\n");
	printf("*     添加联系人     *\n");
	printf("**********************\n");
	people.id = get_min_id(head);
	printf("姓    名:");
	scanf("%s",people.name);
	printf("性    别:");
	scanf("%s",people.sex);
	printf("年    龄:");
	scanf("%s",people.age);
	printf("联系电话:");
	scanf("%s",people.telephone);
	printf("家庭住址:");
	scanf("%s",people.address);
	printf("群    组:");
	scanf("%s",people.group);
	printf("邮    箱:");
	scanf("%s",people.mails);
	strcpy(people.addtime,gettime());
	return people;
}

//添加联系人主函数
STNODE *add_person_infoUI(STNODE *head)
{	
	PERSONINFO peo = add_info(head);
	generate_node(peo,head);//利用尾插法人员的信息临时存储在链表中
	return head;
}

//查询结果打印函数
void print_name_result(STNODE *head,int flag,int choice,char name[])
{
	if(flag == 0)
	{
		printf("联系人中没有姓名叫 %s 的人!!!\n\n",name);
	}
	if(flag >= 1)
	{
		ShowInfo_In_order(head);
	}
	return ; 
}

//查询结果打印函数
void print_id_result(STNODE *head,int flag,int choice,int id)
{
	//printf("wai flag = %d\n",flag);
	if(flag == 0)
	{
		printf("联系人中没有编号是 %d 的人!!!\n\n",id);
	}
	if(flag >= 1)
	{//printf("flag = %d\n",flag);
		ShowInfo_In_order(head);
	}
	//printf("print_id_result\n");
	return ; 
}

//按姓名查找的函数,flag作为查找的依据，用来提示是否存在这个查询的姓名
STNODE *search_name_genratelinkst(STNODE *head,char pname[30],int *flag)
{
	STNODE *head1 = (STNODE *)malloc(sizeof(STNODE));
	head1->next = NULL;
	STNODE *p = head->next;
	while(p != NULL)
	{
		if(strcmp(p->person.name,pname) == 0)
		{
			copy_node(p,head1);//利用尾插法将节点的信息临时存储在链表中
			(*flag)++;// 传地址加的时候使用*flag++,不能使用flag++，会出错的
		}
		p = p->next;
	}
	return head1;
}

//按编号查找的函数,flag作为查找的依据，用来提示是否存在这个查询的编号
STNODE *search_id_genratelinkst(STNODE *head,int id,int *flag)
{
	STNODE *head1 = (STNODE *)malloc(sizeof(STNODE));
	head1->next = NULL;
	STNODE *p = head->next;//printf("123\n");
	while(p != NULL)
	{//printf("serach id \n");
		if(p->person.id == id)
		{
			copy_node(p,head1);//利用尾插法将节点的信息临时存储在链表中
			(*flag)++;
			break;
		}
		p = p->next;
	}
	//printf("search_id_genratelinkst pass!\n");
	return head1;
}

//查找的主函数：按姓名或编号查询的合并的函数
void find_id_or_name(STNODE *head)
{
	STNODE *head1 = NULL;
	STNODE *head2 = NULL;
    char name[30];
    char ch;
    int flag = 0;
	int choice,id,choice1=1;
	while(choice1)
	{
    	printf("请选择查找方式 1：按姓名查找  2：按编号查找\n");
    	choice = inputdigit(ch,'1','2');//等待键盘输入是一个数字1~2否则就一直等待用户输入
    	switch(choice)
    	{
    		case 1:
    			printf("\033[;34m请输入联系人姓名:\033[0m");
				scanf("%s",name);
    			head1 = search_name_genratelinkst(head,name,&flag);
    			print_name_result(head1,flag,choice,name);
    			flag = 0;
    			break;
			case 2:
				printf("\033[;34m请输入联系人编号:\033[0m");
				scanf("%d",&id);
				head2 = search_id_genratelinkst(head,id,&flag);
				print_id_result(head2,flag,choice,id);	
				flag = 0;
    			break;
    	}//end of switch 
    	printf("\033[;31m是否继续查找? 1:继续 0:不继续 :\033[0m");//printf("ch = %c\n",ch);
    	getchar();//接收上一次输入的回车键消除对本次循环的影响
    	choice1 = inputdigit(ch,'0','1');//等待键盘输入是一个数字0~1否则就一直等待用户输入
    }//end of while 
}

/**********************************************
功能:按姓名查找并返回找到了的信息的地址
使用:在删除,修改,查找中都需要调用
传入参数:STNODE *head,char pname[30]
返回值：返回的是查找到的节点的地址，未找到返回NULL
**********************************************/

void show_modify_id(STNODE *head,int id,int choice)
{
	STNODE *head1 = NULL;
    int flag = 0;//printf("234 search_id_genratelinkst rukou\n");
 	head1 = search_id_genratelinkst(head,id,&flag);
	print_id_result(head1,flag,choice,id);	
}

/**********************************************
功能:按姓名查找并返回找到了的信息的地址
使用:在删除,修改,查找中都需要调用
传入参数:STNODE *head,char pname[30]
返回值：返回的是查找到的节点的地址，未找到返回NULL
**********************************************/

int show_modify_name(STNODE *head,char name[],int choice)
{
	STNODE *head1 = NULL;
    char ch[50];
    int flag = 0;
	head1 = search_name_genratelinkst(head,name,&flag);
    print_name_result(head1,flag,choice,name);
    return flag;
}

/**********************************************
功能:按姓名查找并返回找到了的信息的地址
使用:在删除,修改,查找中都需要调用
传入参数:STNODE *head,char pname[30]
返回值：返回的是查找到的节点的地址，未找到返回NULL
**********************************************/
STNODE *findname(STNODE *head,char pname[30])
{
    STNODE *p = head->next;
    while(p != NULL)
    {
    	if(strcmp(p->person.name,pname) == 0)
		{
			return p;
		}
    	p = p->next;
    }
	return NULL;
}

/**********************************************
功能:按编号查找并返回地址
使用:修改,删除,查找中需要调用
传入参数:STNODE *head,int id
返回值：返回的是查找到的节点的地址，未找到返回NULL
**********************************************/
STNODE *findID(STNODE *head,int id)
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

//修改联系人信息的界面
void modify_ui(STNODE *tmp)
{
	//printf("\033[;36m请输入修改后的编号\033[0m：");
	//scanf("%d",&tmp->person.id);
	printf("\033[;36m请输入修改后的姓名\033[0m：");
	scanf("%s",tmp->person.name);
	printf("\033[;36m请输入修改后的性别\033[0m：");
	scanf("%s",tmp->person.sex);
	printf("\033[;36m请输入修改后的年龄\033[0m：");
	scanf("%s",tmp->person.age);
	printf("\033[;36m请输入修改后的电话\033[0m：");
	scanf("%s",tmp->person.telephone);
	printf("\033[;36m请输入修改后的住址\033[0m：");
	scanf("%s",tmp->person.address);
	printf("\033[;36m请输入修改后的群组\033[0m：");
	scanf("%s",tmp->person.group);
	printf("\033[;36m请输入修改后的邮箱\033[0m：");
	scanf("%s",tmp->person.mails);
	strcpy(tmp->person.addtime,gettime());
	getchar();
}
//按编号修改联系人的信息
STNODE *modify_id_info(STNODE *head,int id,int choice)
{
	STNODE *tmp = NULL;
	char ch;
	tmp = findID(head,id);
	show_modify_id(head,id,choice);
	if(tmp == NULL)
		return head;
	int confirm = 0;
	printf("\033[;31m是否确认修改? 1:表示确认修改 0:表示不修改!!!\033[0m\n");
	confirm = inputdigit(ch,'0','1');
	if(confirm == 1)
	{
		modify_ui(tmp);
		printf("\n修改联系人成功！！！\n");
		return head;
	}
	else
		return head;	
}

//按姓名修改联系人的信息
STNODE *modify_name_info(STNODE *head,char name[],int choice)
{
	STNODE *tmp = NULL;
	char ch;
	int id;
	int confirm = 0;
	int flagnum = show_modify_name(head,name,choice);
	if( flagnum == 1)
	{
		tmp = findname(head,name);
	}
	if(flagnum >= 2)
	{	
		printf("\n因为出现重名情况，请输入编号进行操作 !!!\n");
		printf("输入联系人编号：");
		scanf("%d",&id);
		getchar();
		tmp = findID(head,id);
	}
	if(flagnum >= 2 && tmp == NULL)
	{
		printf("没有姓名叫 %s 且编号为 %d 的联系人,请确认后输入!!!\n",name,id);
		return head;
	}
	if( tmp == NULL)
	{
		return head;
	}
	printf("\033[;31m是否确认修改? 1:表示确认修改 0:表示不修改!!!\033[0m\n");
	confirm = inputdigit(ch,'0','1');
	if(confirm == 1)
	{
		modify_ui(tmp);
		printf("\n修改联系人信息成功！！！\n");
		return head;
	}
	else
		return head;	
}
//修改联系人信息的主函数
STNODE *modify_idorname_main(STNODE *head)
{
    char name[30];
    char ch;
    int flag = 0;
	int choice,id,choice1 = 1;
	while(choice1)
	{
    	printf("请选择修改方式 1：按姓名修改  2：按编号修改\n");
    	choice = inputdigit(ch,'1','2');//等待键盘输入是一个数字1~2否则就一直等待用户输入
    	switch(choice)
    	{
    		case 1:
    			printf("\033[;34m请输入联系人姓名:\033[0m");
				scanf("%s",name);
				getchar();
    			head = modify_name_info(head,name,choice);
    			break;
			case 2:
				printf("\033[;34m请输入联系人编号:\033[0m");
				scanf("%d",&id);
				getchar();
				head = modify_id_info(head,id,choice);
    			break;
    	}//end of switch 
    	printf("\033[;31m是否继续修改? 1:继续 0:不继续 :\033[0m");	
    	choice1 = inputdigit(ch,'0','1');//等待键盘输入是一个数字0~1否则就一直等待用户输入
    }//end of while 
    return head;
}

STNODE * dealwith_same_name(STNODE *head,int flagnum,char name[30])
{
	int id;
	STNODE *tmp = NULL;
	if( flagnum == 1)
	{
		tmp = findname(head,name);
		return tmp ;
	}
	if(flagnum >= 2)
	{	
		printf("\n因为出现重名情况，请输入编号进行操作 !!!\n");
		printf("输入联系人编号：");
		scanf("%d",&id);
		getchar();
		tmp = findID(head,id);
		if(tmp == NULL)
		{
			printf("没有姓名叫 %s 且编号为 %d 的联系人,请确认后输入!!!\n",name,id);
			return tmp;
		}
		return tmp ;
	}
	if( tmp == NULL)
	{
		return tmp;
	} 
}

STNODE * findfordelete(STNODE *head)
{
    STNODE *q=NULL;
    char name[30];
    char ch;
	int choice,id,flagnum;
    printf("请选择删除方式 1：按姓名删除  2：按编号删除\n");
    choice =  inputdigit(ch,'1','2');//等待键盘输入是一个数字1~2否则就一直等待用户输入
    switch(choice)
    {
    	case 1:
    		printf("\033[;34m请输入姓名\033[0m:");
			scanf("%s",name);
			getchar();
			flagnum = show_modify_name(head,name,choice);
    		q = dealwith_same_name(head,flagnum,name);
    		return q;
    		break;
		case 2:
			printf("\033[;34m请输入编号\033[0m:");
			scanf("%d",&id);
			getchar();//printf("id = %d\n",id);
			show_modify_id(head,id,choice);//printf("show_modify_id pass\n"); 
			q = findID(head,id);
			return q;
    		break;
    }
}

STNODE *delete_idorname_main(STNODE *head)
{
	STNODE *t=NULL;
	char ch;
	int confirm=0;
	int choice = 1;
	while(choice)
	{
		t = findfordelete(head);//查找到了要删除的地址
		if(t != NULL)
		{	
			printf("是否确认删除? 1:表示确认删除 0:表示不删除!!! \n");
			confirm = inputdigit(ch,'0','1');//等待键盘输入是一个数字0~1否则就一直等待用户输入
			if(confirm == 1)
			{
				savedeleteinfo(t);
				head = DeleteNode(head,t);
			}
		}
		printf("\033[;31m是否继续删除? 1:继续 0:不继续 :\033[0m");	
    	choice= inputdigit(ch,'0','1');//等待键盘输入是一个数字0~1否则就一直等待用户输入		
	}
	return head;			
}



