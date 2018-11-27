#include "data_server.h"

/*
功能:文件判空函数
传入参数:char 类型的数组的文件名
返回值:int 类型
意义:返回ISTRUE表示为空，ISFALSE不为空
*/

Status jugde_file_isEmpty(char filename[50])
{
    int filepos = -1;
    FILE *file = fopen(filename, "rt");
    if(NULL == file)
    {
        printf("%s opening file %s occurs error in lines %d！\n",__PRETTY_FUNCTION__, filename, __LINE__);
        exit(0);
    }
    fseek(file, 0, SEEK_END);//将文件指针放到文件尾部
    filepos = ftell(file);//报告文件距离文件开头的位移量，如果为0，则表示文件为空
    if(0 == filepos)
    {
    	fclose(file);
    	file = NULL;
        return ISTRUE;     // 文件为空
    }
    else
    {
    	fclose(file);
    	file = NULL;
        return ISFALSE;   // 文件不为空
    }
}

/**********************************************************
功能:动态生成指针节点，尾插法。辅助read_file_use_fscanf函数的
使用:在read_file_use_fscanf函数中调用
传入参数:STNODE * 的头指针和 PERSONINFO people
返回值:void,对地址进行操作，无须返回头节点
**********************************************************/

void generate_node_for_login(reg_person_info people,Login_STNODE *head)
{
	Login_STNODE *p = (Login_STNODE *)malloc(sizeof(Login_STNODE)); //创建一个新结点p
    Login_STNODE *tmp = head;
    while(tmp->next != NULL)  //将指针移动到链表的尾部，即最后一个元素的地方,做尾插法操作
    	tmp = tmp->next;
    tmp->next = p;
    p->personinfo = people;
    p->next = NULL;
	return ;
}

/*
功能:fopen读文件生成链表
传入参数:char 类型的数组文件名
返回值:void 类型
意义:生成链表
*/
//读信息到登录表中，从登录表中获取上次登录时间和次数
void read_login_table(char filename[],Login_STNODE *head)
{
	FILE *file = fopen(filename,"rb");
	reg_person_info people;
	if(NULL == file)
    {
        printf(" %s() opening file <%s> occurs error in lines %d！",__PRETTY_FUNCTION__, filename, __LINE__);
        exit(0);
    }
    int flag = jugde_file_isEmpty(filename);
	while(!feof(file) && (!flag))
    {
        fscanf(file,"%d %s %s %s %d %s\n",
        	&people.reg_id,
        	people.reg_name,
        	people.reg_pwd,
        	people.reg_time,
        	&people.logincounts,
        	people.lastlogintime
        	);//从文件读入记录
    	generate_node_for_login(people,head);
    }//end of while
    fclose(file);
    file = NULL; 
}

/*
功能:获取当前系统时间
传入参数:char 类型
返回值:void 类型
意义:获取当前系统时间  需要包含头文件#include <time.h>
*/
void gettime(char *systime)
{
	char year[20],mon[10],day[10],hour[10],min[10],sec[10];
	time_t rawtime;
	struct tm *tm;
	time ( &rawtime );
	tm = localtime ( &rawtime );
	sprintf(year,"%d",tm->tm_year+1900);
	if( tm->tm_mon + 1 < 10)
		sprintf(mon,"0%d",tm->tm_mon + 1);
	else
		sprintf(mon,"%d",tm->tm_mon + 1);
	if( tm->tm_mday  < 10)
		sprintf(day,"0%d",tm->tm_mday);
	else
		sprintf(day,"%d",tm->tm_mday);
	if( tm->tm_hour < 10)
		sprintf(hour,"0%d",tm->tm_hour);
	else
		sprintf(hour,"%d",tm->tm_hour);
	if( tm->tm_min < 10)
		sprintf(min,"0%d",tm->tm_min);
	else
		sprintf(min,"%d",tm->tm_min);
	if( tm->tm_sec < 10)
		sprintf(sec,"0%d",tm->tm_sec);
	else
		sprintf(sec,"%d",tm->tm_sec);
	sprintf(systime,"%s-%s-%s-%s:%s:%s",year,mon,day,hour,min,sec);//printf("systime = %s\n",systime);
}

/*
功能:写客户的注册信息表
传入参数:MESSAGE 类型
返回值:void 类型
意义:写客户注册表
*/
void write_register_table(MESSAGE message)
{
    reg_person_info user_info;
    user_info.reg_id = 1000;
    strcpy(user_info.reg_name, message.name);
    strcpy(user_info.reg_pwd, message.msg);
    gettime(user_info.reg_time);
    user_info.logincounts = 0;
    gettime(user_info.lastlogintime);
    FILE *fp = NULL;
    fp = fopen("./dat/register_info.txt","ab");
    judge_openfile("./dat/register_info.txt", fp);
    fprintf(fp,"%-10d %-17s %-17s %-30s %-17d %-17s \n",
			user_info.reg_id,
        	user_info.reg_name,
        	user_info.reg_pwd,
        	user_info.reg_time,
        	user_info.logincounts,
        	user_info.lastlogintime
        	);//写文件操作
    fclose(fp);
    fp = NULL;
    return ;
}

/*
功能:判断分配空间是否成功
传入参数:指针类型
返回值:void 类型
意义:判断分配空间是否成功,成功继续运行，失败退出系统
*/
void judge_allocate(Login_STNODE *p)
{
	if(NULL == p)
	{
		printf("%s() phsical memory allocate failure in lines %d exit system!!\n",__PRETTY_FUNCTION__, __LINE__);
		exit(0);
	}
	else
	{
		return;
	}
}

/*
功能:判断打开文件是否成功
传入参数:char 和 文件指针类型
返回值:void 类型
意义:判断打开文件是否成功,成功继续运行，失败退出系统
*/
void judge_openfile(char filename[], FILE *fp)
{
    if (NULL == fp)
    {
        printf(" %s() opening file <%s> occurs error in lines %d！",__PRETTY_FUNCTION__, filename, __LINE__);
        exit(0);
    }
    else
    {
        return ;
    }
}

/*
功能:读文件生成注册了的人员信息表
传入参数:char 和 文件指针类型
返回值:void 类型
意义:生成注册了的人员信息表
*/
Login_STNODE * readfiletolist_for_login(char filename[30])
{
	Login_STNODE *head = (Login_STNODE *)malloc(sizeof(Login_STNODE));
	head->next = NULL;
	read_login_table(filename,head);
    return head;
}

void print_personinfo(Login_STNODE *head)
{
    Login_STNODE *p = head->next;
    while(p != NULL)
    {
        printf("%d %s %s %s %d %s\n",
        	p->personinfo.reg_id,
        	p->personinfo.reg_name,
        	p->personinfo.reg_pwd,
        	p->personinfo.reg_time,
        	p->personinfo.logincounts,
        	p->personinfo.lastlogintime
        	);//从文件读入记录
    	p = p->next;
    }
}




