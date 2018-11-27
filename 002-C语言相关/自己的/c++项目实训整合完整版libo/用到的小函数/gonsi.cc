/*

C++实习报告 小型公司管理系统
　姓名：智慧星
　　学号：06
　　指导老师：xxxxxx
　　日期：2007年1月10日
　　邮箱: xing1xing2@126.com
　　一、 实习目的：
　　1、 握C++语言编程的基础知识。通过编写一个小型公司管理系统，学会简单的面向对象的编程方法，包括类的结构、继承以及了的多态与虚函数、抽象类之间的关系。
　　2、 悉Visual C++6.0的编程环境，通过编译提示、断点调试能够找出常见的错误，并学会模块化程序设计的方法。
　　3、 过实训使自己所学程序设计的知识得到进一步的巩固，为下一步学习新知识做好准备，程后进行的一个理论与实践相结合的重要教学环节，提高编程能力和自学能力，并初步掌握软件开发的基本方法，为进行专业软件开发打下基础
　　二、实习题目：
　　某小型公司，主要有四类人员：经理、兼职技术人员、销售经理和兼职推销员。现在，需要存储这些人员的姓名、编号、级别、当月薪水．计算月薪总额并显示全部信息。
　　 人员编号基数为1000，每输入一个人员信息编号顺序加1。
　　　　程序要有对所有人员提升级别的功能。本例中为简单起见，所有人员的初始级别均为1级。然后进行升级，经理升为4级，兼职技术人员和销售经理升为3级，推销员仍为1级。
　　　　 月薪计算办法是：经理拿固定月薪8000元；兼职技术人员按每小时100元领取月薪； 兼职推销员的月薪按该推销员当月销售额的4％提成；销售经理既拿固定月薪也领取销售提成，固定月薪为5000元，销售提成为所管辖部门当月销售总额的5%。
　　二、 实习过程：
　　1.题目分析：
　　在这个公司中有四类人员：经理、兼职技术人员、销售经理和兼职推销员要存储的信息有姓名、编号、级别、当月薪水．计算月薪总额，由于所有职员有相同的成员如姓名(name).工资(pay).等。所以可将所有信息归纳为一个职员类(employee),将其作为一个抽象基类，然后派生出子类，实现各类人员不同的信息(如工资计算)，
　　 由于销售经理具有销售员和经理的特性，所以销售经理采用多重继承的关系，继承销售员和经理的两个类，为避免二义性将employee定义为虚基类，可用下图表示：
　　
　　在这一题目中假设公司有2名技术员、3名销售员、经理和销售经理各1名，所以用对象数组的方式，利用循环语句来实现人员的输入和输出，整个程序设计如下：
2   源代码：

*/
#include<fstream>
#include<iostream>
#include<string>
#include<iomanip>
#include<stdlib.h>
using namespace std;

//常变量（供修改用）：

const int n1=2,n2=2,n3=4,n4=2;        /*定义公司各类职工人数（方便修改）
     (n1：技术员人数；n2:经理人数；n3：销售员人数；n4:销售经理人数 ）*/
const double m_salary=8000;    //经理固定月工资
const double hourpay=100;    //技术员小时工资
const double basicpay=5000;    //销售经理的底薪
const double s_proportion=4.0/100;  //销售员的工资提成比例
const double sm_proportion=0.5/100;  //销售经理的提成比例


//声明部分：

void menu();      //主菜单
void menu2();      //数据输入二级菜单
void menu3();      //数据打印二级菜单
void data_input();     //数据输入函数
void data_print();     //数据打印
void charthead1();     //制作表头1函数，统计销售额
void charthead2();     //制作表头2函数，数据打印
void chartend();     //制作表尾     
void statistics();     //数据统计
double sm_salary();     //销售经理工资计算
void sm_print();     //销售经理打印数据
void data_find();     //数据查询
void data_save();     //数据备份

ofstream outfile; //打开磁盘文件流对象

string f_name;      //全局变量（查询用）


//定义类：

class Employee          //雇员类（基类）
{
public:
   void input()     //数据输入函数
 {
  cout<<"编号:"; 
  cin>>num;
  cout<<"其姓名:"; 
  cin>>name;
  cout<<"性别(m/w):"; 
  cin>>sex;
  cout<<"年龄:";  
  cin>>age;
 }
    
   void print()     //打印数据函数
 {  
  cout<<"├─────┼─────┼─────┼─────┼─────┤"<<endl;
  cout<<"│"<<setw(6)<<num<<"    │"<<setw(8)<<name<<"  │"<<setw(6)<<sex<<"    │"<<setw(6)
   <<age<<"    │"<<setw(7)<<pay<<"   │"<<endl;  
 }

 void find()      //查询函数
 {
  if(f_name==name)  
  {
     charthead2();
    print();
   chartend();
   cout<<endl;
  }
 }

 void save()      //备份数据函数
 {
  
  outfile<<"├─────┼─────┼─────┼─────┼─────┤"<<endl;
  outfile<<"│"<<setw(6)<<num<<"    │"<<setw(8)<<name<<"  │"<<setw(6)<<sex<<"    │"<<setw(6)
   <<age<<"    │"<<setw(7)<<pay<<"   │"<<endl;  
 }
 

protected: 
  int num;     //职工号
  string name;    //职工姓名
  char sex;     //职工性别
  int age;     //职工年龄
  double pay;     //职工工资
};


class Technician:public Employee     //技术员类（公有继承） 
{
public:
  void input()
 {
  cout<<"技术员的";
  Employee::input();
  cout<<"工作时间:"; 
  cin>>worktime;
 }

  void print()
 { 
 	pay=worktime*hourpay;
    Employee::print();          
 }
  void find()
  {
  Employee::find();
  }
 void save()
 { pay=worktime*hourpay;
   Employee::save();          
 }

protected:
 double worktime;    //工作时间（小时）
};


class Manager:public Employee      //经理类
{
public:
  void input()
 {
  cout<<"经理的";
  Employee::input();
 }

  void print()
 {  pay=m_salary;
  Employee::print();
 }

 void find()
  {
  Employee::find();
 
  }
 void save()
 {  pay=m_salary;
  Employee::save();
 }
};


class Sell_manager:public Employee     //销售经理类
{
public:
  void input()
 { cout<<"销售经理的";
  Employee::input();
 }

  int sm_number()    //调用销售经理职工号
  {
   return num;
  }

   string sm_name()    //调用销售经理姓名
  {
   return name;
  }
 
  void print()
 {
  cout<<"├─────┼─────┼─────┼─────┼─────┤"<<endl;
  cout<<"│"<<setw(6)<<num<<"    │"<<setw(8)<<name<<"  │"<<setw(6)<<sex<<"    │"<<setw(6)
   <<age<<"    │";
 
 }
 void save()
 {
  outfile<<"├─────┼─────┼─────┼─────┼─────┤"<<endl;
  outfile<<"│"<<setw(6)<<num<<"    │"<<setw(8)<<name<<"  │"<<setw(6)<<sex<<"    │"<<setw(6)
   <<age<<"    │";
 }

                  
};


class Seller:public Employee      //销售员类
{
public:
 Seller(){ sold_amount=0;  } //构造函数，销售额初始化为0
  void input()
 {
  cout<<"销售员的";
  Employee::input();
  cout<<"销售额:";   
  cin>>sold_amount;
  cout<<"所属销售经理的编号:";
  cin>>nu;
 }
 void grade()     //销售员业绩输出
 {
  cout<<"├─────┼─────┼─────┤"<<endl;
  cout<<"│"<<setw(6)<<num<<"    │"<<setw(8)<<name<<"  │"<<setw(7)<<sold_amount<<"   │"<<endl;
  
 }

  void print()     
 { pay=sold_amount*s_proportion;
   cout<<"├─────┼─────┼─────┼─────┼─────┼───────────┤"<<endl;
  cout<<"│"<<setw(6)<<num<<"    │"<<setw(8)<<name<<"  │"<<setw(6)<<sex<<"    │"<<setw(6)
   <<age<<"    │"<<setw(7)<<pay<<"   │"<<setw(13)<<nu<<"         │"<<endl;
 } 

  int s_number()     //调用销售员所属销售经理职工号
  {
   return nu;
  }
  double amount()    //调用销售员销售额
  {
   return sold_amount;
  }

 void find()
  { if(f_name==name)
  {cout<<"┌─────┬─────┬─────┬─────┬─────┬───────────┐"<<endl;
   cout<<"│ 职 工 号 │  姓  名  │  性  别  │  年  龄  │   工  资 │   所属部门经理编号   │"<<endl;
   print();
   cout<<"└─────┴─────┴─────┴─────┴─────┴───────────┘";
  }
  }
 void save()     
 { pay=sold_amount*s_proportion;
   outfile<<"├─────┼─────┼─────┼─────┼─────┼───────────┤"<<endl;
  outfile<<"│"<<setw(6)<<num<<"    │"<<setw(8)<<name<<"  │"<<setw(6)<<sex<<"    │"<<setw(6)
   <<age<<"    │"<<setw(7)<<pay<<"   │"<<setw(13)<<nu<<"         │"<<endl;
 } 

protected:
 double sold_amount;    //销售额
 int nu;       //所属销售经理职工号
};


//定义全局对象数组 

 Technician t[n1];    //技术员
 Manager m[n2];     //经理
 Seller s[n3];     //销售员
 Sell_manager sm[n4];   //销售经理（下属若干销售员）


//主函数部分：
int main()       
{
 char n;
 menu();
 for(int i=0;i<1000;i++)   //设定循环次数（便于各项操作的切换及方便查询）
 {
  cin>>n;
  switch(n)
  {
   case'1':    //数据输入
    cout<<endl<<"您所选操作为数据输入，请继续——"<<endl<<endl;    
    data_input();
    cout<<endl;
    menu();
    break;

   case'2':    //数据统计
    cout<<endl<<"您所选操作为数据统计，请继续——"<<endl<<endl;   
    statistics();
    cout<<endl<<"销售经理按工资排序为:"<<'\n'<<endl;
    sm_print();
    cout<<endl;
    menu();
    break;

   case'3':    //数据打印
    cout<<endl<<"您所选操作为数据打印，请继续——"<<endl<<endl;
    cout<<'\a'<<"数据打印中，请等待……"<<'\n'<<'\n'<<endl;
    cout<<"职工基本情况一览表如下："<<'\n'<<endl;;
    data_print();
    cout<<endl<<endl;
    cout<<'\a'<<"——数据打印完毕——"<<'\n'<<'\n'<<endl;
    menu();
    break;
 
   case'4':    //数据查询
    cout<<endl<<"您所选操作为数据查询，请继续——"<<endl<<endl;   
    cout<<"请输入您要查询的职工姓名：   ";
    cin>>f_name;    
    cout<<endl<<"——正在查询，请等待——"<<endl<<endl;   
    cout<<"您查询的信息如下："<<endl<<endl; 
    data_find();
    cout<<endl<<endl;
    menu();
    break;
 
   case'5':    //数据备份
    outfile.open("C++程序设计实习.txt",ios::out); //打开磁盘文件流对象
    cout<<endl<<"您所选操作为数据备份，请继续——"<<endl<<endl;
    outfile<<"职工基本情况一览表如下："<<'\n'<<endl;    
    data_save();
    outfile.close();
    cout<<endl<<endl;
    cout<<'\a'<<"——数据备份完成，请继续——"<<endl<<endl;    
    menu(); 
    break; 
  
   case'0':    //退出系统
    cout<<endl<<"您所选操作为退出系统，请确认——"<<endl<<endl;
    cout<<"     是( y )"<<"   "<<"否( n )     ";
    cin>>n;
    if(n=='y') 
    { cout<<'\n'<<"——请按任意键退出系统——"<<endl;   exit(0); cout<<endl;}
    else   menu();
    break;
   default: 
    cout<<endl<<"——出错！请重新选择操作！ "<<'\n'<<endl;
    menu();
    break;    
  }

 }
 return 0;
}


//自定义函数部分：

void menu()       //菜单函数
{ 
 cout<<"  ★★小型公司工资管理系统★★  "<<endl;
 cout<<"┌──────────────┐"<<endl;
 cout<<"│     请选择您所需的操作     │"<<endl;
 cout<<"│   数据输入：1,并按回车键； │"<<endl;
 cout<<"│   数据统计：2,并按回车键； │"<<endl;
 cout<<"│   数据打印：3,并按回车键； │"<<endl;
 cout<<"│   数据查询：4,并按回车键； │"<<endl;
 cout<<"│   数据备份：5,并按回车键； │"<<endl;
 cout<<"│   退出系统：0,并按回车键； │"<<endl;
 cout<<"└──────────────┘"<<endl;
 cout<<"  请选择一个操作:";

}

void menu2()      //数据输入二级菜单函数
{ 
 cout<<"      ★★小型公司工资管理系统★★   "<<endl;
 cout<<"┌──────────────────┐"<<endl;
 cout<<"│         请选择您所需的操作         │"<<endl;
 cout<<"│   经理数据输入    ：1,并按回车键； │"<<endl;
 cout<<"│   技术员数据输入  ：2,并按回车键； │"<<endl;
 cout<<"│   销售员数据输入  ：3,并按回车键； │"<<endl;
 cout<<"│   销售经理数据输入：4,并按回车键； │"<<endl;
 cout<<"│   返回上一级      ：5,并按回车键； │"<<endl;
 cout<<"└──────────────────┘"<<endl;
 cout<<"  请选择一个操作:";

}

void menu3()      //数据打印二级菜单函数
{
 cout<<"      ★★小型公司工资管理系统★★   "<<endl;
 cout<<"┌──────────────────┐"<<endl;
 cout<<"│         请选择您所需的操作         │"<<endl;
 cout<<"│   经理数据打印    ：1,并按回车键； │"<<endl;
 cout<<"│   技术员数据打印  ：2,并按回车键； │"<<endl;
 cout<<"│   销售员数据打印  ：3,并按回车键； │"<<endl;
 cout<<"│   销售经理数据打印：4,并按回车键； │"<<endl;
 cout<<"│   返回上一级      ：5,并按回车键； │"<<endl;
 cout<<"└──────────────────┘"<<endl;
 cout<<"  请选择一个操作:";
}

void data_input()     //数据输入函数
{
 char p;int i;
 menu2();
 for(int j=0;j<100;j++)
 {
 cin>>p;
 if(p=='5') break;
 else
 {
 switch(p)
 {
 case'1':
  for(i=0;i<n2;i++)
   m[i].input();
   cout<<endl<<"-----------------------------------------------------"<<endl;menu2();break;
 case'2':
  for(i=0;i<n1;i++)
   t[i].input();
   cout<<endl<<"-----------------------------------------------------"<<endl;menu2();break;
 case'3':
  for(i=0;i<n3;i++)
   s[i].input();
   cout<<endl<<"-----------------------------------------------------"<<endl;menu2();break;
 case'4':
  for(i=0;i<n4;i++)
   sm[i].input();
   cout<<endl<<"--------------------------------------------------"<<endl;menu2();break;
 }
 
 }
 }
}


void charthead1()     //制表头1（数据统计用）
{
 cout<<"┌─────┬─────┬─────┐"<<endl;
 cout<<"│职 工 号　│  姓  名  │ 销 售 额 │"<<endl;
}

void charthead2()     //制表头2（数据打印及销售经理数据统计用）
{
 cout<<"┌─────┬─────┬─────┬─────┬─────┐"<<endl;
 cout<<"│ 职 工 号 │  姓  名  │  性  别  │  年  龄  │   工  资 │"<<endl;
}

void chartend()      //制表尾（数据打印及销售经理数据统计用）
{
 cout<<"└─────┴─────┴─────┴─────┴─────┘";
}

  
void statistics()     //数据统计函数
{  int i,j;
 for(i=0;i<n4;i++)
  { double sum=0;
   cout<<endl<<"职工号为 "<<sm[i].sm_number()<<" 销售经理 "<<sm[i].sm_name()
      <<" 下属销售员的业绩为:"<<endl<<endl;
   charthead1();
  for(j=0;j<n3;j++)
   if(s[j].s_number()==sm[i].sm_number())
   {  
    sum=sum+s[j].amount();
    s[j].grade();
   }    
    cout<<"├─────┼─────┴─────┤"<<endl;
    cout<<"│销售额总计│"<<setw(12)<<sum<<"          │"<<endl;
    cout<<"└─────┴───────────┘"<<endl; 
  }
}


double salary[n4];
double sm_salary()     //销售经理工资计算及排序
{
 int i,j;double a ;Sell_manager b;
 for(int k=0;k<n4;k++)
  salary[k]=0;
 for(i=0;i<n4;i++)
 { double sum=0;
  for(j=0;j<n3;j++)
   if(s[j].s_number()==sm[i].sm_number())
   { sum=sum+s[j].amount();
    salary[i]=sum*sm_proportion+basicpay;
   }
 }
 for( j=0;j<n4-1;j++)
  for( i=0;i<n4-1-j;i++)
  if(salary[i]<salary[i+1])
   { a=salary[i+1];salary[i+1]=salary[i];salary[i]=a;
    b=sm[i+1];sm[i+1]=sm[i];sm[i]=b;
   }
  return 0;
}

void sm_print()
{
 sm_salary();
 charthead2();
 for(int i=0;i<n4;i++)
 { sm[i].print();
  cout<<setw(7)<<salary[i]<<"   │"<<endl;
 }
    
 chartend();
 cout<<endl;
}


void data_print()     //数据打印
{       
 char p;int i,j;
 menu2();
 for(j=0;j<100;j++)
 {
  cin>>p;
 if(p=='5') break;
 else
 {
  switch(p)  
  {case'1':
   cout<<endl<<"经理"<<endl;       //经理信息
   charthead2();
   for(i=0;i<n2;i++)
   m[i].print();
   chartend();
   cout<<endl<<endl<<"-----------------------------------------------------------------------"<<endl;
   menu3();break;

  case'2':
   cout<<endl<<"技术员"<<endl;       //技术员信息
   charthead2();
   for(i=0;i<n1;i++)
   t[i].print();
   chartend();
   cout<<endl<<endl<<"-----------------------------------------------------------------------"<<endl; 
   menu3();break;

  case'3':
   cout<<endl<<"销售员"<<endl;       //销售员信息
   cout<<"┌─────┬─────┬─────┬─────┬─────┬───────────┐"<<endl;
   cout<<"│ 职 工 号 │  姓  名  │  性  别  │  年  龄  │   工  资 │   所属部门经理编号   │"<<endl;
   for(i=0;i<n3;i++)
   s[i].print();
   cout<<"└─────┴─────┴─────┴─────┴─────┴───────────┘"; 
   cout<<endl<<endl<<"------------------------------------------------------------------------"<<'\n'<<endl;
   menu3();break;

  case'4':
   cout<<endl<<"销售经理"<<endl;      //销售经理信息
   sm_salary();
   sm_print();
   cout<<endl<<endl<<"-----------------------------------------------------------------------"<<endl<<endl;
   menu3();break; } 
  }
 }
}


void data_find()     //数据查询函数
{ 
	int i;
 for(i=0;i<n1;i++)
  t[i].find();
 for(i=0;i<n2;i++)
  m[i].find();
 for(i=0;i<n3;i++) 
  s[i].find();
 for(i=0;i<n4;i++)
  if(f_name==sm[i].sm_name())
   {  charthead2();
    sm[i].print();
   cout<<setw(7)<<salary[i]<<"   │"<<endl;
   chartend();
   cout<<endl;
   break;
 } 
}

void data_save()     //数据备份函数    
{
int i;
 outfile<<endl<<"技术员"<<endl;       //技术员信息
 outfile<<"┌─────┬─────┬─────┬─────┬─────┐"<<endl;
 outfile<<"│ 职 工 号 │  姓  名  │  性  别  │  年  龄  │   工  资 │"<<endl;
 for(int i=0;i<n1;i++)
  t[i].save();
 outfile<<"└─────┴─────┴─────┴─────┴─────┘";
 outfile<<endl<<endl<<"---------------------------------------------------------------------------"<<endl;

 outfile<<endl<<"经理"<<endl;        //经理信息
 outfile<<"┌─────┬─────┬─────┬─────┬─────┐"<<endl;
 outfile<<"│ 职 工 号 │  姓  名  │  性  别  │  年  龄  │   工  资 │"<<endl;
 for(i=0;i<n2;i++)
  m[i].save();
 outfile<<"└─────┴─────┴─────┴─────┴─────┘";
 outfile<<endl<<endl<<"----------------------------------------------------------------------------"<<endl; 
 
 outfile<<endl<<"销售经理"<<endl;       //销售经理信息
    sm_salary();
 outfile<<"┌─────┬─────┬─────┬─────┬─────┐"<<endl;
 outfile<<"│ 职 工 号 │  姓  名  │  性  别  │  年  龄  │   工  资 │"<<endl;
 for(i=0;i<n4;i++)
 { sm[i].save();
 outfile<<setw(7)<<salary[i]<<"   │"<<endl;}
 outfile<<"└─────┴─────┴─────┴─────┴─────┘";
 outfile<<endl<<endl<<"----------------------------------------------------------------------------"<<endl<<endl;

 outfile<<endl<<"销售员"<<endl;       //销售员信息
 outfile<<"┌─────┬─────┬─────┬─────┬─────┬───────────┐"<<endl;
 outfile<<"│ 职 工 号 │  姓  名  │  性  别  │  年  龄  │   工  资 │   所属部门经理编号   │"<<endl;
 for(i=0;i<n3;i++)
  s[i].save();
 outfile<<"└─────┴─────┴─────┴─────┴─────┴───────────┘";  
 outfile<<endl<<endl<<"-----------------------------------------------------------------------------"<<'\n'<<endl;
}




