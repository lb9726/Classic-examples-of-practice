#include "File.h"
#include "serverdata.h"
//客户端传来 USER Cliuser;
//经服务器接收后  USER Seruser;//

void Showuser(USER *Seruser)
{
	printf("Seruser.iID = %d\n",Seruser->iID);
	printf("Seruser.szPass = %s\n",Seruser->szPass);
}

/*
//1.插入信息   头插法
STNODE *AddDicNode(STNODE *stHead,DIC buf)
{
    STNODE *pnode = malloc(sizeof(STNODE));
    pnode->buf = buf;
    pnode->next = NULL;
   
    pnode->next = stHead->next; 
    stHead->next = pnode;
    
    return stHead;
}


int GetMaxNum(STNODE *stHead)
{
	STNODE *p = stHead->next;
	int iMax = 0;
	while(p != NULL)
    {
    	if(p->buf.iNum > iMax)  			
    		iMax = p->buf.iNum;   		
    	p = p->next;
	}
	return iMax;
}




//单聊写入文件
int Addonecaht(CHAT *Serchat)
{
	int fd;
	fd = open((char *)Serchat->iID,O_RDWR|O_CREAT,0664);//要修改
	if(fd<0)
    {
         printf("open file %s\n",strerror(errno));
         return -1;
    }
    printf("open sucess\n");
 
    ssize_t len,ret;
	len = sizeof(CHAT);
	lseek(fd,0L,SEEK_END);
    while(len > 0)
    {
         ret = write(fd,(CHAT *)Serchat,len);
         if(ret < 0)
         {
		     perror("write()");
 		     return -1;
 	     }
         len = len - ret;    
    }
  //  Show(Serchat);
    close(fd);
    return 0;
}*/

int Addgroupcaht(CHAT *Serchat)
{
	printf("加入到群聊记录\n");
	return 0;

}








