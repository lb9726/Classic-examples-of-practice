#include"ui.h"
int main()
{
    connectdatabase();//调用连接数据库函数
    LoginUI();
    mysql_close(conn);
}
