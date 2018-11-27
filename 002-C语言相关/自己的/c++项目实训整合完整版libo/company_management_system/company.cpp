/*************************************************************************
    > File Name: company.cpp
    > Author: wystan
    > Mail: 617020899@qq.com 
    > Created Time: 2015年05月28日 星期四 11时18分36秒
 ************************************************************************/

#include "company.h"
#include <stdio.h>
#include <time.h>
#include <iomanip>

using namespace std;

boss::boss(int n,string nam,string pwd,string pos,float sl,string t,int flg,string mk,string lead)	//structural function for employee
{
	number = n;
	name = nam;
	password = pwd;
	position = pos;
	salary = sl;
	logtime = t;
	flag = flg;
	mark = mk;
	leader = lead;
}

boss::boss()												//structural function of null for employee
{

}

employee::employee(int n,string nam,string pwd,string pos,float sl,string t,int flg,string mk,string lead)	//structural function for employee
{
	number = n;
	name = nam;
	password = pwd;
	position = pos;
	salary = sl;
	logtime = t;
	flag = flg;
	mark = mk;
	leader = lead;
}

employee::employee()												//structural function of null for employee
{

}

s_man::s_man(int n,string nam,string pwd,string pos,float sl,string t,int flg,string mk,string lead)	//structural function for sales man
{
	number = n;
	name = nam;
	password = pwd;
	position = pos;
	salary = sl;
	logtime = t;
	flag = flg;
	mark = mk;
	leader = lead;
}

s_man::s_man()												//structural function of null for sales man
{

}

s_manager::s_manager(int n,string nam,string pwd,string pos,float sl,string t,int flg,string mk,string lead)	//structural function for sales manager
{
	number = n;
	name = nam;
	password = pwd;
	position = pos;
	salary = sl;
	logtime = t;
	flag = flg;
	mark = mk;
	leader = lead;
}

s_manager::s_manager()									//structural function of null for sales manager
{

}

t_man::t_man(int n,string nam,string pwd,string pos,float sl,string t,int flg,string mk,string lead)	//structural function for technical man
{
	number = n;
	name = nam;
	password = pwd;
	position = pos;
	salary = sl;
	logtime = t;
	flag = flg;
	mark = mk;
	leader = lead;
}

t_man::t_man()												//structural function of null for technical man
{

}

t_manager::t_manager(int n,string nam,string pwd,string pos,float sl,string t,int flg,string mk,string lead)	//structural function for technical manager
{
	number = n;
	name = nam;
	password = pwd;
	position = pos;
	salary = sl;
	logtime = t;
	flag = flg;
	mark = mk;
	leader = lead;
}

t_manager::t_manager()										//structural function of null for technical manager
{

}



int employee::get_num()										//get number
{
	return number;
}

string employee::get_name()									//get name
{
	return name;
}

string employee::get_pwd()									//get password
{
	return password;
}

int employee::get_flag()									//get flag
{
	return flag;
}

string employee::get_lead()									//get leader
{
	return leader;
}

float employee::get_salary()										//get salary
{
	return salary;
}

/***************employee function***********************/

void employee::set_nu(const int &nu,const string &na)		//set number and name
{
	number = nu;
	name = na;
}

void employee::set_passwd(const string &pwd)				//set password
{
	password = pwd;
}

void employee::set_pos(const string &pos)					//set position
{
	position = pos;
}

void employee::set_logt(const string &t)					//set last login time
{
	logtime = t;
}

void employee::set_flag(const int &f)						//set flag
{
	flag = f;
}

void employee::set_mark(const string &mk)					//set remark
{
	mark = mk;
}

void employee::set_leader(const string &ld)					//set leader name
{
	leader = ld;
}

void employee::save_str(char *savestr)										//save information to mysql
{
	sprintf(savestr,"insert into employee (number,name,password,position,salary,logtime,flag,remark,leader) values (%d,'%s','%s','%s',%f,'%s',%d,'%s','%s')",
			number,name.c_str(),password.c_str(),position.c_str(),
			salary,logtime.c_str(),flag,mark.c_str(),leader.c_str());
}

void employee::print()											//display information
{

	cout.width(8);	cout<<number<<" |";
	cout.width(17);	cout<<name<<" |";
	cout.width(10);	cout<<position<<" |";
	cout.width(7); cout<<setiosflags(ios::fixed)<<setprecision(1); cout<<salary<<" |";	
	cout.width(7);	cout<<flag<<" |";
	cout.width(17);	cout<<mark<<" |";
	cout.width(17);	cout<<leader<<" |";
	cout.width(40);	cout<<logtime<<" |"<<endl;;
	cout<<"--------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
}


//sales man's salary
void s_man::set_salary()							//set salary
{
	salary = sales*0.1;
}

void s_man::set_sales(const float &sal)				//set sale valume
{
	sales = sal;
}

void s_man::set_worktime(const int &t)				//set worktime
{

}

void s_man::set_fixed_salary(const float &f)		//set fixed salary
{

}

float s_man::get_sales()							//get sales
{
	return sales;
}

//sales manager's salary
void s_manager::set_salary()							//set salary
{
	salary = fixed + m_sales*0.02;
}

void s_manager::set_sales(const float &sal)				//set sale valume
{
	m_sales = sal;
}

void s_manager::set_worktime(const int &t)				//set worktime
{

}

void s_manager::set_fixed_salary(const float &f)		//set fixed salary
{
	fixed = f;
}

float s_manager::get_sales()							//get sales
{
	return m_sales;
}

//technical man's salary
void t_man::set_salary()							//set salary
{
	salary = worktime*22.5;
}

void t_man::set_sales(const float &sal)				//set sale valume
{

}

void t_man::set_worktime(const int &t)				//set worktime
{
	worktime = t;
}

void t_man::set_fixed_salary(const float &f)		//set fixed salary
{

}

float t_man::get_sales()							//get sales
{
	return 0;
}

//technical manager's salary
void t_manager::set_salary()							//set salary
{
	salary = fixed;
}

void t_manager::set_sales(const float &sal)				//set sale valume
{

}

void t_manager::set_worktime(const int &t)				//set worktime
{
	
}

void t_manager::set_fixed_salary(const float &f)		//set fixed salary
{
	fixed = f;
}

float t_manager::get_sales()							//get sales
{
	return 0;
}


//boss
void boss::set_salary()							//set salary
{
}

void boss::set_sales(const float &sal)				//set sale valume
{
}

void boss::set_worktime(const int &t)				//set worktime
{

}

void boss::set_fixed_salary(const float &f)		//set fixed salary
{

}

float boss::get_sales()							//get sales
{
	return 0;
}




















