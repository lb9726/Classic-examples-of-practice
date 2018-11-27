#include"addrui.h"

int main()
{
	STNODE *head = NULL;
	head = readfiletolist("职工管理系统.txt");//gettime();
	ShowInfo_In_order(head);
	//ShowInfo_In_order(head);
	//linksort_big_to_small(head);
	//ShowInfo_In_order(head);
	//linksort_small_to_big(head);
	//ShowInfo_In_order(head);
	//find_id_or_name(head);//ShowInfo_In_order(head);
	//int i = get_min_id(head);
	//printf("i = %d\n",i);
	//head = add_person_infoUI(head);
	//head = modify_idorname_main(head);
	//ShowInfo_In_order(head);
	//DestroyLinklist(head);
	//ShowInfo_In_order(head);
	head = delete_idorname_main(head);
	ShowInfo_In_order(head);
	//savefile(head,"2.txt");
	return 0;
}
