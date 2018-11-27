#include"addrui.h"

//添加联系人界面
PERSONINFO add_info(STNODE *head)
{
	STNODE *p = (STNODE *)malloc(sizeof(STNODE *)*200);
	printf(BROWN"**********************\n");
	printf("*     添加联系人     *\n");
	printf("**********************\n"NONE);
	p->person.id = get_min_id(head);
	printf(BROWN"姓    名:"NONE);
	scanf("%s",p->person.name);
	printf(BROWN"性    别:"NONE);
	check_person_sex(p->person.sex);
	printf(BROWN"年    龄:"NONE);
	check_person_age(p->person.age);
	printf(BROWN"联系电话:"NONE);
	check_person_telephone(p->person.telephone);
	printf(BROWN"家庭住址:"NONE);
	scanf("%s",p->person.address);
	getchar();
	printf(BROWN"群    组:"NONE);
	check_person_group(p->person.group);
	printf(BROWN"邮    箱:"NONE);
	check_person_mails(p->person.mails);
	strcpy(p->person.addtime,gettime());
	return p->person;
}

//添加联系人主函数
STNODE *add_person_infoUI(STNODE *head)
{	
	int choice = 1;
	char ch ;
	do{
		PERSONINFO peo = add_info(head);
		generate_node(peo,head);//利用尾插法人员的信息临时存储在链表中
		add_flag++;             //添加标记自增
		printf("\033[;31m是否继续添加? 1:继续 0:不继续 :\033[0m");
		choice = inputdigit(ch,'0','1');
	}while(choice);
	return head;
}

//查找的主函数：按姓名或编号查询的合并的函数
void find_id_or_name_main(STNODE *head)
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


//修改联系人信息的界面
void modify_ui(STNODE *p)
{
	printf("\033[;36m请输入修改后的姓名\033[0m：");
	scanf("%s",p->person.name);
	printf("\033[;36m请输入修改后的性别\033[0m：");
	check_person_sex(p->person.sex);
	printf("\033[;36m请输入修改后的年龄\033[0m：");
	check_person_age(p->person.age);
	printf("\033[;36m请输入修改后的电话\033[0m：");
	check_person_telephone(p->person.telephone);
	printf("\033[;36m请输入修改后的住址\033[0m：");
	scanf("%s",p->person.address);
	getchar();
	printf("\033[;36m请输入修改后的群组\033[0m：");
	check_person_group(p->person.group);
	printf("\033[;36m请输入修改后的邮箱\033[0m：");
	check_person_mails(p->person.mails);
	strcpy(p->person.addtime,gettime());
}

//按姓名修改联系人的信息同时处理出现同名的情况
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
		printf(RED"\n因为出现重名情况，请输入编号进行操作 !!!\n"NONE);
		printf("输入联系人编号：");
		scanf("%d",&id);
		getchar();
		tmp = findID(head,id);
	}
	if(flagnum >= 2 && tmp == NULL)
	{
		printf(RED"没有姓名叫 %s 且编号为 %d 的联系人,请确认后输入!!!\n"NONE,name,id);
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
		printf(BLUE"\n修改联系人信息成功！！！\n"NONE);
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
    			modify_flag++;
    			break;
			case 2:
				printf("\033[;34m请输入联系人编号:\033[0m");
				scanf("%d",&id);
				getchar();
				head = modify_id_info(head,id,choice);
				modify_flag++;
    			break;
    	}//end of switch 
    	printf("\033[;31m是否继续修改? 1:继续 0:不继续 :\033[0m");	
    	choice1 = inputdigit(ch,'0','1');//等待键盘输入是一个数字0~1否则就一直等待用户输入
    }//end of while 
    return head;
}

//删除的主函数
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
				savedeleteinfo(t);          //保存删除人员的信息
				head = DeleteNode(head,t);  //删除节点
				delete_flag++;              //删除标记
				printf(BLUE"删除联系人成功!!!\n"NONE);
			}
			if(confirm == 0)
				printf("您选择不删除此联系人的信息!!!\n");
		}
		printf("\033[;31m是否继续删除? 1:继续 0:不继续 :\033[0m");	
    	choice= inputdigit(ch,'0','1');//等待键盘输入是一个数字0~1否则就一直等待用户输入		
	}
	return head;			
}

//返回操作选项函数
int return_option(char name[])
{
	int iChoice = 0;
    char ch;
    system("clear");     
    printf("\n\t\033[47;36m****************************************************************\033[0m\n");
    printf("\t\033[47;36m*                                                              *\033[0m\n");
    printf("\t\033[47;36m          ——————欢迎%s进入通讯录管理系统——————                \033[0m\n",name);
    printf("\t\033[47;36m*                                                              *\033[0m\n");
    printf("\t\033[47;36m****************************************************************\033[0m\n");
    printf("\t\033[47;36m                                                                \033[0m\n");
    printf("\t\033[47;36m                       相关操作选项                             \033[0m\n");
    printf("\t\033[47;36m                                                                \033[0m\n");
    printf("\t\033[47;36m****************************************************************\033[0m\n");
    printf("\t\033[47;36m*                     0.安全退出  系统                         *\033[0m\n");
    printf("\t\033[47;36m*                     1.添加联系人信息                         *\033[0m\n");
    printf("\t\033[47;36m*                     2.删除联系人信息                         *\033[0m\n");
    printf("\t\033[47;36m*                     3.修改联系人信息                         *\033[0m\n");
    printf("\t\033[47;36m*                     4.查找联系人信息                         *\033[0m\n");
    printf("\t\033[47;36m*                     5.显示联系人信息                         *\033[0m\n");
    printf("\t\033[47;36m*                     6.删除了的联系人                         *\033[0m\n");
    printf("\t\033[47;36m****************************************************************\033[0m\n");
    printf("请输入功能编号0 ~ 6:");
	iChoice = inputdigit(ch,'0','6');
    return iChoice;
}

//退出前进行资源回收和信息保存
void recovery_source_save_file(STNODE *head)
{
	STNODE *p = head->next;
	char ch;
	if(add_flag >= 1 || delete_flag >= 1 || modify_flag >= 1)
	{
		printf(L_PURPLE"\n系统检测到您改变了联系人信息，是否保存联系人信息 "NONE RED"[ 1/0 ]"NONE " !!!\n");
		int confirm = inputdigit(ch,'0','1');
		if(confirm == 1)
		{
			savefile(head,"职工管理系统.txt");
			DestroyLinklist(head);
			printf(RED"已安全退出系统，谢谢使用!!!\n"NONE);
			exit(0);
		}
		else
		{
			printf("\n您选择不保存已经更改的联系人信息!!!\n");
			DestroyLinklist(head);
			printf(RED"已安全退出系统，谢谢使用!!!\n"NONE);
			exit(0);
		}
	}
	else
	{
		DestroyLinklist(head);
		printf(L_PURPLE"\n\n系统未检测到您改变了联系人信息，已安全退出系统，谢谢使用!!!\n"NONE);
		exit(0);
	}
}

//返回主界面函数
void rethome()
{
	printf("\n按任意键回车后返回主界面 !!!\n");
	while(getchar() == '\n');
	getchar();
}

//用户登录成功之后对数据进行处理的函数
void useraction(char name[])
{
	STNODE *head1 = NULL;
	STNODE *head2 = NULL;
	head1 = readfiletolist("职工管理系统.txt");
	int choice,choice1 = 1;
	char ch;
	while(choice1)
	{
		choice = return_option(name);//UI层的返回操作选项的调用
		switch(choice)
		{
			case 1:                                   //增加人员信息
				head1 = add_person_infoUI(head1);    
				break;
			case 2:                                   //删除人员信息
				head1 = delete_idorname_main(head1); 
				break;
			case 3:                                   //修改人员信息
				head1 = modify_idorname_main(head1); 
				break;
			case 4:                                   //查找人员信息
				find_id_or_name_main(head1);              
				break;   
			case 5:                                   //显示人员信息
				showinfo_use_three_kinds(head1);       
				rethome();       
				break;
			case 6:                                   //显示删除了的人员信息
				show_delete_person_info();
				rethome();
				break;
			
			case 8:                              
				;                           
				break;
			case 0:                                   //退出保存操作
				recovery_source_save_file(head1);
				break;
		}
	}
	return;
}

int user_loginUI()
{
	char sname[20];
	char pass[30];
	int i = 1;
	for(i = 1; i < 4; i++)
	{
		printf("\t\033[46;31m***************用户登录***************************\033[0m\n");
		printf("\033[;31m 输入姓名:\033[0m");
		scanf("%s",sname);
		printf("\033[;31m 输入密码:\033[0m");
        getchar();
		hiden(pass);
		printf("\n");        
		if( (strcmp(sname,"李波") == 0) && strcmp(pass,"123") == 0 )
		{
			if(iputchecking())//验证码输入为正确的
			{
				logininf(sname,pass);//用来写登录纪录和提示上次登录时间和次数
				useraction(sname);  //boss的操作函数
				break;
			}
		}
		else
			printf("\033[;31m用户名或密码错误!!\033[0m\n");
	}
	if(i == 4)
	{
		printf("\033[;31m输入错误3次,自动退出系统!!\033[0m\n");
		exit(1);
	}
	return 0 ;
}























