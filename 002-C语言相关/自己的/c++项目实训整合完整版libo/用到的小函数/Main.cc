#include"Data.h"
MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;

int LoginUI()
{
	const char *server = "localhost";
	const char *user = "root";
	const char *passwd = "341125";
	const char *database = "zhx";
	conn=mysql_init(NULL);   //初始化句柄，成功：不为NULL
	if(!mysql_real_connect(conn,server,user,passwd,database,0,NULL,0)) //连接成功，返回conn;失败，返回NULL。
	{
		fprintf(stderr,"%s\n",mysql_error(conn));

		return 0;
	}
	mysql_set_character_set(conn,"utf8");  //字符集设置

	char name[20];
	int pass;
	int i = 1;
	int iChoice;

	list<People> Link;
	People xp;
	mysql_query(conn,"select *from logintable"); //从数据库中获取登录信息
	res = mysql_use_result(conn);  //获得结果集， 一个表

	while((row = mysql_fetch_row(res))!=NULL)
	{
		strcpy(xp.sname,row[1]);
		xp.passwd = atoi(row[2]);
		xp.rank = atoi(row[3]);
		Link.push_back(xp);
               //cout <<row[1] << row[2] <<row[3] <<endl;
	}
       /* list<People>::iterator p1=Link.begin();  //创建容器Link1的迭代器 p;
			while(p1!=Link.end())
			{
				cout << p1->sname;
                                cout << p1->passwd;  cout << p1->rank <<endl;
				p1++;
			}*/
	while(iChoice!=0)
	{
		cout<<"\t***************欢迎进入公司管理系统**************"<<endl;
		cout<<"\t**             1.boss登录                      **"<<endl;
		cout<<"\t**             2.经理登录                      **"<<endl;
		cout<<"\t**             3.销售经理登录                  **"<<endl;
		cout<<"\t**             4.技术人员登录                  **"<<endl;
		cout<<"\t**             5.销售人员登录                  **"<<endl;
		cout<<"\t**             0.退出                          **"<<endl;
		cout<<"\t*************************************************"<<endl;
		cout<<"请输入操作的编号:"<<endl;
		cin>>iChoice;

		if(iChoice==1)   //boss rank=1
		{
			for(i=1;i<4;i++)
			{
			cout<<"\t***************boss登录*************************"<<endl;
			cout<<" 输入姓名:";
			cin>> name;
			cout<<" 输入密码:";
			cin>> pass;
			if((strcmp(name,"boss")==0)&&pass==123)
			{
				bossUI();
				break;
			}
			cout << "输入错误" <<endl;
			}
		}
		else if(iChoice==2)  //经理级别 rank=2;
		{
			for(i=1;i<4;i++)
			{
			cout<<"\t****************经理登录************************"<<endl;
			cout<< "输入姓名:";
			cin>>name;
			cout<< "输入密码:";
			cin>>pass;
			list<People>::iterator p=Link.begin();  //创建容器Link1的迭代器 p;
			while(p!=Link.end())
			{
				if((strcmp(name,p->sname)==0)&&(pass==p->passwd)&&p->rank==2)
				{     
                                  
                                         bossUI();
					//Saleman();
					break;
				}
				p++;
			}
                        if(p!=Link.end())
				break;
			if(p==Link.end())
				cout<< "输入错误" <<endl;
                       }
                 }
		else if(iChoice==3)  //销售经理 rank = 3
		{
			for(i=1;i<4;i++)
			{
			cout<<"\t**********************销售经理登录****************"<<endl;
			cout<<"输入姓名:";
			cin>>name;
			cout<<"输入密码:";
			cin>>pass;
			list<People>::iterator p=Link.begin();
			while(p!=Link.end())
			{
				if((strcmp(name,p->sname)==0)&&(pass==p->passwd)&&p->rank==3)
				{       
                                         bossUI();  
					//Salemanger();
					break;
				}
				p++;
			}
			if(p!=Link.end())
				break;
			if(p==Link.end())
				cout<< "输入错误"<<endl;
			}
		}
		else if(iChoice==4)     //技术人员 rank = 4
		{
			for(i=1;i<4;i++)
			{
			cout<<"\t**********************技术人员登录****************"<<endl;
			cout<<"输入姓名:";
			cin>>name;
			cout<<"输入密码:";
			cin>>pass;
			list<People>::iterator p=Link.begin();
			while(p!=Link.end())
			{
				if((strcmp(name,p->sname)==0)&&(pass==p->passwd)&&p->rank==4)
				{
                                         bossUI();
					//Skillman();
					break;
				}
				p++;
			}
			if(p!=Link.end())
				break;
			if(p==Link.end())
				cout<< "输入错误"<<endl;
			}
		}
                else if(iChoice==5)     //销售人员 rank = 5
		{
			for(i=1;i<4;i++)
			{
			cout<<"\t**********************销售人员登录****************"<<endl;
			cout<<"输入姓名:";
			cin>>name;
			cout<<"输入密码:";
			cin>>pass;
			list<People>::iterator p=Link.begin();  //创建容器Link1的迭代器 p;
			while(p!=Link.end())
			{
				if((strcmp(name,p->sname)==0)&&(pass==p->passwd)&&p->rank==5)
				{     
                               
                                         bossUI();
					//Saleman();
					break;
				}
				p++;
			}
			if(p!=Link.end())
				break;
			if(p==Link.end())
				cout<< "输入错误"<<endl;
			}
		}
                else if(iChoice==0)
                      {
                        break;
                      }
                else
                {
                     cout<<"输入有误！"<<endl;
                }
            mysql_close(conn);
	}
	
	 
}
int main()
{
    LoginUI();

    return 0;
}	
