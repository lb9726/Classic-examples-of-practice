#ifndef __INTERFACE_H__
#define __INTERFACE_H__


#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>



void registface(char *name, char *pwd);
void loginface(char *id, char *pwd);
void loginfaceshow(char*, char*);
void regist_success(char *,char *);
void regist_failure();
void login_failure();
void press_enter();
void menu(void);

#define DEL		while(getchar()!='\n')





#endif

