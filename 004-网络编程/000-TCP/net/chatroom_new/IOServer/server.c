#include<server.h>
int main()
{
    int listenfd, connectfd;
    struct sockaddr_in server;
    struct sockaddr_in client;
    socklen_t addrlen;
    fd_set rset;
    int clientfd[MaxCounts] = {'\0'};

    if (-1 == (listenfd = socket(AF_INET, SOCK_STREAM, 0)))
    {
        perror("socket() errror !");
        exit(1);
    }
    /*
    设置套接字选项SO_REUSEADDR,即地址重用。
    由于系统默认是只允许一个套接字绑定在一个特定的协议地址上，
    并且当套接字关闭后，系统仍不允许在该地址上绑定其他套接字。
    如果去掉这两行，程序运行时可能会产生错误信息为：Bind() error:Address already in user.
    */
    int opt = SO_REUSEADDR;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    bzero(&server,sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = htonl (INADDR_ANY);
    if (-1 == bind(listenfd, (struct sockaddr *)&server, sizeof(server)))
    {
        perror("Bind() error");
        exit(1);
    }
    if (-1 == listen(listenfd, BACKLOG))
    {
        perror("listen() error");
        exit(1);
    } 
    
   int  len = sizeof(client);
    if (-1 == (connectfd = accept(listenfd, (struct sockaddr *) &client, &addrlen)))
    {
        perror("accept() error");
        exit(1);
    }
    printf("you got a connection from client's ip is %s, port is %d \n", inet_ntoa(client.sin_addr), htons(client.sin_port));

    send(connectfd, "welcome\n", 8, 0);
    printf("connectfd = %d\n", connectfd);
    close(connectfd);
    close(listenfd);
    return 0;
}
