#include"data.h"
char checknum[6];
int getch()
{
    int c=0;
    struct termios org_opts, new_opts;
    int res=0;
    //-----  store old settings -----------
    res=tcgetattr(STDIN_FILENO, &org_opts);//获取与终端相关的参数
    assert(res == 0);
    //---- set new terminal parms --------
    memcpy(&new_opts, &org_opts, sizeof(new_opts));//拷贝结构体

    new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);//设置终端参数
    c=getchar();
    //------  restore old settings ---------
    res=tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);//还原终端设置
    assert(res == 0);
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
            if (pd[i] == '\n')
            {
                pd[i]='\0';
                break;
            }
            if (pd[i] == 127)
            {
                printf("\b \b");
                i=i-2;
            }
            else
                printf("*");
            if (i<0)
                pd[0]='\0';
        }
        break;
    }
}
//生成验证码
void get_rand_str(int number)
{
    char str[63] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int i,t;
    char ss[6];
    srand(time(NULL));
    for(i=0;i<number;i++)
    {
        t=rand()%62;
        ss[i]=str[t];//printf("i=%d\n",i);
    }
    ss[4]='\0';
    strcpy(checknum,ss);
    cout<<"\033[;31m请输入以下验证码:\033[0m";
}

//链接数据库
void connectdatabase()
{
    const char *server="localhost";
    const char *user="root";
    const char *password="123456";
    const char *database="companymanage";
    conn=mysql_init(NULL);  //初始化句柄，成功：不为NULL
    if (conn == NULL)
    {
        cout<<"mysql_init error!!"<<endl;
        return;
    }
    if (!mysql_real_connect(conn,server,user,password,database,0,NULL,0)) //连接成功，返回conn;失败，返回NULL。
    {
        fprintf(stderr,"%s\n",mysql_error(conn));
        return;
    }
    mysql_set_character_set(conn,"utf8"); //字符集设置
}
//数据库按编号查找
int findnumber(char buf[200],int idnum)
{	
    int flag=0;
    if (mysql_query(conn,buf))
    {
        fprintf(stderr,"%s\n",mysql_error(conn));
        exit(1);
    }
    res = mysql_use_result(conn);//发送结果集
    if ((row=mysql_fetch_row(res)) != NULL)
    {
        flag=1;
        printf("%-10s%-12s%-15s%-15s  %-13s%-10s","\t编号","  姓名","职  称","  部  门","等级","上 级\n");
        printf("\t%-6d\t %-10s%-18s %-17s%-10s%-10s\n\n",atoi(row[0]),row[1],row[2],row[3],row[4],row[5]);
    }
    //	else
    //		cout<<"    没有编号为"<< idnum <<"的人员信息!!!\n"<<endl;
    return flag;
}

//数据库按姓名查找
int findname(char buf[200],char name[30])
{	
    int flag = 0;
    if (mysql_query(conn,buf))
    {
        fprintf(stderr,"%s\n",mysql_error(conn));
        exit(1);
    }
    res = mysql_use_result(conn);
    if ((row=mysql_fetch_row(res))!= NULL)
    {
        flag = 1;
        printf("%-10s%-12s%-17s%-15s%-13s%-10s","\t姓名","  编号","职    称","部  门","等级","上    级\n");
        printf("\t%-11s%-8d%-17s %-17s%-11s%-10s\n\n",row[0],atoi(row[1]),row[2],row[3],row[4],row[5]);
    }
    //	else
    //		cout<<"    没有姓名为"<< name <<"的人员信息!!!\n"<<endl;
    return flag;

}

//按部门删除的查找
void showfordep()
{	
    char man[200];
    sprintf(man,"select id,name,position,department,grade,leader from personinfo where department='%s'","技术部");
    if (mysql_query(conn,man))
    {
        fprintf(stderr,"%s\n",mysql_error(conn));
        exit(1);
    }
    res = mysql_use_result(conn);
    printf("%-10s%-12s%-15s%-15s%-13s%-10s","\t姓名","  编号","职    称","部  门","等级","上    级\n");
    while((row = mysql_fetch_row(res))!=NULL)
    {
        printf("\t%-11s%-8d%-16s %-17s%-11s%-10s\n\n",row[0],atoi(row[1]),row[2],row[3],row[4],row[5]);
    }
    mysql_free_result(res);  //释放结果集使用内存
    cout<<endl;cout<<endl;
    sprintf(man,"select id,name,position,department,grade,leader from personinfo where department='%s'","销售部");
    if (mysql_query(conn,man))
    {
        fprintf(stderr,"%s\n",mysql_error(conn));
        exit(1);
    }
    res = mysql_use_result(conn);
    printf("%-10s%-12s%-15s%-15s%-13s%-10s","\t姓名","  编号","职    称","部  门","等级","上    级\n");
    while ((row = mysql_fetch_row(res))!=NULL)
    {
        printf("\t%-11s%-8d%-16s %-17s%-11s%-10s\n\n",row[0],atoi(row[1]),row[2],row[3],row[4],row[5]);
    }
    mysql_free_result(res);  //释放结果集使用内存
}

//数据库按编号删除
void deletenumber(char buf,int idnum)
{
    char man[100];
    if (buf == 'y')
    {
        sprintf(man,"delete from personinfo where id=%d",idnum);
        if (mysql_query(conn,man))
        {
            fprintf(stderr,"%s\n",mysql_error(conn));
            exit(1);
        }
        cout<<"\033[;31m删除成功!!!\033[0m"<<endl;
    }
    if (buf == 'n')
        cout <<"\033[;31m您选择不删除这一条纪录!!!\n\033[0m";

}

//数据库按姓名删除
void deletename(char buf,char name[30])
{
    char man[100];
    if (buf == 'y')
    {
        sprintf(man,"delete from personinfo where name='%s'",name);
        if (mysql_query(conn,man))
        {
            fprintf(stderr,"%s\n",mysql_error(conn));
            exit(1);
        }
        cout<<"\033[;31m删除成功!!!\033[0m"<<endl;
    }
    if (buf == 'n')
        cout <<"\033[;31m您选择不删除这一条纪录!!!\n\033[0m";
}


//boss按编号修改
void modifyid(char name[30],int idnum,int id,char pos[30],char dep[30],char gra[30],char lea[30],char perf[20],int ltime)
{
    char man[300];
    sprintf(man,"update personinfo set name='%s',id=%d,position='%s',department='%s',grade='%s',leader='%s',performance='%s',latertimes=%d where id=%d",name,id,pos,dep,gra,lea,perf,ltime,idnum);
    if (mysql_query(conn,man))
    {
        fprintf(stderr,"%s\n",mysql_error(conn));
        exit(1);
    }
}
//boss按姓名修改
void modifyname(char name[30],char nname[30],int id,char pos[30],char dep[30],char gra[30],char lea[30],char perf[20],int ltime)
{
    char man[300];
    sprintf(man,"update personinfo set name='%s',id=%d,position='%s',department='%s',grade='%s',leader='%s',performance='%s',latertimes=%d where name='%s'",nname,id,pos,dep,gra,lea,perf,ltime,name);
    if (mysql_query(conn,man))
    {
        fprintf(stderr,"%s\n",mysql_error(conn));
        exit(1);
    }
}

//经理销售经理按编号修改
void modifyid1(char name[30],int idnum,int id,/*char pos[30],char dep[30],char gra[30],char lea[30],*/char perf[20],int ltime)
{
    char man[300];
    sprintf(man,"update personinfo set name='%s',id=%d,performance='%s',latertimes=%d where id=%d",name,id,perf,ltime,idnum);
    if (mysql_query(conn,man))
    {
        fprintf(stderr,"%s\n",mysql_error(conn));
        exit(1);
    }
}
//经理销售经理按姓名修改
void modifyname1(char name[30],char nname[30],int id,/*char pos[30],char dep[30],char gra[30],char lea[30],*/char perf[20],int ltime)
{
    char man[300];
    sprintf(man,"update personinfo set name='%s',id=%d,performance='%s',latertimes=%d where name='%s'",nname,id,perf,ltime,name);
    if (mysql_query(conn,man))
    {
        fprintf(stderr,"%s\n",mysql_error(conn));
        exit(1);
    }
}

//boss按编号输入(修改)
void input1(char buf,int idnum)
{
    char name[30];
    int id;
    char pos[30];
    char dep[30];
    char gra[30];
    char lea[30];
    char perf[20];
    int ltime;
    if (buf == 'y')
    {
        cout<<"\033[;31m请输入修改后的姓名:\033[0m";
        cin>>name;
        cout<<"\033[;31m请输入修改后的编号:\033[0m";
        cin>>id;
        cout<<"\033[;31m请输入修改后的职称:\033[0m";
        cin>>pos;
        cout<<"\033[;31m请输入修改后的部门:\033[0m";
        cin>>dep;
        cout<<"\033[;31m请输入修改后的等级:\033[0m";
        cin>>gra;
        cout<<"\033[;31m请输入修改后的上级:\033[0m";
        cin>>lea;
        cout<<"\033[;31m请输入修改后的表现:\033[0m";
        cin>>perf;
        cout<<"\033[;31m请输入修改后的迟到次数:\033[0m";
        cin>>ltime;
        modifyid(name,idnum,id,pos,dep,gra,lea,perf,ltime);
        cout<<"\033[;31m修改成功!!!\033[0m"<<endl;
    }
    if (buf == 'n')
        cout <<"\033[;31m您选择不修改这一条纪录!!!\n\033[0m";
}
//boss按姓名输入(修改)
void input2(char buf,char name[30])
{
    char nname[30];
    int id;
    char pos[30];
    char dep[30];
    char gra[30];
    char lea[30];
    char perf[20];
    int ltime;
    if (buf == 'y')
    {
        cout<<"\033[;31m请输入修改后的姓名:\033[0m";
        cin>>nname;
        cout<<"\033[;31m请输入修改后的编号:\033[0m";
        cin>>id;
        cout<<"\033[;31m请输入修改后的职称:\033[0m";
        cin>>pos;
        cout<<"\033[;31m请输入修改后的部门:\033[0m";
        cin>>dep;
        cout<<"\033[;31m请输入修改后的等级:\033[0m";
        cin>>gra;
        cout<<"\033[;31m请输入修改后的上级:\033[0m";
        cin>>lea;
        cout<<"\033[;31m请输入修改后的表现:\033[0m";
        cin>>perf;
        cout<<"\033[;31m请输入修改后的迟到次数:\033[0m";
        cin>>ltime;
        modifyname(name,nname,id,pos,dep,gra,lea,perf,ltime);
        cout<<"\033[;31m修改成功!!!\033[0m"<<endl;
    }
    if (buf == 'n')
        cout <<"\033[;31m您选择不修改这一条纪录!!!\n\033[0m";
}

//经理销售经理按编号输入(修改)
void input3(char buf,int idnum)
{
    char name[30];
    int id;
    //char pos[30];
    //char dep[30];
    //char gra[30];
    //char lea[30];
    char perf[20];
    int ltime;
    if (buf == 'y')
    {
        cout<<"\033[;31m请输入修改后的姓名:\033[0m";
        cin>>name;
        cout<<"\033[;31m请输入修改后的编号:\033[0m";
        cin>>id;
        /*cout<<"\033[;31m请输入修改后的职称:\033[0m";
                cin>>pos;
                cout<<"\033[;31m请输入修改后的部门:\033[0m";
                cin>>dep;
                cout<<"\033[;31m请输入修改后的等级:\033[0m";
                cin>>gra;
                cout<<"\033[;31m请输入修改后的上级:\033[0m";
                cin>>lea;*/
        cout<<"\033[;31m请输入修改后的表现:\033[0m";
        cin>>perf;
        cout<<"\033[;31m请输入修改后的迟到次数:\033[0m";
        cin>>ltime;
        modifyid1(name,idnum,id,/*pos,dep,gra,lea,*/perf,ltime);
        cout<<"\033[;31m修改成功!!!\033[0m"<<endl;
    }
    if (buf == 'n')
        cout <<"\033[;31m您选择不修改这一条纪录!!!\n\033[0m";
}
//经理销售经理按姓名输入(修改)
void input4(char buf,char name[30])
{
    char nname[30];
    int id;
    char pos[30];
    char perf[20];
    int ltime;
    if (buf == 'y')
    {
        cout<<"\033[;31m请输入修改后的姓名:\033[0m";
        cin>>nname;
        cout<<"\033[;31m请输入修改后的编号:\033[0m";
        cin>>id;
        cout<<"\033[;31m请输入修改后的表现:\033[0m";
        cin>>perf;
        cout<<"\033[;31m请输入修改后的迟到次数:\033[0m";
        cin>>ltime;
        modifyname1(name,nname,id,perf,ltime);
        cout<<"\033[;31m修改成功!!!\033[0m"<<endl;
    }
    if (buf == 'n')
        cout <<"\033[;31m您选择不修改这一条纪录!!!\n\033[0m";
}

//部门选择
employee depart(employee e)
{
    if (strcmp(e.position,"经理") == 0||strcmp(e.position,"技术人员") == 0)
    {
        strcpy(e.department,"技术部");
    }
    if (strcmp(e.position,"销售经理") == 0 ||strcmp(e.position,"销售人员") == 0)
    {
        strcpy(e.department,"销售部");
    }
    return e;
}

//级别选择
employee gradechoice(employee e)
{
    if (strcmp(e.position,"技术人员") == 0 || strcmp(e.position,"销售人员") == 0)
    {
        strcpy(e.grade,"3");
    }
    if (strcmp(e.position,"经理") == 0 || strcmp(e.position,"销售经理") == 0)
    {
        strcpy(e.grade,"2");
    }
    return e;
}

//上级选择
employee leaderchoice(employee e)
{	
    if (strcmp(e.position,"技术人员") == 0)
    {
        strcpy(e.leader,"经理");
    }
    if (strcmp(e.position,"销售人员") == 0)
    {
        strcpy(e.leader,"销售经理");
    }
    if (strcmp(e.position,"经理") == 0 || strcmp(e.position,"销售经理") == 0)
    {
        strcpy(e.leader,"boss");
    }
    return e;
}
//固定工资
employee stablesal(employee e)
{	
    if (strcmp(e.position,"技术人员") == 0)
    {
        e.stablesalary=0;
    }
    if (strcmp(e.position,"销售人员") == 0)
    {
        e.stablesalary=0;
    }
    if (strcmp(e.position,"经理") == 0 )
    {
        e.stablesalary=20000;
    }
    if ( strcmp(e.position,"销售经理") == 0)
    {
        e.stablesalary=5000;
    }
    return e;
}

//工作时间
int wtime(employee e,int worktime)
{	
    if (strcmp(e.position,"技术人员") == 0)
    {
        worktime=8;
    }
    if (strcmp(e.position,"销售人员") == 0)
    {
        worktime=0;
    }
    if (strcmp(e.position,"经理") == 0 )
    {
        worktime=0;
    }
    if ( strcmp(e.position,"销售经理") == 0)
    {
        worktime=0;
    }
    return worktime;
}

//单位时间报酬
int treward(employee e)
{	
    if (strcmp(e.position,"技术人员") == 0)
    {
        e.timereward=50;
    }
    if (strcmp(e.position,"销售人员") == 0)
    {
        e.timereward=0;
    }
    if (strcmp(e.position,"经理") == 0 )
    {
        e.timereward=0;
    }
    if ( strcmp(e.position,"销售经理") == 0)
    {
        e.timereward=0;
    }
    return e.timereward;
}

//提成
double tic(employee e)
{	
    if (strcmp(e.position,"技术人员") == 0)
    {
        e.ticheng=0;
    }
    if (strcmp(e.position,"销售人员") == 0)
    {
        e.ticheng=0.012;
    }
    if (strcmp(e.position,"经理") == 0 )
    {
        e.ticheng=0;
    }
    if ( strcmp(e.position,"销售经理") == 0)
    {
        e.ticheng=0.01;
    }
    return e.ticheng;
}

//积分初始化
int jifeninit(employee e)
{
    if (strcmp(e.position,"技术人员") == 0 || strcmp(e.position,"销售人员") == 0)
    {
        e.jifen = 100;
    }
    if (strcmp(e.position,"经理") == 0 || strcmp(e.position,"销售经理") == 0)
    {
        e.jifen = 200;
    }
    return e.jifen;
}

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

// 等待键盘输入是一个数字0~9否则就一直等待用户输入
int inputdigit09(char ch)
{
    do
    {
        ch=getchar();
    }
    while(!(ch>='0'&&ch<='9'));
    return ch-'0';
}

// 等待键盘输入是一个数字0~9否则就一直等待用户输入
int inputdigit02(char ch)
{
    do
    {
        ch=getchar();
    }
    while(!(ch>='0'&&ch<='2'));
    return ch-'0';
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
//模拟与服务器连接函数,动态打印点
void printdot1()
{
    int i = 3;
    while(i)
    {
        printf(" . . ");
        fflush(stdout);
        i--;
        sleep(1);
    }
    printf("\n");
}


//向数据库发送sql语句
void sendrequest(char man[200])
{	
    if (mysql_query(conn,man))
    {
        fprintf(stderr,"%s\n",mysql_error(conn));
        exit(1);
    }

}
//工资按照职称,表现,迟到次数计算最终工资
void judgesalary(employee e,int idnum)
{
    char man[200];
    char bz[100];
    if (strcmp(e.position,"经理") == 0)
    {
        if (strcmp(e.performance,"一般") == 0)
        {
            if (e.latertimes>=3)
            {
                e.salary=e.stablesalary-100;
                sprintf(bz,"表现一般,迟到%d次,扣除工资100元",e.latertimes);
                sprintf(man,"update personinfo set salary=%lf,beizhu='%s' where id=%d",e.salary,bz,idnum);
                sendrequest(man);//向数据库发送sql语句
            }
            else
            {
                e.salary=e.stablesalary;
                sprintf(bz,"表现一般,迟到少于三次,不扣工资,也没有奖励!");
                sprintf(man,"update personinfo set salary=%lf,beizhu='%s' where id=%d",e.salary,bz,idnum);
                sendrequest(man);//向数据库发送sql语句
            }
        }
        if (strcmp(e.performance,"优秀") == 0)
        {
            e.salary=e.stablesalary+500;
            sprintf(bz,"表现优秀,奖励工资500元,再接再厉!");
            sprintf(man,"update personinfo set salary=%lf,beizhu='%s' where where id=%d",e.salary,bz,idnum);
            sendrequest(man);//向数据库发送sql语句

        }
    }
    else if (strcmp(e.position,"销售经理") == 0)
    {
        if (strcmp(e.performance,"一般") == 0)
        {
            if (e.latertimes>=3)
            {
                e.salary=e.stablesalary+e.zonge*e.ticheng-100;
                sprintf(bz,"表现一般,迟到%d次,扣除工资100,提成加上%.0lf",e.latertimes,e.zonge*e.ticheng);
                sprintf(man,"update personinfo set salary=%lf,beizhu='%s' where id=%d",e.salary,bz,idnum);
                sendrequest(man);//向数据库发送sql语句

            }
            else
            {
                e.salary=e.stablesalary+e.zonge*e.ticheng;
                sprintf(bz,"表现一般,迟到少于三次,不扣工资,提成加%.0lf",e.zonge*e.ticheng);
                sprintf(man,"update personinfo set salary=%lf,beizhu='%s' where id=%d",e.salary,bz,idnum);
                sendrequest(man);//向数据库发送sql语句

            }
        }
        if (strcmp(e.performance,"优秀") == 0)
        {
            e.salary=e.stablesalary+e.zonge*e.ticheng+500;
            sprintf(bz,"表现优秀,奖励500元,提成加上%.0lf,再接再厉!",e.zonge*e.ticheng);
            sprintf(man,"update personinfo set salary=%lf,beizhu='%s' where id=%d",e.salary,bz,idnum);
            sendrequest(man);//向数据库发送sql语句

        }

    }
    else if (strcmp(e.position,"技术人员") == 0)
    {
        if (strcmp(e.performance,"一般") == 0)
        {
            if (e.latertimes>=3)
            {
                e.salary=e.worktime*e.timereward*30-100;
                sprintf(bz,"表现一般,迟到%d次,扣除工资100",e.latertimes);
                sprintf(man,"update personinfo set salary=%lf,beizhu='%s' where id=%d",e.salary,bz,idnum);
                sendrequest(man);//向数据库发送sql语句

            }
            else
            {
                e.salary=e.worktime*e.timereward*30;
                sprintf(bz,"表现一般,迟到少于三次,不扣工资,也没有奖励!");
                sprintf(man,"update personinfo set salary=%lf,beizhu='%s' where id=%d",e.salary,bz,idnum);
                sendrequest(man);//向数据库发送sql语句

            }
        }
        if (strcmp(e.performance,"优秀") == 0)
        {
            e.salary=e.worktime*e.timereward*30+500;
            sprintf(bz,"表现优秀,奖励500元,再接再厉!!");
            sprintf(man,"update personinfo set salary=%lf,beizhu='%s' where id=%d",e.salary,bz,idnum);
            sendrequest(man);//向数据库发送sql语句
        }

    }
    else if (strcmp(e.position,"销售人员") == 0)
    {
        if (strcmp(e.performance,"一般") == 0)
        {
            if (e.latertimes>=3)
            {
                e.salary=e.ticheng*e.zonge-100;
                sprintf(bz,"表现一般,迟到%d次,扣除工资100,提成加上%.0lf",e.latertimes,e.ticheng*e.zonge);
                sprintf(man,"update personinfo set salary=%lf,beizhu='%s' where id=%d",e.salary,bz,idnum);
                sendrequest(man);//向数据库发送sql语句
            }
            else
            {
                e.salary=e.ticheng*e.zonge;
                sprintf(bz,"表现一般,迟到少于三次,不扣工资,提成加%.0lf",e.ticheng*e.zonge);
                sprintf(man,"update personinfo set salary=%lf,beizhu='%s' where id=%d",e.salary,bz,idnum);
                sendrequest(man);//向数据库发送sql语句
            }
        }
        if (strcmp(e.performance,"优秀") == 0)
        {
            e.salary=e.ticheng*e.zonge+500;
            sprintf(bz,"表现优秀,奖励500元,再接再厉!!");
            sprintf(man,"update personinfo set salary=%lf,beizhu='%s' where id=%d",e.salary,bz,idnum);
            sendrequest(man);//向数据库发送sql语句
        }
    }
}
//登录时显示上次登录时间函数并且将本次登录时间和次数写进数据库里面去
void logininf(int idnum,char name[30],char pass[30])
{	
    char man[200];
    char lgtime[40];
    int number;
    sprintf(man,"select lastlogintime,logincounts from logintable where id=%d",idnum);
    sendrequest(man);
    res = mysql_use_result(conn);  //获得结果集， 一个表
    row = mysql_fetch_row(res);
    if (row == NULL)//登录表中没有此人的信息时将此人的信息插入到登录表中
    {
        mysql_free_result(res);
        sprintf(man,"insert into logintable (id,username,passwd,lastlogintime,logincounts)values(%d,'%s','%s',now(),%d)",idnum,name,pass,1);
        sendrequest(man);
        cout<<name<<"\033[;31m您好! 您是首次登录,欢迎您的到来!!\033[0m"<<endl;
    }

    if (row!=NULL)//登录表中没有此人的信息时将此人的信息插入到登录表中
    {
        strcpy(lgtime,row[0]);
        number=atoi(row[1])+1;
        mysql_free_result(res);
        //		cout<<name<<"您好! 您上次登录时间:"<<row(0)<<"欢迎您的到来!!"<<endl; //row[0]不能在这里使用 error: ‘row’ cannot be used as a function
        printf("%s\033[;31m您好! 您上次登录时间:\033[0m%s ,\033[;31m第\033[0m%d\033[;31m次登录,欢迎您的到来!,正在跳转操作界面请稍后\033[0m",name,lgtime,number);
        printdot();
        sprintf(man,"update logintable set lastlogintime=now(),logincounts=logincounts+1 where id=%d",idnum);
        sendrequest(man);
    }
    sleep(1);
}
//各类用户都可以修改密码包括boss
void modifypasswd(int idnum)
{
    char man[200];
    char pass[30];
    char confirm;
    cout<<"\033[;31m请输入修改后的密码:\033[0m";
    cin>>pass;
    cout<<"\033[;31m是否确认修改?  [y/n]:\033[0m";
    while(getchar()!='\n');
    confirm=getchar();
    sprintf(man,"update personinfo set passwd='%s' where id=%d",pass,idnum);
    if (confirm == 'y')
    {
        sendrequest(man);//向数据库发送sql语句
        cout<<"\033[;31m密码修改成功!!\n\033[0m";
    }
    else if (confirm == 'n')
    {
        cout<<"\033[;31m您选择放弃修改密码!\n\033[0m";
    }
    else
    {
        cout<<"\033[;31m输入的不是y/n,密码修改失败,退出修改!!\n\033[0m";
    }
    sleep(3);
}








