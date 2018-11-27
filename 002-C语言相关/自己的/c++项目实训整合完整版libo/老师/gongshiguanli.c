//经理级别 1  技术人员11  销售经理 2  销售人员22
//#include<limits>
#include<iostream>
#include<list>
#include<algorithm>
#include<stdlib.h>
using namespace std;
#include<string.h>
#include<mysql/mysql.h>
#include<stdio.h>
//void xianshi(int a);
class people{
	public:
		void find(int x);
		void change(int x);
		void tianjia(int x);
		void xianshi(int x);
		void del(int x);
		people(){}
		char sname[20],sex[6];
		int bian,jibie,isuse,password,xin;
};
class jingli:public people{
	public:
		void find1(int x);
		void change1(int x);
		void tianjia1(int x);
		void xianshi1(int x);
		void del1(int x);
		void jiesuan1(int x);
		jingli(){}
};
class xiaoshou:public people{
	public:
		void find2(int x);
		void change2(int x);
		void tianjia2(int x);
		void xianshi2(int x);
		void del2(int x);
		void jiesuan2(int x);
		
};
using namespace std;
MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;

//////////////////////////////////////////////////////  老板界面 ///////////////////////////////////////////////////////////////

void people::find(int x)
{
	int r=1;
	int wq=1;
	int fg;
	char asd[100];
		if(x==1)
		{
			while(r==1){
			if(wq==1)
			{
				cout<<"输入要查找的编号:";
				cin>>fg;
				sprintf(asd,"select * from go1 where isuse =1 and bian=%d",fg);
				mysql_query(conn,asd);
				res=mysql_use_result(conn);
				if((row=mysql_fetch_row(res))!=NULL)
				{
					printf("\t编号\t姓名\t性别\t级别\t薪水\n");
					printf("\t%s\t%s\t%s\t%s\t%s\n",row[0],row[1],row[2],row[3],row[4]);
				}
				else
				{
				cout<<"你输入的编号不存在！\n";
				}
				mysql_free_result(res);
			}
			cout<<"是否继续查找?(输入1继续):";
			cin>>r;
			}
		}
		
	
}
void people::change(int x)
{
	int r=1;
	char zx[100];
	int q;
	int qwe[10];
	while(r==1)//是否继续操作
	{
		if(x==1)//boss的操作
		{
			cout<<"请输入修改内容:\n1.级别 2.薪水 3.密码\n";
			cin>>q;
			if(q==1)
			{
				list<people> lp;
				people k;
				cout<<"输入要修改的编号:";
				cin>>qwe[0];
				mysql_query(conn,"select bian,sname,isuse from go1 order by bian asc");
				res=mysql_use_result(conn);
				while((row=mysql_fetch_row(res))!=NULL)
				{
					k.bian=atoi(row[0]);
					strcpy(k.sname,row[1]);
					k.isuse=atoi(row[2]);
					lp.push_back(k);
				}
				list<people>::iterator ui=lp.begin();
				while(ui!=lp.end())
				{
					if((qwe[0]==ui->bian)&&(ui->isuse==1)){
						cout<<"输入修改后的级别:(经理级别为1 技术人员级别为11 销售经理级别为2 销售人员级别为22)\n";
						cin>>qwe[1];
						sprintf(zx,"update go1 set jibie=%d where bian = %d",qwe[1],qwe[0]);
						mysql_query(conn,zx);
						cout<<"修改成功!\n";
						break;
					}
					ui++;
				}
				if(ui==lp.end()){
					cout<<"无此编号的员工"<<endl;}
				mysql_free_result(res);
			}
			else if(q==2)
			{
				list<people> lp;
				people k;
				cout<<"输入要修改的编号:";
				cin>>qwe[0];
				mysql_query(conn,"select bian,sname,isuse from go1 order by bian asc");
				res=mysql_use_result(conn);
				while((row=mysql_fetch_row(res))!=NULL)
				{
					k.bian=atoi(row[0]);
					strcpy(k.sname,row[1]);
					k.isuse=atoi(row[2]);
					lp.push_back(k);
				}
				list<people>::iterator ui=lp.begin();
				while(ui!=lp.end())
				{
					if((qwe[0]==ui->bian)&&(ui->isuse==1)){
						cout<<"输入修改后的薪水:";
						cin>>qwe[1];
						sprintf(zx,"update go1 set xin=%d where bian = %d",qwe[1],qwe[0]);
						mysql_query(conn,zx);
						cout<<"修改成功!\n";
						break;
					}
					ui++;
				}
				if(ui==lp.end()){
					cout<<"无此编号的员工"<<endl;}
				mysql_free_result(res);
			}
			else if(q==3)
			{
			list<people> lp;
				people k;
				cout<<"输入要修改的编号:";
				cin>>qwe[0];
				mysql_query(conn,"select bian,sname,isuse from go1 order by bian asc");
				res=mysql_use_result(conn);
				while((row=mysql_fetch_row(res))!=NULL)
				{
					k.bian=atoi(row[0]);
					strcpy(k.sname,row[1]);
					k.isuse=atoi(row[2]);
					lp.push_back(k);
				}
				list<people>::iterator ui=lp.begin();
				while(ui!=lp.end())
				{
					if((qwe[0]==ui->bian)&&(ui->isuse==1)){
						cout<<"输入修改后的密码（默认为123456）:";
						cin>>qwe[1];
						sprintf(zx,"update go1 set password=%d where bian = %d",qwe[1],qwe[0]);
						mysql_query(conn,zx);
						cout<<"修改成功!\n";
						break;
					}
					ui++;
				}
				if(ui==lp.end()){
					cout<<"无此编号的员工"<<endl;}
				mysql_free_result(res);
			}
			else{cout<<"输入有误！";}
		}
		cout<<"是否继续修改?(输入1继续):";
		cin>>r;
	}
}
void people::del(int x)
{
	int q;
	int qwe;
	char name[100];
	char rt[100];
	int r=1;
	while(r==1)//是否进行第二次操作
	{
		if(x==1)//boss的操作
		{
			list<people> lo;
			people vg;
			cout<<"按什么进行删除?\n1.编号\n2.姓名\n";
			cin>>q;
			if(q==1)
			{
				cout<<"输入要删除员工的编号:";
				cin>>qwe;
				mysql_query(conn,"select bian,sname,isuse from go1 order by bian asc");
				res=mysql_use_result(conn);
				while((row=mysql_fetch_row(res))!=NULL)
				{
					vg.bian=atoi(row[0]);
					strcpy(vg.sname,row[1]);
					vg.isuse=atoi(row[2]);
					lo.push_back(vg);
				}
				list<people>::iterator oo=lo.begin();
				while(oo!=lo.end())
				{
					if((qwe==oo->bian)&&(oo->isuse==1)){
						oo->isuse=0;
						sprintf(rt,"update go1 set isuse=0 where bian=%d",oo->bian);
						mysql_query(conn,rt);
						cout<<"删除成功！\n";
						break;
					}
					oo++;
				}
				if(oo==lo.end()){
					cout<<"无此编号的员工！\n";
				}
				mysql_free_result(res);
			}
			else if(q==2)
			{
				cout<<"输入要删除员工的姓名:";
				cin>>name;
				mysql_query(conn,"select bian,sname,isuse from go1 order by bian asc");
				res=mysql_use_result(conn);
				while((row=mysql_fetch_row(res))!=NULL)
				{
					vg.bian=atoi(row[0]);
					strcpy(vg.sname,row[1]);
					vg.isuse=atoi(row[2]);
					lo.push_back(vg);
				}
				list<people>::iterator oo=lo.begin();
				while(oo!=lo.end())
				{
					if(strcmp(name,oo->sname)==0 && oo->isuse==1){
						oo->isuse=0;
						sprintf(rt,"update go1 set isuse=0 where sname='%s'",oo->sname);
						mysql_query(conn,rt);
						cout<<"删除成功！\n";
						break;
					}
					oo++;
				}
				if(oo==lo.end()){
					cout<<"无此姓名的员工！\n";
				}
				mysql_free_result(res);
			}
			else 
			{
				cout<<"输入错误！\n";

			}
		}
	cout<<"是否继续删除?(1继续):";
	cin>>r;
	}
}
void people::tianjia(int x)
{
	int q=1;
	int w;
	char sdf[100];
	char sf[100];
	if(x==1){
		cout<<" 请选择添加的职位：\n1.经理（级别请设置为1）\n2.销售经理（级别请设置为2） \n3.兼职技术人员（级别请设置为11）\n4.兼职推销员（级别请设置为22）\n";
		cin>>w;
		if(w==1||w==2||w==3||w==4){
			people a;
			list<people> link;
			mysql_query(conn,"select bian,sname,sex,jibie,xin,isuse from go1  where isuse =0 order by bian asc");
			res=mysql_use_result(conn);
			while((row=mysql_fetch_row(res))!=NULL)
			{
				a.bian = atoi(row[0]);
				strcpy(a.sname,row[1]);
				strcpy(a.sex,row[2]);
				a.jibie=atoi(row[3]);
				a.xin=atoi(row[4]);
				link.push_back(a);
			}
			list<people>::iterator we =link.begin();
			if(link.size()!=0){
			while((q==1)&&(we!=link.end())){
			cout<<"输入姓名:";
			cin>>we->sname;
			cout<<"输入性别:";
			cin>>we->sex;
			cout<<"输入级别:";
			cin>>we->jibie;
			cout<<"输入薪水:";
			cin>>we->xin;
			we->isuse=1;
			cout<<"添加成功！\n";
			cout<<"是否继续添加？(输入1继续):";
			cin>>q;
			we++;
			}
			we = link.begin();
			while(we!=link.end())
			{
				sprintf(sdf,"update go1 set sname ='%s',sex='%s',jibie=%d,xin=%d,isuse=%d where bian=%d",we->sname,we->sex,we->jibie,we->xin,we->isuse,we->bian);
				mysql_query(conn,sdf);
				we++;
			}
			}
			list<people> li;
			people b;
			while(q==1)
			{
				cout<<"输入姓名:";
				cin>>b.sname;
				cout<<"输入性别:";
				cin>>b.sex;
				cout<<"输入级别:";
				cin>>b.jibie;
				cout<<"输入薪水:";
				cin>>b.xin;
				li.push_back(b);
				cout<<"添加成功！";
				cout<<"是否继续添加?(输入1继续):";
				cin>>q;
			}
			list<people>::iterator om=li.begin();
			while(om!=li.end())
			{
				sprintf(sf,"insert into go1(sname,sex,jibie,xin) values ('%s','%s',%d,%d)",om->sname,om->sex,om->jibie,om->xin);
				mysql_query(conn,sf);
				om++;
			}
			mysql_free_result(res);
		}
		else
		{cout<<"输入有误！\n";
					}
	}
}

void people::xianshi(int a)
{
	int sa;
	if(a==1){
		cout<<"---1.按编号顺序显示\t2.按级别顺序显示----"<<endl;
		cin>>sa;
		if(sa==1){
			mysql_query(conn,"select * from go1 where isuse=1  order by bian asc");
			res=mysql_use_result(conn);
			cout<<"\t编号\t姓名\t性别\t级别\t薪水"<<endl;
			while((row=mysql_fetch_row(res))!=NULL){
				printf("\t%s\t%s\t%s\t%s\t%s\n",row[0],row[1],row[2],row[3],row[4]);
			}
			mysql_free_result(res);
		}
		else if(sa==2){
			mysql_query(conn,"select * from go1 where isuse=1 order by jibie asc");
			res=mysql_use_result(conn);
			cout<<"\t编号\t姓名\t性别\t级别\t薪水"<<endl;;
			while((row=mysql_fetch_row(res))!=NULL){
				printf("\t%s\t%s\t%s\t%s\t%s\n",row[0],row[1],row[2],row[3],row[4]);
			}
			mysql_free_result(res);
		}
		else 
		{
		cout<<"输入错误！\n";	
		}
	}

}

void boss()
{	int x=1;
	people cv;
	while(x!=0){
	cout<<"***********************老板界面**************************"<<endl;
	cout<<"1.添加人员\n2.删除人员\n3.修改人员信息\n4.查找人员信息\n5.显示所有员工\n0.返回主界面"<<endl;
	cin>>x;
	switch(x){
		case 1:
			cv.tianjia(1);
			break;
		case 2:
			cv.del(1);
			break;
		case 3:
			cv.change(1);
			break;
		case 4:
			cv.find(1);
			break;
		case 5:
			cv.xianshi(1);
			break;
		case 0:
			break;
		default:
			cout<<"输入有误！请重新输入\n";
			break;
	}
	}
}

///////////////////////////////////////   经理界面 /////////////////////////////////////////////////////////////////////////

void jingli::tianjia1(int x)
{
	int q=1;
	int w;
	char sdf[100];
	char sf[100];
	if(x==1){
		
			jingli a;
			list<jingli> link;
			mysql_query(conn,"select bian,sname,sex,jibie,xin,isuse from go1  where isuse =0 order by bian asc");
			res=mysql_use_result(conn);
			while((row=mysql_fetch_row(res))!=NULL)
			{
				a.bian = atoi(row[0]);
				strcpy(a.sname,row[1]);
				strcpy(a.sex,row[2]);
				a.jibie=atoi(row[3]);
				a.xin=atoi(row[4]);
				link.push_back(a);
			}
			list<jingli>::iterator we =link.begin();
			if(link.size()!=0){
			while((q==1)&&(we!=link.end())){
			cout<<"输入姓名:";
			cin>>we->sname;
			cout<<"输入性别:";
			cin>>we->sex;
			we->isuse=1;
			cout<<"添加成功！\n";
			cout<<"是否继续添加？(输入1继续):";
			cin>>q;
			we++;
			}
			we = link.begin();
			while(we!=link.end())
			{
				sprintf(sdf,"update go1 set sname ='%s',sex='%s',jibie=11,xin=0,isuse=%d where bian=%d",we->sname,we->sex,we->isuse,we->bian);
				mysql_query(conn,sdf);
				we++;
			}
			}
			list<jingli> li;
			jingli b;
			while(q==1)
			{
				cout<<"输入姓名:";
				cin>>b.sname;
				cout<<"输入性别:";
				cin>>b.sex;
				li.push_back(b);
				cout<<"添加成功！";
				cout<<"是否继续添加?(输入1继续):";
				cin>>q;
			}
			list<jingli>::iterator om=li.begin();
			while(om!=li.end())
			{
				sprintf(sf,"insert into go1(sname,sex,jibie,xin) values ('%s','%s',11,0)",om->sname,om->sex);
				mysql_query(conn,sf);
				om++;
			}

		mysql_free_result(res);
	}
}

void jingli::del1(int x)
{
	int q;
	int qwe;
	char name[100];
	char rt[100];
	int r=1;
	while(r==1)//是否进行第二次操作
	{
		if(x==1)//boss的操作
		{
			list<people> lo;
			people vg;
			cout<<"按什么进行删除?\n1.编号\n2.姓名\n";
			cin>>q;
			if(q==1)
			{
				cout<<"输入要删除技术员工的编号:";
				cin>>qwe;
				mysql_query(conn,"select bian,sname,isuse from go1 where jibie=11 order by bian asc");
				res=mysql_use_result(conn);
				while((row=mysql_fetch_row(res))!=NULL)
				{
					vg.bian=atoi(row[0]);
					strcpy(vg.sname,row[1]);
					vg.isuse=atoi(row[2]);
					lo.push_back(vg);
				}
				list<people>::iterator oo=lo.begin();
				while(oo!=lo.end())
				{
					if((qwe==oo->bian)&&(oo->isuse==1)){
						oo->isuse=0;
						sprintf(rt,"update go1 set isuse=0 where bian=%d",oo->bian);
						mysql_query(conn,rt);
						cout<<"删除成功！\n";
						break;
					}
					oo++;
				}
				if(oo==lo.end()){
					cout<<"无此编号的技术员工！\n";
				}
			}
			else if(q==2)
			{
				cout<<"输入要删除技术员工的姓名:";
				cin>>name;
				mysql_query(conn,"select bian,sname,isuse from go1 where jibie=11 order by bian asc");
				res=mysql_use_result(conn);
				while((row=mysql_fetch_row(res))!=NULL)
				{
					vg.bian=atoi(row[0]);
					strcpy(vg.sname,row[1]);
					vg.isuse=atoi(row[2]);
					lo.push_back(vg);
				}
				list<people>::iterator oo=lo.begin();
				while(oo!=lo.end())
				{
					if(strcmp(name,oo->sname)==0 && oo->isuse==1){
						oo->isuse=0;
						sprintf(rt,"update go1 set isuse=0 where sname='%s'",oo->sname);
						mysql_query(conn,rt);
						cout<<"删除成功！\n";
						break;
					}
					oo++;
				}
				if(oo==lo.end()){
					cout<<"无此姓名的技术员工！\n";
				}
			}
			else 
			{
				cout<<"输入错误！\n";

			}
		}
	mysql_free_result(res);
	cout<<"是否继续删除?(1继续):";
	cin>>r;
	}
}

void jingli::change1(int x)
{
	int r=1;
	char zx[100];
	int q;
	int qwe[10];
	while(r==1)//是否继续操作
	{
		if(x==1)//boss的操作
		{
			cout<<"请输入修改内容:\n 1.薪水 2.密码\n";
			cin>>q;
			if(q==1)
			{
				list<people> lp;
				people k;
				cout<<"输入要修改技术员工的编号:";
				cin>>qwe[0];
				mysql_query(conn,"select bian,sname,isuse from go1 where jibie=11 order by bian asc");
				res=mysql_use_result(conn);
				while((row=mysql_fetch_row(res))!=NULL)
				{
					k.bian=atoi(row[0]);
					strcpy(k.sname,row[1]);
					k.isuse=atoi(row[2]);
					lp.push_back(k);
				}
				list<people>::iterator ui=lp.begin();
				while(ui!=lp.end())
				{
					if((qwe[0]==ui->bian)&&(ui->isuse==1)){
						cout<<"输入修改后的薪水:";
						cin>>qwe[1];
						sprintf(zx,"update go1 set xin=%d where bian = %d",qwe[1],qwe[0]);
						mysql_query(conn,zx);
						cout<<"修改成功!\n";
						break;
					}
					ui++;
				}
				if(ui==lp.end()){
					cout<<"无此编号的技术员工"<<endl;}
			}
			else if(q==2)
			{
			list<people> lp;
				people k;
				cout<<"输入要修改技术员工的编号:";
				cin>>qwe[0];
				mysql_query(conn,"select bian,sname,isuse from go1 where jibie=11 order by bian asc");
				res=mysql_use_result(conn);
				while((row=mysql_fetch_row(res))!=NULL)
				{
					k.bian=atoi(row[0]);
					strcpy(k.sname,row[1]);
					k.isuse=atoi(row[2]);
					lp.push_back(k);
				}
				list<people>::iterator ui=lp.begin();
				while(ui!=lp.end())
				{
					if((qwe[0]==ui->bian)&&(ui->isuse==1)){
						cout<<"输入修改后的密码（默认为123456）:";
						cin>>qwe[1];
						sprintf(zx,"update go1 set password=%d where bian = %d",qwe[1],qwe[0]);
						mysql_query(conn,zx);
						cout<<"修改成功!\n";
						break;
					}
					ui++;
				}
				if(ui==lp.end()){
					cout<<"无此编号的技术员工"<<endl;}
			}
			else{cout<<"输入有误！";}
		}
		mysql_free_result(res);
		cout<<"是否继续修改?(输入1继续):";
		cin>>r;
	}
}

void jingli::find1(int x)
{
	int r=1;
	int wq=1;
	int fg;
	char asd[100];
		if(x==1)
		{
			while(r==1){
			if(wq==1)
			{	
				
				cout<<"输入要查找的技术员工编号:";
				cin>>fg;
				sprintf(asd,"select * from go1 where (jibie=11) and (isuse =1) and (bian=%d)",fg);
				mysql_query(conn,asd);
				res=mysql_use_result(conn);
				if((row=mysql_fetch_row(res))!=NULL)
				{
					printf("\t编号\t姓名\t性别\t级别\t薪水\n");
					printf("\t%s\t%s\t%s\t%s\t%s\n",row[0],row[1],row[2],row[3],row[4]);
				}
				else
				{
				cout<<"你输入的技术员工编号不存在！\n";
				}
				mysql_free_result(res);
			}
			cout<<"是否继续查找?(输入1继续):";
			cin>>r;
			}
		}
		
	
}

void jingli::xianshi1(int a)
{
	int sa;
	if(a==1){
		cout<<"---1.按编号顺序显示\t2.按级别顺序显示----"<<endl;
		cin>>sa;
		if(sa==1){
			mysql_query(conn,"select * from go1 where isuse=1 and jibie=11 order by bian asc");
			res=mysql_use_result(conn);
			cout<<"\t编号\t姓名\t性别\t级别\t薪水"<<endl;
			while((row=mysql_fetch_row(res))!=NULL){
				printf("\t%s\t%s\t%s\t%s\t%s\n",row[0],row[1],row[2],row[3],row[4]);
			}
		}
		else if(sa==2){
			mysql_query(conn,"select * from go1 where isuse=1 and jibie=11 order by jibie asc");
			res=mysql_use_result(conn);
			cout<<"\t编号\t姓名\t性别\t级别\t薪水"<<endl;;
			while((row=mysql_fetch_row(res))!=NULL){
				printf("\t%s\t%s\t%s\t%s\t%s\n",row[0],row[1],row[2],row[3],row[4]);
			}
		}
		else 
		{
		cout<<"输入错误！\n";	
		}
		mysql_free_result(res);
	}

}

void jingli::jiesuan1(int a)
{
char asd[100];
char zx[100];
int i,j,sa;
cout<<"请输入要结算技术员工的编号：";
cin>>i;
sprintf(asd,"select * from go1 where (isuse=1) and (jibie=11) and (bian=%d)",i);
			mysql_query(conn,asd);
			res=mysql_use_result(conn);
			if((row=mysql_fetch_row(res))!=NULL){
				cout<<"你要结算的技术员工的信息:\n";
				cout<<"\t编号\t姓名\t性别\t级别\t薪水"<<endl;
				printf("\t%s\t%s\t%s\t%s\t%s\n",row[0],row[1],row[2],row[3],row[4]);
				cout<<"请输入该技术员工该月工作时间（单位小时）：";
				cin>>j;
				sa=j*15;
				cout<<"该员工该月工资为："<<sa<<endl;
				mysql_free_result(res);
				sprintf(zx,"update go1 set xin=%d where bian = %d",sa,i);
						mysql_query(conn,zx);
						cout<<"结算成功!\n";
					
						
			}
			else
			{
			cout<<"你输入的技术员工编号不存在！";
			}
			




}

void Jingli(char name[])
{	char asd[100];
	int x=1;
	jingli cv;
	while(x!=0){
	cout<<"***********************经理界面**************************"<<endl;
	cout<<"1.添加兼职技术人员\n2.删除兼职技术人员\n3.修改兼职技术人员信息\n4.查找兼职技术人员信息\n5.显示所有兼职技术人员\n6.结算兼职技术员工工资\n7.显示自己的信息\n0.返回主界面"<<endl;
	cin>>x;
	switch(x){
		case 1:
			cv.tianjia1(1);
			break;
		case 2:
			cv.del1(1);
			break;
		case 3:
			cv.change1(1);
			break;
		case 4:
			cv.find1(1);
			break;
		case 5:
			cv.xianshi1(1);
			break;
		case 6:
			cv.jiesuan1(1);
			break;
		case 7:
			sprintf(asd,"select * from go1 where isuse=1 and sname='%s'",name);
			mysql_query(conn,asd);
			res=mysql_use_result(conn);
			cout<<"\t编号\t姓名\t性别\t级别\t薪水"<<endl;
			if((row=mysql_fetch_row(res))!=NULL){
				printf("\t%s\t%s\t%s\t%s\t%s\n",row[0],row[1],row[2],row[3],row[4]);
			}
			mysql_free_result(res);
			break;
		case 0:
			break;
		default:
			cout<<"输入有误！请重新输入\n";
			break;
	}
	}
}

////////////////////////////////////////////////  销售经理界面 //////////////////////////////////////////////////////

void xiaoshou::tianjia2(int x)
{
	int q=1;
	int w;
	char sdf[100];
	char sf[100];
	if(x==1){
		
			jingli a;
			list<jingli> link;
			mysql_query(conn,"select bian,sname,sex,jibie,xin,isuse from go1  where isuse =0 order by bian asc");
			res=mysql_use_result(conn);
			while((row=mysql_fetch_row(res))!=NULL)
			{
				a.bian = atoi(row[0]);
				strcpy(a.sname,row[1]);
				strcpy(a.sex,row[2]);
				a.jibie=atoi(row[3]);
				a.xin=atoi(row[4]);
				link.push_back(a);
			}
			list<jingli>::iterator we =link.begin();
			if(link.size()!=0){
			while((q==1)&&(we!=link.end())){
			cout<<"输入姓名:";
			cin>>we->sname;
			cout<<"输入性别:";
			cin>>we->sex;
			we->isuse=1;
			cout<<"添加成功！\n";
			cout<<"是否继续添加？(输入1继续):";
			cin>>q;
			we++;
			}
			we = link.begin();
			while(we!=link.end())
			{
				sprintf(sdf,"update go1 set sname ='%s',sex='%s',jibie=22,xin=0,isuse=%d where bian=%d",we->sname,we->sex,we->isuse,we->bian);
				mysql_query(conn,sdf);
				we++;
			}
			}
			list<jingli> li;
			jingli b;
			while(q==1)
			{
				cout<<"输入姓名:";
				cin>>b.sname;
				cout<<"输入性别:";
				cin>>b.sex;
				li.push_back(b);
				cout<<"添加成功！";
				cout<<"是否继续添加?(输入1继续):";
				cin>>q;
			}
			list<jingli>::iterator om=li.begin();
			while(om!=li.end())
			{
				sprintf(sf,"insert into go1(sname,sex,jibie,xin) values ('%s','%s',22,0)",om->sname,om->sex);
				mysql_query(conn,sf);
				om++;
			}

		mysql_free_result(res);
	}
}

void xiaoshou::del2(int x)
{
	int q;
	int qwe;
	char name[100];
	char rt[100];
	int r=1;
	while(r==1)//是否进行第二次操作
	{
		if(x==1)//boss的操作
		{
			list<people> lo;
			people vg;
			cout<<"按什么进行删除?\n1.编号\n2.姓名\n";
			cin>>q;
			if(q==1)
			{
				cout<<"输入要删除销售员工的编号:";
				cin>>qwe;
				mysql_query(conn,"select bian,sname,isuse from go1 where jibie=22 order by bian asc");
				res=mysql_use_result(conn);
				while((row=mysql_fetch_row(res))!=NULL)
				{
					vg.bian=atoi(row[0]);
					strcpy(vg.sname,row[1]);
					vg.isuse=atoi(row[2]);
					lo.push_back(vg);
				}
				list<people>::iterator oo=lo.begin();
				while(oo!=lo.end())
				{
					if((qwe==oo->bian)&&(oo->isuse==1)){
						oo->isuse=0;
						sprintf(rt,"update go1 set isuse=0 where bian=%d",oo->bian);
						mysql_query(conn,rt);
						cout<<"删除成功！\n";
						break;
					}
					oo++;
				}
				if(oo==lo.end()){
					cout<<"无此编号的销售员工！\n";
				}
			}
			else if(q==2)
			{
				cout<<"输入要删除销售员工的姓名:";
				cin>>name;
				mysql_query(conn,"select bian,sname,isuse from go1 where jibie=22 order by bian asc");
				res=mysql_use_result(conn);
				while((row=mysql_fetch_row(res))!=NULL)
				{
					vg.bian=atoi(row[0]);
					strcpy(vg.sname,row[1]);
					vg.isuse=atoi(row[2]);
					lo.push_back(vg);
				}
				list<people>::iterator oo=lo.begin();
				while(oo!=lo.end())
				{
					if(strcmp(name,oo->sname)==0 && oo->isuse==1){
						oo->isuse=0;
						sprintf(rt,"update go1 set isuse=0 where sname='%s'",oo->sname);
						mysql_query(conn,rt);
						cout<<"删除成功！\n";
						break;
					}
					oo++;
				}
				if(oo==lo.end()){
					cout<<"无此姓名的销售员工！\n";
				}
			}
			else 
			{
				cout<<"输入错误！\n";

			}
		}
	mysql_free_result(res);
	cout<<"是否继续删除?(1继续):";
	cin>>r;
	}
}

void xiaoshou::change2(int x)
{
	int r=1;
	char zx[100];
	int q;
	int qwe[10];
	while(r==1)//是否继续操作
	{
		if(x==1)//boss的操作
		{
			cout<<"请输入修改内容:\n 1.薪水 2.密码\n";
			cin>>q;
			if(q==1)
			{
				list<people> lp;
				people k;
				cout<<"输入要修改销售员工的编号:";
				cin>>qwe[0];
				mysql_query(conn,"select bian,sname,isuse from go1 where jibie=22 order by bian asc");
				res=mysql_use_result(conn);
				while((row=mysql_fetch_row(res))!=NULL)
				{
					k.bian=atoi(row[0]);
					strcpy(k.sname,row[1]);
					k.isuse=atoi(row[2]);
					lp.push_back(k);
				}
				list<people>::iterator ui=lp.begin();
				while(ui!=lp.end())
				{
					if((qwe[0]==ui->bian)&&(ui->isuse==1)){
						cout<<"输入修改后的薪水:";
						cin>>qwe[1];
						sprintf(zx,"update go1 set xin=%d where bian = %d",qwe[1],qwe[0]);
						mysql_query(conn,zx);
						cout<<"修改成功!\n";
						break;
					}
					ui++;
				}
				if(ui==lp.end()){
					cout<<"无此编号的销售员工"<<endl;}
			}
			else if(q==2)
			{
			list<people> lp;
				people k;
				cout<<"输入要修改销售员工的编号:";
				cin>>qwe[0];
				mysql_query(conn,"select bian,sname,isuse from go1 where jibie=22 order by bian asc");
				res=mysql_use_result(conn);
				while((row=mysql_fetch_row(res))!=NULL)
				{
					k.bian=atoi(row[0]);
					strcpy(k.sname,row[1]);
					k.isuse=atoi(row[2]);
					lp.push_back(k);
				}
				list<people>::iterator ui=lp.begin();
				while(ui!=lp.end())
				{
					if((qwe[0]==ui->bian)&&(ui->isuse==1)){
						cout<<"输入修改后的密码（默认为123456）:";
						cin>>qwe[1];
						sprintf(zx,"update go1 set password=%d where bian = %d",qwe[1],qwe[0]);
						mysql_query(conn,zx);
						cout<<"修改成功!\n";
						break;
					}
					ui++;
				}
				if(ui==lp.end()){
					cout<<"无此编号的销售员工"<<endl;}
			}
			else{cout<<"输入有误！";}
		}
		mysql_free_result(res);
		cout<<"是否继续修改?(输入1继续):";
		cin>>r;
	}
}

void xiaoshou::find2(int x)
{
	int r=1;
	int wq=1;
	int fg;
	char asd[100];
		if(x==1)
		{
			while(r==1){
			if(wq==1)
			{	
				
				cout<<"输入要查找的销售员工编号:";
				cin>>fg;
				sprintf(asd,"select * from go1 where (jibie=22) and (isuse =1) and (bian=%d)",fg);
				mysql_query(conn,asd);
				res=mysql_use_result(conn);
				if((row=mysql_fetch_row(res))!=NULL)
				{
					printf("\t编号\t姓名\t性别\t级别\t薪水\n");
					printf("\t%s\t%s\t%s\t%s\t%s\n",row[0],row[1],row[2],row[3],row[4]);
				}
				else
				{
				cout<<"你输入的销售员工编号不存在！\n";
				}
				mysql_free_result(res);
			}
			cout<<"是否继续查找?(输入1继续):";
			cin>>r;
			}
		}
		
	
}

void xiaoshou::xianshi2(int a)
{
	int sa;
	if(a==1){
		cout<<"---1.按编号顺序显示\t2.按级别顺序显示----"<<endl;
		cin>>sa;
		if(sa==1){
			mysql_query(conn,"select * from go1 where isuse=1 and jibie=22 order by bian asc");
			res=mysql_use_result(conn);
			cout<<"\t编号\t姓名\t性别\t级别\t薪水"<<endl;
			while((row=mysql_fetch_row(res))!=NULL){
				printf("\t%s\t%s\t%s\t%s\t%s\n",row[0],row[1],row[2],row[3],row[4]);
			}
		}
		else if(sa==2){
			mysql_query(conn,"select * from go1 where isuse=1 and jibie=22 order by jibie asc");
			res=mysql_use_result(conn);
			cout<<"\t编号\t姓名\t性别\t级别\t薪水"<<endl;;
			while((row=mysql_fetch_row(res))!=NULL){
				printf("\t%s\t%s\t%s\t%s\t%s\n",row[0],row[1],row[2],row[3],row[4]);
			}
		}
		else 
		{
		cout<<"输入错误！\n";	
		}
		mysql_free_result(res);
	}

}

void xiaoshou::jiesuan2(int a)
{
char asd[100];
char zx[100];
int i,j,sa;
cout<<"请输入要结算销售员工的编号：";
cin>>i;
sprintf(asd,"select * from go1 where (isuse=1) and (jibie=22) and (bian=%d)",i);
			mysql_query(conn,asd);
			res=mysql_use_result(conn);
			if((row=mysql_fetch_row(res))!=NULL){
				cout<<"你要结算的销售员工的信息:\n";
				cout<<"\t编号\t姓名\t性别\t级别\t薪水"<<endl;
				printf("\t%s\t%s\t%s\t%s\t%s\n",row[0],row[1],row[2],row[3],row[4]);
				cout<<"请输入该销售员工该月销售额：";
				cin>>j;
				sa=j+2000;
				cout<<"该员工该月工资为："<<sa<<endl;
				mysql_free_result(res);
				sprintf(zx,"update go1 set xin=%d where bian = %d",sa,i);
						mysql_query(conn,zx);
						cout<<"结算成功!\n";
					
						
			}
			else
			{
			cout<<"你输入的销售员工编号不存在！\n";
			}
			




}




void Xiaoshou(char name[])
{	char asd[100];
	int x=1;
	int s=0;
	char zx[100];
	xiaoshou cv;
	while(x!=0){
	cout<<"***********************销售经理界面**************************"<<endl;
	cout<<"1.添加销售人员\n2.删除销售人员\n3.修改销售人员信息\n4.查找销售人员信息\n5.显示所有销售人员\n6.结算销售员工工资\n7.显示自己的信息\n0.返回主界面"<<endl;
	cin>>x;
	switch(x){
		case 1:
			cv.tianjia2(1);
			break;
		case 2:
			cv.del2(1);
			break;
		case 3:
			cv.change2(1);
			break;
		case 4:
			cv.find2(1);
			break;
		case 5:
			cv.xianshi2(1);
			break;
		case 6:
			cv.jiesuan2(1);
			break;
		case 7:
			s=0;
			mysql_query(conn,"select xin from go1 where isuse=1 and jibie=22 order by bian asc");
			res=mysql_use_result(conn);
			while((row=mysql_fetch_row(res))!=NULL){
				s=s+atoi(row[0])-2000;
			}
			mysql_free_result(res);
			s=s+5000;

			sprintf(asd,"select * from go1 where isuse=1 and sname='%s'",name);
			mysql_query(conn,asd);
			res=mysql_use_result(conn);
			
			if((row=mysql_fetch_row(res))!=NULL){
				cout<<"\t编号\t姓名\t性别\t级别\t薪水"<<endl;
				printf("\t%s\t%s\t%s\t%s\t%d\n",row[0],row[1],row[2],row[3],s);
			}
			mysql_free_result(res);
			sprintf(zx,"update go1 set xin=%d where sname = '%s'",s,name);
			mysql_query(conn,zx);
			break;
		case 0:
			break;
		default:
			cout<<"输入有误！请重新输入\n";
			break;
	}
	}
}





//////////////////////////////////////////////////////  主函数   ////////////////////////////////////////////////////////////
   
int main()
{
	const char *server="localhost";
	const char *user="root";
	const char *password="123456";
	const char *database="w1";
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		fprintf(stderr,"%s\n",mysql_error(conn));
		return 0;
	}
	mysql_set_character_set(conn,"utf8");
	char name[20];
	int  pass;
	int i=1;
	int dc;
	list<people> np;
	people xp;
	mysql_query(conn,"select sname,password,jibie from go1");
	res=mysql_use_result(conn);
	while((row=mysql_fetch_row(res))!=NULL)
	{
		strcpy(xp.sname,row[0]);
		xp.password=atoi(row[1]);
		xp.jibie=atoi(row[2]);
		np.push_back(xp);
	}
	while(dc!=0)
	{
	cout<<"***********欢迎进入公司人员信息管理系统**********"<<endl;
   	cout<<"          1.老板登录                        "<<endl; 
   	cout<<"          2.经理登录                    "<<endl;
   	cout<<"          3.销售经理登录                    "<<endl;
   	cout<<"          0.退出                                "<<endl;
   	cout<<"*************************************************"<<endl;
   	cout<<"请输入所要操作的编号：";
	cin>>dc;
	if(dc==1){
	for(i=1;i<4;i++){
		cout<<"================登录===================="<<endl;
		cout<<"	输入姓名:";
		cin>>name;	
		cout<<"	输入密码:";
		cin>>pass;
		if((strcmp(name,"boss")==0)&&pass==123456)
		{
			boss();
			break;
		}
		cout<<"输入错误"<<endl;
	}}
	else if(dc==2)
	{
		for(i=1;i<4;i++){
		cout<<"==================登录=================="<<endl;
		cout<<"输入姓名:";
		cin>>name;
		cout<<"输入密码:";
		cin>>pass;
		list<people>::iterator dp=np.begin();
		while(dp!=np.end())
		{
			if((strcmp(name,dp->sname)==0)&&(pass==dp->password)&&dp->jibie==1
){
			Jingli(name);
			break;
			}
			dp++;
		}
		if(dp!=np.end())
			break;
		if(dp==np.end())
			cout<<"输入错误\n";
		}
		}
	
	else if(dc==3)
	{
		for(i=1;i<4;i++){
		cout<<"==================登录=================="<<endl;
		cout<<"输入姓名:";
		cin>>name;
		cout<<"输入密码:";
		cin>>pass;
		list<people>::iterator dp=np.begin();
		while(dp!=np.end())
		{
			if((strcmp(name,dp->sname)==0)&&(pass==dp->password)&&dp->jibie==2
){
			Xiaoshou(name);
			break;
			}
			dp++;
		}
		if(dp!=np.end())
			break;
		if(dp==np.end())
			cout<<"输入错误\n";
		}
		}
	else if(dc==0){}
	else{cout<<"输入有误！\n";}
	
	}
	//cout<<name<<pass<<endl;
	//---------------------------------------------------------------
	//mysql_free_result(res);
	mysql_close(conn);
}
