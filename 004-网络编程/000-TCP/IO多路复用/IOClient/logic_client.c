#include "logic_client.h"

// 验证注册输入的用户名是否合法
Status check_register_name(char username[])
{
    char *p = username;
    char *q = username;
    if (strlen(username) >= 10)
    {
        printf(RED"用户名长度大于等于10,过长！\n"NONE);
        return ERROR;
    }
    while (*p != '\0')
    {
        *q = *p;
        p++;
        if ('\0' == *p && ' ' == *q)
        {
            printf(RED"用户名末尾不能包含空格!\n"NONE);
            return ERROR;
        }
    }
    return OK;
}

// 验证注册两次输入的密码长度是否正确是否一致
Status check_register_pwd( char userpwd[], char pwdagain[])
{
    if (strlen(userpwd) >= 20)
    {
        printf(RED"密码长度大于等于20,过长！\n"NONE);
        return ERROR;
    }
    printf("userpwd = %s, pwdagain = %s\n",userpwd, pwdagain);
    if (0 != strcmp(userpwd, pwdagain))
    {
        printf(RED"两次输入的密码不一致！\n"NONE);
        return ERROR;
    }
    return OK;
}
