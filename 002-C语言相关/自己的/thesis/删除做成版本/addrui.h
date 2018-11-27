#include"addrlogic.h"

int user_loginUI();

PERSONINFO add_info(STNODE *head);

STNODE *add_person_infoUI(STNODE *head);

void print_name_result(STNODE *head,int flag,int choice,char name[]);

void print_id_result(STNODE *head,int flag,int choice,int id);

void find_id_or_name(STNODE *head);

STNODE *search_name_genratelinkst(STNODE *head,char pname[30],int *flag);

STNODE *search_id_genratelinkst(STNODE *head,int id,int *flag);

STNODE *findname(STNODE *head,char pname[30]);

STNODE *findID(STNODE *head,int id);

void modify_ui(STNODE *tmp);

void show_modify_id(STNODE *head,int id,int choice);

int show_modify_name(STNODE *head,char name[],int choice);

STNODE *modify_id_info(STNODE *head,int id,int choice);

STNODE *modify_name_info(STNODE *head,char name[],int choice);

STNODE *modify_idorname_main(STNODE *head);

STNODE * dealwith_same_name(STNODE *head,int flagnum,char name[30]);

STNODE * findfordelete(STNODE *head);

//STNODE *delete_id_info(STNODE *head,int id,int choice);

//STNODE *delete_name_info(STNODE *head,char name[],int choice);

STNODE *delete_idorname_main(STNODE *head);








