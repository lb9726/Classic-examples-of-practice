#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>

int createFile(const char *filename)
{
    int fd = open(filename, O_CREAT|O_RDWR, 0777);
    if (0 > fd)
    {
        printf("file %s open falied!\n", filename);
        return -1;
    }
    return fd;
}

int main()
{
    //创建套接字
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    //向服务器（特定的IP和端口）发起请求
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    serv_addr.sin_port = htons(1234);  //端口
    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
   
    //读取服务器传回的数据
    char buffer[1000];
    int nCounts;
    int fd = createFile("/home/libo/Desktop/movies.mp4");
    if (fd < 0)
    {
        close(sock);
        exit(0);
    }
    while (nCounts = read(sock, buffer, sizeof(buffer)))
    {
        write(fd, buffer, nCounts);
        printf("nCounts = %d\n", nCounts);
    }
    close(fd);
//    printf("Message form server: %s\n", buffer);
   
    //关闭套接字
    close(sock);
    return 0;
}

