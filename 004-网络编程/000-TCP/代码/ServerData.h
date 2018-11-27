#include<stdio.h>
#include <stdlib.h>
#include<sys/socket.h>
#include<strings.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<time.h>  
#include <errno.h>
#include <sys/types.h>         
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/time.h>

#define BUF_SIZE 1024

static char pname[64];
//操作信息结构体
typedef struct _MESSAGE    
{
    int  pnum;           //归属人编号
    int  num;            //好友（其他人）编号
    char name[64];       //归属人姓名
    char msg[100];
    char flag[50];
    int  state;         //在线状态
    int  clientfd;
    char IP[30];        
}MESSAGE;


//操作信息结构链表
typedef struct _STHandle    
{
    MESSAGE message;
    struct _STHandle *next;
}STHandle;


static STHandle head;

int DestoryLinklist();                             //1,销毁链表    

int addSTlinklist(MESSAGE message);                //2,添加注册人员信息链表  for RegInfoTab.txt and PerInfoTab.txt     

int STlinkreadRegInfofile();                       //3,链表读取文件RegInfoTab.txt

int STlinkreadPerInfofile();                       //4,链表读取文件PerInfoTab.txt                

int  CoverRegNode(int num0);                       //5,遍历  for 注册

int  CoverLogNode(MESSAGE message);                //6,遍历  for 登录

int  CoverAddFNode(MESSAGE message);               //7,遍历  for 添加好友

int  CoverDelFNode(MESSAGE message);                //8,遍历  for 删除好友

int UpdateStartIP(MESSAGE messages);                //9,开始更新IP

int UpdateEndIP(MESSAGE messages);                  //9.1,开始更新IP

int  CoverFriListNode(MESSAGE message,int sockfd);  //10,遍历  for 好友列表            

int writeRegInfofile();                             //11,链表写入文件RegInfoTab.txt  

int HandlePerChat(int clientfd,MESSAGE msg);        //12，处理私人聊天函数

int HandleGroChat(int clientfd,MESSAGE msg);        //12.1，处理群组聊天函数

int getclient(MESSAGE msg);                         //12.2  获取客户端号

int ExitChat(int clientfd,MESSAGE msg);             //13,退出聊天   

int FriendList(int clientfd,MESSAGE msg);           //14,好友列表  

int FriendList1(int clientfd,MESSAGE msg);          //14,1,好友列表

int AddFriend(int clientfd,MESSAGE msg);            //15,添加好友  

int DelFriend(int clientfd,MESSAGE msg);            //16,删除好友
  
