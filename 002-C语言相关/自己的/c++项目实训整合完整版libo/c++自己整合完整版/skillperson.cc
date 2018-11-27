#include"ui.h"

int SkillpersonUI(int idnum)
{
    int iChoice=1;
    Skillperson skillperson;
    char ch;
    system("clear");
    while (iChoice!=0)
    {
        system("clear");
        cout<<"\t\033[46;31m*********************技术人员界面*****************\033[0m"<<endl;
        cout<<"\t\033[46;31m**                 1.显示个人信息               **\033[0m"<<endl;
        cout<<"\t\033[46;31m**                 2.修改个人密码               **\033[0m"<<endl;
        cout<<"\t\033[46;31m**                 0.返回登录界面               **\033[0m"<<endl;
        cout<<"\t\033[46;31m**************************************************\033[0m"<<endl;

        cout<<" \033[;31m选择要使用的功能(0-2):\033[0m" <<endl;
        //		cin>>iChoice;
        iChoice=inputdigit02(ch);
        switch(iChoice)
        {
        case 1:
            skillperson.show(idnum);
            break;
        case 2:
            modifypasswd(idnum);
            break;
        case 0:
            LoginUI();
            break;
        }
    }
}

void Skillperson::show(int idnum)
{   
    system("clear");
    char man[200];
    sprintf(man,"select id,name,passwd,sex,position,department,grade,leader from personinfo where id=%d",idnum);
    if (mysql_query(conn,man))
    {
        fprintf(stderr,"%s\n",mysql_error(conn));
        exit(1);
    }
    res = mysql_use_result(conn);//获得结果集， 一个表。
    printf("%-8s%-15s%-15s%-11s%-6s%-12s%-16s%-12s%-s","\t\033[;31m编号","   姓名","密码","性别","职"," 称","部  门","等级","上   级\n\033[0m");
    while ((row=mysql_fetch_row(res)) != NULL)
    {
        printf("\t%d\t%-12s%-10s\t%-8s\t%-12s\t%-13s\t%s\t%-10s\n",atoi(row[0]),row[1],row[2],row[3],row[4],row[5],row[6],row[7]);
    }
    cout<<"\033[;31m按任意键回上一界面！\033[0m"<<endl;
    while (getchar()=='\n');

    //	mysql_free_result(res);
}  

