#include "../include/addrui.h"

int main()
{
	Login_STNODE *head = NULL;
	head = readfiletolist_for_login("logintable.txt");
	user_loginUI(head);//管理员登录
	free(head);
	head = NULL;
	return 0;
}
