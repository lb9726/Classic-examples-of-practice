#include"addrlogic.h"

PERSONINFO add_info(STNODE *head);

STNODE *add_person_infoUI(STNODE *head);//添加的主函数

void find_id_or_name_main(STNODE *head);//查找主函数

void modify_ui(STNODE *p);

STNODE *modify_name_info(STNODE *head,char name[],int choice);

STNODE *modify_idorname_main(STNODE *head);//修改的主函数

STNODE *delete_idorname_main(STNODE *head);//删除的主函数

void recovery_source_save_file(STNODE *head);

int user_loginUI(Login_STNODE *head);

void useraction(char name[],Login_STNODE *head,int id);




