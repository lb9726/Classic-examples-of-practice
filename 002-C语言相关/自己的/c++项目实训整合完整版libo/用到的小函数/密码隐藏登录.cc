 /*
c_flag:本地模式标志,控制终端编辑功能
ICANON:使用标准输入模式ECHOE:如果ICANONS同时设置,ERASE将删除输入的字符
*ECHOK:如果ICANON同时设置,KILL将删除当前行,ECHONL如果ICANON同时设置,急死ECHO没有设置依然显示换行符
*ECHOPRT:如果ECHO和ICANON同时设置,将删除打印出的字符(非POSIX)
TCSANOW:不等数据传输完成就立即改变属性
*/

#include<stdio.h>
#include<termios.h>
#include<unistd.h>
#include<assert.h>
#include<string.h>

//改变终端设置
int getch()
{
 int c=0;
 struct termios org_opts, new_opts;
    int res=0;
    //-----  store old settings -----------
     res=tcgetattr(STDIN_FILENO, &org_opts);//获取与终端相关的参数
     assert(res==0);
   //---- set new terminal parms --------
  memcpy(&new_opts, &org_opts, sizeof(new_opts));//拷贝结构体
 
  new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);
  tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);//设置终端参数
  c=getchar();
   //------  restore old settings ---------
  res=tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);//还原终端设置
  assert(res==0);
  return c;
}

void hiden(char pd[30])
{
	int i;
	while(1)
	{
 		for(i=0;;i++)
 		{
 			pd[i]=getch();
 			if(pd[i]=='\n')
 			{
 				pd[i]='\0';
 				break;
 			}
 			if(pd[i]==127)
 			{
 				printf("\b \b");
 				i=i-2;
 			}
 			else
 				printf("*");
 			if(i<0)
 				pd[0]='\0';
 		}
 		break;
 	}
}

int main()
{
 char pd2[128];
 printf("请输入密码：");
 hiden(pd2);//密码隐藏
 printf("\n您输入的密码是：[%s]\n",pd2);
}


