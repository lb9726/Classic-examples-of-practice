#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>   //头文件  
struct occupy        //声明一个occupy的结构体  
{  
        char name[20];      //定义一个char类型的数组名name有20个元素  
        unsigned int user;  //定义一个无符号的int类型的user  
        unsigned int nice;  //定义一个无符号的int类型的nice  
        unsigned int system;//定义一个无符号的int类型的system  
        unsigned int idle;  //定义一个无符号的int类型的idle  
};  
float g_cpu_used;           //定义一个全局的float类型g_cpu_used  
int cpu_num;                //定义一个全局的int类型cup_num  
void cal_occupy(struct occupy *, struct occupy *);  //声明无类型的函数cal_occupy包含两个结构体参数  
void get_occupy(struct occupy *);                   //声明无类型的函数get_occupy包含一个结构体参数  
int main()                  //主函数开始   
{  
  struct occupy ocpu[10];   //定义occupy结构体变量名是ocpu含10个元素  
  struct occupy ncpu[10];   //定义occupy结构体变量名是ncpu含10个元素  
  int i;                    //定义一个局部int变量i  
    
  cpu_num = sysconf(_SC_NPROCESSORS_ONLN);   //系统调用返回cpu的个数赋给cpu_num  
  for(;;)                                    //死循环  
  {    
      //sleep(1);                               //等待1秒  
      get_occupy(ocpu);                       //调用get函数带回结构体数组第一次  
      sleep(1);                               //等待1秒   
      get_occupy(ncpu);                       //调用get函数带回结构体数组第二次  
      for (i=0; i<cpu_num; i++)               //循环cpu_num-1次  
      {  
              cal_occupy(&ocpu[i], &ncpu[i]); //调用cal函数带回结构体数组  
              printf("cpu[%d] = %-f\t",i, g_cpu_used);    //打印g_cpu_used的使用情况以6位小数显示             
      }
      if (i == cpu_num)
      {
      	   printf("\n");
      }   
  }  
}  
void  cal_occupy (struct occupy *o, struct occupy *n)//对无类型cal函数含有两个形参结构体类型的指针变量O和N  
{  
    double od, nd;   //定义双精度实型变量od,nd  
    double id, sd;   //定义双精度实型变量id,sd  
    double scale;    //定义双精度实型变量scale  
    od = (double) (o->user + o->nice + o->system + o->idle);//第一次(用户+优先级+系统+空闲)的时间再赋给od  
    nd = (double) (n->user + n->nice + n->system + n->idle);//第二次(用户+优先级+系统+空闲)的时间再赋给od  
    scale = 100.0 / (float)(nd - od);       //100除强制转换(nd-od)之差为float类型再赋给scale这个变量  
    id = (double) (n->user - o->user);    //用户第一次和第二次的时间之差再赋给id  
    sd = (double) (n->system - o->system);//系统第一次和第二次的时间之差再赋给sd  
    g_cpu_used = ((sd + id)*100.0)/(nd - od); //((用户+系统)乖100)除(第一次和第二次的时间差)再赋给g_cpu_used  
}  
void  get_occupy (struct occupy *o) //对无类型get函数含有一个形参结构体类弄的指针O  
{  
    FILE *fd;         //定义文件指针fd  
    int n;            //定义局部变量n为int类型  
    char buff[1024];  //定义局部变量buff数组为char类型大小为1024  
                                                                                                                
    fd = fopen ("/proc/stat", "r"); //以R读的方式打开stat文件再赋给指针fd  
    fgets (buff, sizeof(buff), fd); //从fd文件中读取长度为buff的字符串再存到起始地址为buff这个空间里  
    for(n = 0; n < cpu_num; n++)          //循环cpu_num-1次  
    {  
      fgets (buff, sizeof(buff),fd);//从fd文件中读取长度为buff的字符串再存到起始地址为buff这个空间里  
      /*下面是将buff的字符串根据参数format后转换为数据的结果存入相应的结构体参数 */  
      sscanf (buff, "%s %u %u %u %u", o[n].name, &o[n].user, &o[n].nice,&o[n].system, &o[n].idle);  
      /*下面是错误的输出 */  
    //  fprintf (stderr, "%s %u %u %u %u/n", o[n].name, o[n].user, o[n].nice,o[n].system, o[n].idle);  
    }  
   fclose(fd);     //关闭文件fd  
}  
