/*************************************************************************
  > File Name: company.h
  > Author: wystan
  > Mail: 617020899@qq.com 
  > Created Time: 2015年05月28日 星期四 08时46分36秒
 ************************************************************************/
#ifndef _COMPANY_H
#define _COMPANY_H

#include <iostream>
using namespace std;
class employee
{
	protected:
		int number;
		string name;
		string password;
		string position;
		float salary;
		string logtime;
		int flag;
		string mark;
		string leader;

	public:
		employee(int n,string nam,string pwd,string pos,float sl,string t,int flg,string mk,string lead);	//structural function
		employee();												//structural function of null
	
		void set_nu(const int &nu,const string &na);			//set number and name,they can't be changed
		void set_passwd(const string &pwd);						//set password
		void set_pos(const string &pos);						//set position
		void set_logt(const string &t);							//set last login time
		void set_flag(const int &f);							//set flag
		void set_mark(const string &mk);						//set remark
		void set_leader(const string &ld);						//set leader

		int get_num();											//get number
		string get_name();										//get name
		string get_pwd();										//get password
		int get_flag();											//get flag
		string get_lead();										//get leader
		float get_salary();										//get salary
		
		void print();											//display information
			
		void save_str(char *savestr);								//save data to mysql

		virtual void set_salary()=0;							//set salary
		virtual void set_sales(const float &sal)=0;				//set sale valume			
		virtual void set_worktime(const int &t)=0;				//set worktime
		virtual void set_fixed_salary(const float &f)=0;		//set fixed salary
		virtual float get_sales()=0;							//get sales
		
		friend bool sort_num (const employee *first, const employee * second);			//sort from little to greater by number
		friend bool sort_name (const employee *first,const employee * second);			//sort from little to greater by name
		friend bool sort_depart (const employee *first,const employee * second);		//sort from little to greater by depart	
		friend bool sort_lead (const employee *first,const employee * second);			//sort from little to greater by depart
		friend bool sort_any (const employee *first,const employee * second);			//sort from little to greater by depart
};

class boss:public employee
{
	public:
	boss(int n,string nam,string pwd,string pos,float sl,string t,int flg,string mk,string lead);	//structural function
	boss();
	virtual void set_salary();								//set salary
	virtual void set_sales(const float &sal);					//set sale valume
	virtual void set_worktime(const int &t);				//set worktime
	virtual void set_fixed_salary(const float &f);			//set fixed salary
	virtual float get_sales();							//get sales
};

class s_man:public employee
{
	private:
		float sales;
	public:
		s_man(int n,string nam,string pwd,string pos,float sl,string t,int flg,string mk,string lead);	//structural function
		s_man();												//structural function of null
		virtual void set_salary();								//set salary
		virtual void set_sales(const float &sal);					//set sale valume
		virtual void set_worktime(const int &t);				//set worktime
		virtual void set_fixed_salary(const float &f);			//set fixed salary
		virtual float get_sales();							//get sales

};

class s_manager:public employee
{
	private:
		float m_sales;
		float fixed;
	public:
		s_manager(int n,string nam,string pwd,string pos,float sl,string t,int flg,string mk,string lead);	//structural function
		s_manager();												//structural function of null
		virtual void set_salary();								//set salary
		virtual void set_sales(const float &sal);					//set sale valume
		virtual void set_worktime(const int &t);				//set worktime
		virtual void set_fixed_salary(const float &f);			//set fixed salary
		virtual float get_sales();							//get sales

};

class t_man:public employee
{
	private:
		int worktime;
	public:
		t_man(int n,string nam,string pwd,string pos,float sl,string t,int flg,string mk,string lead);	//structural function
		t_man();												//structural function of null
		virtual void set_salary();								//set salary
		virtual void set_sales(const float &sal);					//set sale valume
		virtual void set_worktime(const int &t);				//set worktime
		virtual void set_fixed_salary(const float &f);			//set fixed salary
		virtual float get_sales();							//get sales

};

class t_manager:public employee
{	
	private:
		float fixed;											//fixed salary
	public:
		t_manager(int n,string nam,string pwd,string pos,float sl,string t,int flg,string mk,string lead);	//structural function
		t_manager();												//structural function of null
		virtual void set_salary();								//set salary
		virtual void set_sales(const float &sal);				//set sale valume
		virtual void set_worktime(const int &t);				//set worktime
		virtual void set_fixed_salary(const float &f);			//set fixed salary
		virtual float get_sales();								//get sales
};


#endif
