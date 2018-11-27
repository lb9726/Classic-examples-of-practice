/*************************************************************************
    > File Name: main.cpp
    > Author: wystan
    > Mail: 617020899@qq.com 
    > Created Time: 2015年05月28日 星期四 14时42分47秒
 ************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <list>
#include <climits>
#include <mysql/mysql.h>
#include "company.h"
#include "main.h"
#include <time.h>
#include <iomanip>
#include <stdio.h>
using namespace std;

list<employee*> link;
int check =0;													//to sign the statue is quit or not
MYSQL* conn=NULL;

void login();													//login
int login_account(int num,string pwd);							//check account
void load();													//load data
void connect_sql();												//connect to local mysql


void man_fun(list<employee*>::iterator p);						//sales man function
void manager_fun(list<employee*>::iterator p);					//sales manager function
void boss_fun(list<employee*>::iterator p);						//boss function
	
void save_all();												//save all data
void show_personal(list<employee*>::iterator p);							//show personal  information 
void show_depart(list<employee*>::iterator p);					//show depart  information 
void change_pwd(list<employee*>::iterator p);					//change  password 
void show_depart(list<employee*>::iterator p);					//view depart staff information
void add_man(list<employee*>::iterator p);						//add sales man
void update(list<employee*>::iterator p);						//view depart staff information
void modify_salary(list<employee*>::iterator p,list<employee*>::iterator q);				//modify salary	
void modify_mark(list<employee*>::iterator p);					//modify remark
void del(list<employee*>::iterator p);							//delete an employee
void view_all(list<employee*>::iterator p);						//view all

bool sort_num (const employee *first, const employee * second);			//sort from little to greater by number
bool sort_name (const employee *first,const employee * second);				//sort from little to greater by name
bool sort_depart (const employee *first,const employee * second);		//sort from little to greater by depart
bool sort_lead (const employee *first,const employee * second);			//sort from little to greater by depart
bool sort_any (const employee *first,const employee * second);			//sort from little to greater by depart
time_t convert_string_to_time_t(const std::string & time_string);		//translate string to time_t


void view_all(list<employee*>::iterator p)								//view all information
{	
	while(1)
	{
		system("clear");
		system("tput cup 15 38");	cout<<"\t\t****************************************************"<<endl;
		system("tput cup 16 38");	cout<<"\t\t*             SELECT DISPLAY MODE                  *"<<endl;
		system("tput cup 17 38");	cout<<"\t\t*--------------------------------------------------*"<<endl;
		system("tput cup 18 38");	cout<<"\t\t*               1.BY JOBNUMBER                     *"<<endl;
		system("tput cup 19 38");	cout<<"\t\t*               2.BY NAME                          *"<<endl;
		system("tput cup 20 38");	cout<<"\t\t*               3.BY DEPART                        *"<<endl;
		system("tput cup 21 38");	cout<<"\t\t*               4.BY LEADER                        *"<<endl;
		system("tput cup 22 38");	cout<<"\t\t*               5.ANY MODE                         *"<<endl;
		system("tput cup 23 38");	cout<<"\t\t*               SELECT:                            *"<<endl;
		system("tput cup 24 38");	cout<<"\t\t****************************************************"<<endl;
		system("tput cup 23 73");string select;
		cin>>select;
		if(select == "1")
		{
			link.sort(sort_num);
			break;
		}
		else if(select == "2")
		{
			link.sort(sort_name);
			break;
		}
		else if(select == "3")
		{
			link.sort(sort_depart);
			break;
		}
		else if(select == "4")
		{
			link.sort(sort_lead);
			break;
		}
		else if(select == "5")
		{
			link.sort(sort_any);
			break;
		}
	}
	system("clear");
	p=link.begin();
	cout<<"--------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;

	cout.width(10);	cout<<"JOBNUM |";
	cout.width(19);	cout<<"NAME |";
	cout.width(12);	cout<<"POSITION |";
	cout.width(9);	cout<<"SALARY |";
	cout.width(9);	cout<<"FLAG |";
	cout.width(19);	cout<<"REMARK |";
	cout.width(19);	cout<<"SUPERIOR |";
	cout.width(40);	cout<<"LASTLOGINTIME";
	cout<<endl;
	cout<<"--------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
	while(p!=link.end())
	{
		(*p)->print();
		p++;
	}
	cin.ignore(1000,'\n');
	cin.get();
}

void add_manager(list<employee*>::iterator p)								//add manager
{
	
	employee* ptr =NULL;
	string name;	cout<<"Input name:";	cin>>name;
	string pwd = "www";						
	string pos;
	int flag;

	string mark;	cout<<"Input remark:";		cin>>mark;
	time_t t;	t=time(NULL);
	string g_t;
	char tt[1024]="";
	struct tm *tmper;
	tmper = localtime(&t);
	sprintf(tt,"%d-%d-%d %d:%d:%d",tmper->tm_year+1900,tmper->tm_mon+1,tmper->tm_mday,tmper->tm_hour,tmper->tm_min,tmper->tm_sec);
	g_t = tt;

	string lead = (*p)->get_name();
	float fixed;
	cout<<"Input fixed salary:";	cin>>fixed;
	
	link.sort(sort_num);
	list<employee*>::iterator q =link.begin();

	q=link.begin();
	int number = ((*q)->get_num());	
	while(q!=link.end())
	{
		if( number < ((*q)->get_num()) )
		{
			break;
		}
		q++;
		number++;
	}
	while(1)
	{
		cout<<"\nWHITCH ACCOUNT DO YOU WANT TO ADD:  1.S_MANAGER   2.T_MANAGER\n";
		int select;
		cin>>select;
		if(select == 1)
		{
			flag =2;
			pos = "s_manager";
			ptr=new s_manager(number,name,pwd,pos,fixed,g_t,flag,mark,lead);
			ptr->set_fixed_salary(fixed);
			ptr->set_sales(0);
			ptr->set_salary();
			break;
		}
		else if(select == 2)
		{
			flag = 4;
			pos = "t_manager";
			ptr=new t_manager(number,name,pwd,pos,fixed,g_t,flag,mark,lead);
			break;
		}
	}
	link.push_front(ptr);
	cout<<"ADD MEMBER SUCCESSFUL"<<endl;
	cin.ignore(1000,'\n');
	cin.get();
	save_all();

}

void boss_fun(list<employee*>::iterator p)									//boss function
{
	while(1)
	{
		system("clear");
		system("tput cup 15 38");	cout<<"\t\t****************************************************"<<endl;
		system("tput cup 16 38");	cout<<"\t\t*      CHOOSE THE ITEM YOU WANT TO OPERATOR        *"<<endl;
		system("tput cup 17 38");	cout<<"\t\t*--------------------------------------------------*"<<endl;
		system("tput cup 18 38");	cout<<"\t\t*               1.ADD MANAGER                      *"<<endl;
		system("tput cup 19 38");	cout<<"\t\t*               2.VIEW ALL EMPLOYEE                *"<<endl;
		system("tput cup 20 38");	cout<<"\t\t*               3.DELETE AN EMPLOYEE               *"<<endl;
		system("tput cup 21 38");	cout<<"\t\t*               4.CHANGE PASSWORD                  *"<<endl;
		system("tput cup 22 38");	cout<<"\t\t*               5.RETURN                           *"<<endl;
		system("tput cup 23 38");	cout<<"\t\t*               6.EXIT                             *"<<endl;
		system("tput cup 24 38");	cout<<"\t\t*               SELECT:                            *"<<endl;
		system("tput cup 25 38");	cout<<"\t\t****************************************************"<<endl;
		int select;
		cin.clear();
		cin.sync();
		system("tput cup 24 75");	cin>>select;
		switch(select)
		{
			case 1:
				add_manager(p);
				break;
			case 2:
				view_all(p);
				break;
			case 3:
				del(p);
				break;
			case 4:
				change_pwd(p);
				break;
			case 5:
				return;
				break;
			case 6:
				system("clear");
				exit(0);
				break;
			default:
				break;
		}
	}
}

void del(list<employee*>::iterator p)							//delete an employee
{
	list<employee*>::iterator q=link.begin();
	int number;
	cout<<"INPUT JOBNUM:";
	cin>>number;
	float m_fixed;
	while(q!=link.end())
	{
		if((number == (*q)->get_num()) && ((*p)->get_name() == (*q)->get_lead()) )
		{
			m_fixed = (*p)->get_salary();
			m_fixed = m_fixed - (*q)->get_salary()/5;
			(*p)->set_sales(0);
			(*p)->set_fixed_salary(m_fixed);
			(*p)->set_salary();		
			link.erase(q);
			cout<<"DELETE INFORMATION SUCCESSFULL"<<endl;
			cin.ignore(1000,'\n');
			cin.get();
			break;
		}
		q++;
	}

	if(q == link.end())
	{
		cout<<"NO SUCH EMPLOYEE"<<endl;
		cin.ignore(1000,'\n');
		cin.get();
		return;
	}
	save_all();
}

void modify_salary(list<employee*>::iterator p,list<employee*>::iterator q)						//modify salary	
{
	int time;
	float sales;
	float fixed;
	float m_fixed;
	float s_fixed;
	switch((*p)->get_flag())
	{
		case 1:
			cout<<"Input sales:";	cin>>sales;
			s_fixed = (*p)->get_salary();
			(*p)->set_sales(sales);
			(*p)->set_salary();
			m_fixed = (*q)->get_salary();
			m_fixed = m_fixed - s_fixed/5;
			(*q)->set_fixed_salary(m_fixed);
			(*q)->set_sales(sales);
			(*q)->set_salary();
			break;
		case 2:
			cout<<"Input fixed salary:";	cin>>fixed;
			(*p)->set_fixed_salary(fixed);
			(*p)->set_salary();
			break;
		case 3:
			cout<<"Input worktime:";	cin>>time;
			(*p)->set_worktime(time);
			(*p)->set_salary();
			break;
		case 4:
			cout<<"Input fixed salary:";	cin>>fixed;
			(*p)->set_fixed_salary(fixed);
			(*p)->set_salary();
			break;
		default:
			break;
	}
	cout<<"MODIFY SUCCESSFULL"<<endl;
	cin.ignore(1000,'\n');
	cin.get();
	save_all();
}

void modify_mark(list<employee*>::iterator p)				//modify remark
{
	string mark;
	cout<<"Input remark:";
	cin>>mark;
	(*p)->set_mark(mark);
	cout<<"MODIFY SUCCESSFULL"<<endl;
	cin.ignore(1000,'\n');
	cin.get();
	save_all();
}

void update(list<employee*>::iterator p)					//view depart staff information
{
	int number;
	string name = (*p)->get_name();
	list<employee*>::iterator q=link.begin();
	cout<<"INPUT JOBNUM:";
	cin>>number;
	while(q!=link.end())
	{
		if( number == (*q)->get_num() && name == (*q)->get_lead() )
		{
			break;
		}
		q++;
	}
	if(q==link.end())
	{
		cout<<"NO SUCH STAFF"<<endl;
		cin.ignore(1000,'\n');
		cin.get();
		return;
	}
	system("clear");
	system("tput cup 15 38");	cout<<"\t\t****************************************************"<<endl;
	system("tput cup 16 38");	cout<<"\t\t*      CHOOSE THE ITEM YOU WANT TO MODIFY          *"<<endl;
	system("tput cup 17 38");	cout<<"\t\t*--------------------------------------------------*"<<endl;
	system("tput cup 18 38");	cout<<"\t\t*               1.MODIFY SALARY                    *"<<endl;
	system("tput cup 19 38");	cout<<"\t\t*               2.MODIFY REMARK                    *"<<endl;
	system("tput cup 21 38");	cout<<"\t\t*               3.RETURN                           *"<<endl;
	system("tput cup 20 38");	cout<<"\t\t*               SELECT:                            *"<<endl;
	system("tput cup 21 38");	cout<<"\t\t****************************************************"<<endl;
	int select;
	cin.clear();
	cin.sync();
	system("tput cup 20 75");	cin>>select;
	switch(select)
	{
		case 1:
			modify_salary(q,p);
			break;
		case 2:
			modify_mark(q);
			break;
		case 3:
			return;
		default:
			break;
	}
}

void add_man(list<employee*>::iterator p)						//add sales man
{
	
	employee* ptr =NULL;
	string name;	cout<<"Input name:";	cin>>name;
	string pwd = "www";						
	string pos;
	float d_salary =3000;
	int flag;
	string mark;	cout<<"Input remark:";		cin>>mark;
	string lead	=	(*p)->get_name();
	time_t t;	t=time(NULL);
	string g_t;
	char tt[1024]="";
	struct tm *tmper;
	tmper = localtime(&t);
	sprintf(tt,"%d-%d-%d %d:%d:%d",tmper->tm_year+1900,tmper->tm_mon+1,tmper->tm_mday,tmper->tm_hour,tmper->tm_min,tmper->tm_sec);
	g_t = tt;
	int wt;
	float sale;
	float m_fixed;

	link.sort(sort_num);
	list<employee*>::iterator q =link.begin();

	q=link.begin();
	int number = ((*q)->get_num());	
	while(q!=link.end())
	{
		if( number < ((*q)->get_num()) )
		{
			break;
		}
		q++;
		number++;
	}

	switch((*p)->get_flag())
	{
		case 2:
			flag = 1;
			pos="s_man";
			ptr=new s_man(number,name,pwd,pos,d_salary,g_t,flag,mark,lead);
			cout<<"Input sales:";	cin>>sale;
			ptr->set_sales(sale);
			ptr->set_salary();
			m_fixed = (*p)->get_salary();
			(*p)->set_sales(sale);
			(*p)->set_fixed_salary(m_fixed);
			(*p)->set_salary();
			break;
		case 4:
			flag = 3;
			pos="t_man";
			ptr=new t_man(number,name,pwd,pos,d_salary,g_t,flag,mark,lead);
			cout<<"Input worktime:";	cin>>wt;
			ptr->set_worktime(wt);
			ptr->set_salary();
			break;
		default:
			break;
	}	

	link.push_front(ptr);
	save_all();
	cout<<"ADD STAFF SUCCESSFUL"<<endl;
	cin.ignore(1000,'\n');
	cin.get();
}


void show_depart(list<employee*>::iterator p)					//view depart staff information
{
	string name;
	name = (*p)->get_name();
	p=link.begin();
	system("clear");
	cout<<"--------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
	cout.width(10);	cout<<"JOBNUM |";
	cout.width(19);	cout<<"NAME |";
	cout.width(12);	cout<<"POSITION |";
	cout.width(9); 	cout<<"SALARY |";
	cout.width(9);	cout<<"FLAG |";
	cout.width(19);	cout<<"REMARK |";
	cout.width(19);	cout<<"SUPERIOR |";
	cout.width(40);	cout<<"LASTLOGINTIME |";
	cout<<endl;
	cout<<"--------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
	while(p!=link.end())
	{
		if( (((*p)->get_lead()) == name)  )
		{
			(*p)->print();
		}
		p++;
	}
	cin.ignore(1000,'\n');
	cin.get();
}


void save_all()													//save all data to mysql
{
	list<employee*>::iterator p=link.begin();
	if(mysql_query(conn,"drop table employee"))
	{
		cout<<"mysql error"<<endl;
		exit(1);
	}
	if(mysql_query(conn,"create table employee(no int auto_increment not null primary key,number int not null,name varchar(20) not null,password varchar(20) not null default '1234',position varchar(20) not null,salary float not null,logtime timestamp default current_timestamp,flag tinyint not null,remark varchar(128),leader varchar(20))"))
	{
		cout<<"mysql create error"<<endl;
		exit(1);
	}

	char str[1024]="";
	while(p!=link.end())
	{
		(*p)->save_str(str);
		if(mysql_query(conn,str))
		{
			cout<<"insert data error!"<<endl;
			exit(1);
		}
		p++;
	}
}

void manager_fun(list<employee*>::iterator p)					//sales manager function
{
	while(1)
	{

		system("clear");
		cout<<"\t\t\n\n\n";
		system("tput cup 15 38");	cout<<"\t\t****************************************************"<<endl;
		system("tput cup 16 38");	cout<<"\t\t*           WELCOM TO SALES SYSTEM                 *"<<endl;
		system("tput cup 17 38");	cout<<"\t\t****************************************************"<<endl;
		system("tput cup 18 38");	cout<<"\t\t*         PLEASE CHOOSE YOUR OPPERATION            *"<<endl;
		system("tput cup 19 38");	cout<<"\t\t*--------------------------------------------------*"<<endl;
		system("tput cup 20 38");	cout<<"\t\t*            1.SEE PERSONAL INFORMATION            *"<<endl;
		system("tput cup 21 38");	cout<<"\t\t*            2.VIEW DEPARTMENT STAFF INFORMATION   *"<<endl;
		system("tput cup 22 38");	cout<<"\t\t*            3.ADD STAFF                           *"<<endl;
		system("tput cup 23 38");	cout<<"\t\t*            4.MODIFY EMPLOYEE INFORMATION         *"<<endl;
		system("tput cup 24 38");	cout<<"\t\t*            5.DELETE EMPLOYEE INFORMATION         *"<<endl;
		system("tput cup 25 38");	cout<<"\t\t*            6.CHANGE PASSWORD                     *"<<endl;
		system("tput cup 26 38");	cout<<"\t\t*            7.RETURN                              *"<<endl;
		system("tput cup 27 38");	cout<<"\t\t*            8.EXIT                                *"<<endl;
		system("tput cup 28 38");	cout<<"\t\t*            SELECT:                               *"<<endl;
		system("tput cup 29 38");	cout<<"\t\t****************************************************"<<endl;
		int select;
		cin.clear();
		cin.sync();
		system("tput cup 28 69");	cin>>select;
		switch(select)
		{
			case 1:
				show_personal(p);			//show information of sale manager
				break;
			case 2:
				show_depart(p);				//show depart information
				break;
			case 3:
				add_man(p);
				break;
			case 4:
				update(p);
				break;
			case 5:
				del(p);
				break;
			case 6:
				change_pwd(p);//change sales manager's password
				return;
				break;
			case 7:
				return;
			case 8:					//save all data
				system("clear");
				exit(0);
			default:
				break;
		}
	}
}

void change_pwd(list<employee*>::iterator p)					//change salesman's password 
{
	string pwd;
	string c_pwd;
	while(1)
	{
		cout<<"\nInput new password:";
		system("stty -echo");
		cin>>pwd;
		system("stty echo");
		cout<<"\nInput new password again:";
		system("stty -echo");
		cin>>c_pwd;
		system("stty echo");
		if(pwd == c_pwd)
		{
			(*p)->set_passwd(pwd);
			cout<<"\nCHANGE PASSWORD SUCCESSFUL"<<endl;
			cout<<"Input any key";
			cin.ignore(1000,'\n');
			cin.get();
			break;
		}		
	}
	save_all();
}

void show_personal(list<employee*>::iterator p)						//show saleman's  information 
{
	system("clear");
	cout<<"your information is"<<endl<<endl;
	
	cout<<"--------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
	cout.width(10);	cout<<"JOBNUM |";
	cout.width(19);	cout<<"NAME |";
	cout.width(12);	cout<<"POSITION |";
	cout.width(9);	cout<<"SALARY |";
	cout.width(9);	cout<<"FLAG |";
	cout.width(19);	cout<<"REMARK |";
	cout.width(19);	cout<<"SUPERIOR |";
	cout.width(40);	cout<<"LASTLOGINTIME";
	cout<<endl;
	cout<<"--------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
	(*p)->print();
	cin.ignore(1000,'\n');
	cin.get();
	
}

void man_fun(list<employee*>::iterator p)						//sales man function
{
	while(1)
	{

		system("clear");
		cout<<"\t\t\n\n\n";
		system("tput cup 15 38");	cout<<"\t\t****************************************************"<<endl;
		system("tput cup 16 38");	cout<<"\t\t*           WELCOM TO SALES SYSTEM                 *"<<endl;
		system("tput cup 17 38");	cout<<"\t\t****************************************************"<<endl;
		system("tput cup 18 38");	cout<<"\t\t*         PLEASE CHOOSE YOUR OPPERATION            *"<<endl;
		system("tput cup 19 38");	cout<<"\t\t*--------------------------------------------------*"<<endl;
		system("tput cup 20 38");	cout<<"\t\t*            1.SEE PERSONAL INFORMATION            *"<<endl;
		system("tput cup 21 38");	cout<<"\t\t*            2.CHANGE PASSWORD                     *"<<endl;
		system("tput cup 22 38");	cout<<"\t\t*            3.RETURN                              *"<<endl;
		system("tput cup 23 38");	cout<<"\t\t*            4.EXIT                                *"<<endl;
		system("tput cup 24 38");	cout<<"\t\t*            SELECT:                               *"<<endl;
		system("tput cup 25 38");	cout<<"\t\t****************************************************"<<endl;
		int select;
		cin.clear();
		cin.sync();
		system("tput cup 24 69");	cin>>select;
		switch(select)
		{
			case 1:
				show_personal(p);						//see information
				break;
			case 2:
				change_pwd(p);					//change password
				break;
			case 3:
				return;							//return to login
				break;
			case 4:								//exit program						
				system("clear");
				exit(1);
				break;
			default:
				break;
		}
	}
}


int login_account(int num,string pwd)	//check account
{

	list<employee*>::iterator p = link.begin();
	while(p!=link.end())
	{
		if( (((*p)->get_num()) == num) )		//iterator为指针，容器中也为指针，所以需要用(*p)->
		{
			if( ((*p)->get_pwd())==pwd)
			{
				check = 0;
				break;
			}
			else
			{
				cout<<"password wrong!"<<endl;
				cin.ignore(1000,'\n');
				cin.get();
				check++;
				if(check >= 3)		//3 times wrong ,exit program
				{
					cout<<"you have Input too many times"<<endl;
					cin.get();
					exit(0);
				}
				return 0;
			}
		}
		p++;
	}
	if(p==link.end())
	{
		cout<<"No such account"<<endl;		//find no such account
		cin.ignore(1000,'\n');
		cin.get();
		return 0;
	}
	switch((*p)->get_flag())
	{
		case 0:
			boss_fun(p);
			break;
		case 1:
			man_fun(p);
			break;
		case 2:
			manager_fun(p);
			break;
		case 3:
			man_fun(p);
			break;
		case 4:
			manager_fun(p);
			break;
		default:
			break;
	}
	return 0;
}

void login()	//login
{
	while(1)
	{

		system("clear");
		cout<<"\t\t\n\n\n";
		system("tput cup 15 38");	cout<<"\t\t****************************************************"<<endl;
		system("tput cup 16 38");	cout<<"\t\t*    WELCOME TO USE THE COMPANY MANAGER SYSTEM     *"<<endl;
		system("tput cup 17 38");	cout<<"\t\t****************************************************"<<endl;
		system("tput cup 18 38");	cout<<"\t\t*                PLEASE  LOGIN                     *"<<endl;
		system("tput cup 19 38");	cout<<"\t\t*--------------------------------------------------*"<<endl;
		system("tput cup 20 38");	cout<<"\t\t*       JOBNUMBER:                                 *"<<endl;
		system("tput cup 21 38");	cout<<"\t\t*        PASSWORD:                                 *"<<endl;
		system("tput cup 22 38");	cout<<"\t\t****************************************************"<<endl;
		int l_num;
		string l_pwd;
		cin.clear();
		cin.sync();
		system("tput cup 20 66");	cin>>l_num;
		cin.clear();
		cin.sync();
		system("stty -echo");
		system("tput cup 21 66");	cin>>l_pwd;
		system("stty echo");
		login_account(l_num,l_pwd);
	}
	
}

void connect_sql()	//connect mysql
{
	conn = mysql_init(NULL);
	const char *server = "localhost";
	const char *user = "root";
	const char *password = "341125";
	const char *database ="zhx";
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		cout<<"connect mysql error"<<endl;
		exit(1);
	}
	
	mysql_set_character_set(conn,"utf8");		//set character base
}

void load()		//load data
{
	MYSQL_RES* res;
	MYSQL_ROW row;
	
	employee* p=NULL;
	
	int number;
	string  name;
	string pwd;
	string position;
	float salary;
	string logtime;
	int flag;
	string mark;
	string leader;


	connect_sql();
	if(mysql_query(conn,"select* from employee"))
	{
		cout<<mysql_error(conn)<<endl;
		exit(1);
	}

	res = mysql_use_result(conn);

	while((row = mysql_fetch_row(res))!=NULL)
	{
		number = atoi(row[1]);
		name = row[2];
		pwd = row[3];
		position = row[4];
		salary = atof(row[5]);
		logtime=row[6];
		flag = atoi(row[7]);
		mark = row[8];
		leader = row[9];

		switch(flag)
		{
			case 0:
				p=new boss(number,name,pwd,position,salary,logtime,flag,mark,leader);
				link.push_front(p);
				delete p;
				p= NULL;
				break;
			case 1:
				p=new s_man(number,name,pwd,position,salary,logtime,flag,mark,leader);
				link.push_front(p);
				delete p;
				p=NULL;
				break;
			case 2:
				p=new s_manager(number,name,pwd,position,salary,logtime,flag,mark,leader);
				link.push_front(p);
				delete p;
				p=NULL;
				break;
			case 3:
				p=new t_man(number,name,pwd,position,salary,logtime,flag,mark,leader);
				link.push_front(p);
				delete p;
				p=NULL;
				break;
			case 4:
				p=new t_manager(number,name,pwd,position,salary,logtime,flag,mark,leader);
				link.push_front(p);
				delete p;
				p=NULL;
				break;
			default:
				break;
		}
	}

}

bool sort_any (const employee *first,const employee * second)			//sort from little to greater by depart
{
	bool res;
	if((first->flag) < (second->flag))
	{
		if((first->leader) < (second->leader))
		{
			if((first->number) < (second->number))
			{
				res = true;
			}
			else
			{
				res = false;
			}
		}
	} 
	else
	{
		res = false;
	}
	return res = true?true:false;
}


bool sort_lead (const employee *first,const employee * second)			//sort from little to greater by lead
{
	return (first->leader) < (second->leader)?true:false;
}

bool sort_depart (const employee *first,const employee * second)				//sort from little to greater by depart
{
	return (first->flag) <(second->flag)?true:false;
}

bool sort_num (const employee *first, const employee * second)			//sort from little to greater by number
{
	return (first->number) < (second->number)?true:false;
}

bool sort_name (const employee *first,const employee * second)			//sort from little to greater by name
{
	return (first->name) < (second->name)?true:false;
}

int main()
{
	load();					//load data from mysql

	login();				//login system
	
	return 0;
}




