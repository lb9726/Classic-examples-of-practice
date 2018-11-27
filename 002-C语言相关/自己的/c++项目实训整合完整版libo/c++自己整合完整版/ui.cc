#include"ui.h"
#include"logic.h"
char check[10];
extern char checknum[10];
//输入验证码调用函数
int iputchecking()
{   int i = 0;
    int flag = 0;
    while (i<3)
    {
        get_rand_str(4); puts(checknum);
        cin>>check;//puts(check);
        if (strcmp(check, checknum) == 0)
        {
            flag=1;
            break;
        }
        i++;
    }
    if (i == 3)
        exit(1);
    return flag;
}

int LoginUI()
{
    char sname[20];
    char pass[30];
    char check[10];
    char ch;
    int i = 1;
    int iChoice=1;
    int Choice;

    list<employee> Link;
    employee xp;
    mysql_query(conn, "select *from personinfo"); //从数据库中获取登录信息
    res = mysql_use_result(conn);  //获得结果集， 一个表

    while ((row = mysql_fetch_row(res)) != NULL)
    {
        xp.id = atoi(row[0]);
        strcpy(xp.name, row[1]);
        strcpy(xp.passwd, row[2]);
        strcpy(xp.position, row[4]);
        Link.push_back(xp);

    }

    system("clear");
    while (iChoice!=0)
    {
        system("clear");
        cout<<"\t\033[46;31m ***************欢迎进入公司管理系统**************\033[0m"<<endl;
        cout<<"\t\033[47;31m **                                             **\033[0m"<<endl;
        cout<<"\t\033[47;31m **             1.boss登录                      **\033[0m"<<endl;
        cout<<"\t\033[47;31m **                                             **\033[0m"<<endl;
        cout<<"\t\033[47;31m **             2.经理登录                      **\033[0m"<<endl;
        cout<<"\t\033[47;31m **                                             **\033[0m"<<endl;
        cout<<"\t\033[47;31m **             3.销售经理登录                  **\033[0m"<<endl;
        cout<<"\t\033[47;31m **                                             **\033[0m"<<endl;
        cout<<"\t\033[47;31m **             4.技术人员登录                  **\033[0m"<<endl;
        cout<<"\t\033[47;31m **                                             **\033[0m"<<endl;
        cout<<"\t\033[47;31m **             5.销售人员登录                  **\033[0m"<<endl;
        cout<<"\t\033[47;31m **                                             **\033[0m"<<endl;
        cout<<"\t\033[47;31m **             0.退出                          **\033[0m"<<endl;
        cout<<"\t\033[46;31m *************************************************\033[0m"<<endl;
        cout<<"\033[;31m 请输入操作的编号:\033[0m"<<endl;
        //		cin>>Choice;
        Choice = inputdigit05(ch);// 等待键盘输入是一个数字0~5否则就一直等待用户输入
        if (Choice == 1)
        {
            for(i=1; i<4; i++)
            {
                cout<<"\t\033[46;31m***************boss登录***************************\033[0m"<<endl;
                cout<<"\033[;31m 输入姓名:\033[0m";
                cin>> sname;
                cout<<"\033[;31m 输入密码:\033[0m";
                //cin>>pass;
                getchar();
                hiden(pass);
                cout<< endl;

                if ((strcmp(sname, "boss") == 0) && strcmp(pass, "123") == 0)
                {
                    if (iputchecking())//验证码输入为正确的
                    {
                        logininf(1, sname, pass);
                        BossUI();
                        break;
                    }
                }
                else
                    cout << "\033[;31m输入错误\033[0m" <<endl;
            }
            cout << "\033[;31m输入错误3次, 自动退出系统\033[0m"<<endl;
            exit(1);
        }
        else if (Choice == 2)  //经理级别 按职称登录
        {
            for(i=1; i<4; i++)
            {
                cout<<"\t\033[46;31m****************经理登录**************************\033[0m"<<endl;
                cout<< "\033[;31m输入姓名:\033[0m";
                cin>>sname;
                cout<< "\033[;31m输入密码:\033[0m";
                //cin>>pass;
                getchar();
                hiden(pass);
                cout<< endl;
                list<employee>::iterator p=Link.begin();  //创建容器Link1的迭代器 p;
                while (p!=Link.end())
                {
                    if ((strcmp(sname, p->name) == 0&&strcmp(pass, p->passwd) == 0)&&strcmp("经理", p->position) == 0)
                    {
                        if (iputchecking())//验证码输入为正确的
                        {
                            logininf(p->id, p->name, p->passwd);
                            ManagerUI(p->id);
                            break;
                        }
                    }
                    p++;
                }
                if (p!=Link.end())
                    break;
                if (p == Link.end())
                    cout << "\033[;31m输入错误\033[0m" <<endl;
            }
            cout << "\033[;31m输入错误3次, 自动退出系统\033[0m"<<endl;
            exit(1);
        }
        else if (Choice == 3)  //销售经理 按职称登录
        {
            for(i=1; i<4; i++)
            {
                cout<<"\t\033[46;31m**********************销售经理登录****************\033[0m"<<endl;
                cout<<"\033[;31m输入姓名:\033[0m";
                cin>>sname;
                cout<<"\033[;31m输入密码:\033[0m";
                //cin>>pass;
                getchar();
                hiden(pass);
                cout<< endl;
                list<employee>::iterator p=Link.begin();
                while (p!=Link.end())
                {
                    if ((strcmp(sname, p->name) == 0&&strcmp(pass, p->passwd) == 0)&&strcmp("销售经理", p->position) == 0)
                    {
                        if (iputchecking())//验证码输入为正确的
                        {
                            logininf(p->id, p->name, p->passwd);
                            SalemanagerUI(p->id);
                            break;
                        }
                    }
                    p++;
                }
                if (p!=Link.end())
                    break;
                if (p == Link.end())
                    cout << "\033[;31m输入错误\033[0m" <<endl;
            }
            cout << "\033[;31m输入错误3次, 自动退出系统\033[0m"<<endl;
            exit(1);
        }
        else if (Choice == 4)     //技术人员 按职称登录
        {
            for(i=1;i<4;i++)
            {
                cout<<"\t\033[46;31m**********************技术人员登录****************\033[0m"<<endl;
                cout<<"\033[;31m输入姓名:\033[0m";
                cin>>sname;
                cout<<"\033[;31m输入密码:\033[0m";
                //cin>>pass;
                getchar();
                hiden(pass);
                cout<< endl;
                list<employee>::iterator p=Link.begin();
                while (p!=Link.end())
                {
                    if ((strcmp(sname, p->name) == 0&&strcmp(pass, p->passwd) == 0)&&strcmp("技术人员", p->position) == 0)
                    {
                        if (iputchecking())//验证码输入为正确的
                        {
                            logininf(p->id, p->name, p->passwd);
                            SkillpersonUI(p->id);
                            break;
                        }
                    }
                    p++;
                }
                if (p!=Link.end())
                    break;
                if (p == Link.end())
                    cout << "\033[;31m输入错误\033[0m" <<endl;
            }
            cout << "\033[;31m输入错误3次, 自动退出系统\033[0m"<<endl;
            exit(1);
        }
        else if (Choice == 5)     //销售人员 rank = 5
        {
            for(i=1;i<4;i++)
            {
                cout<<"\t\033[46;31m**********************销售人员登录****************\033[0m"<<endl;
                cout<<"\033[;31m输入姓名:\033[0m";
                cin>>sname;
                cout<<"\033[;31m输入密码:\033[0m";
                //cin>>pass;
                getchar();
                hiden(pass);
                cout<< endl;
                list<employee>::iterator p=Link.begin();  //创建容器Link1的迭代器 p;
                while (p!=Link.end())
                {
                    if ((strcmp(sname, p->name) == 0&&strcmp(pass, p->passwd) == 0)&&strcmp("销售人员", p->position) == 0)
                    {
                        if (iputchecking())//验证码输入为正确的
                        {
                            logininf(p->id, p->name, p->passwd);
                            SalepersonUI(p->id);
                            break;
                        }
                    }
                    p++;
                }
                if (p!=Link.end())
                    break;
                if (p == Link.end())
                    cout << "\033[;31m输入错误\033[0m" <<endl;
            }
            cout << "\033[;31m输入错误3次, 自动退出系统\033[0m"<<endl;
            exit(1);
        }
        else if (Choice == 0)
        {
            exit(1);
        }
        else
        {
            cout<<"\033[;31m输入有误！请重新输入\033[0m"<<endl;
            LoginUI();
        }
    }


}
