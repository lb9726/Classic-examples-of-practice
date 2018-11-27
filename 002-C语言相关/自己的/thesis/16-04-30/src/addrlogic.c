#include "../include/addrlogic.h"

void check_person_sex(char sex[])
{
	do
	{
		scanf("%s",sex);
		getchar();
		if((strcmp(sex,"男") != 0) && (strcmp(sex,"女") != 0))
			printf("性别输入不合法,请输入"RED"[男/女] !!!\n"NONE);
	}while((strcmp(sex,"男") != 0) && (strcmp(sex,"女") != 0));
}

void check_person_age(char age[])
{
	age_legal(age);
}

void check_person_telephone(char telephone[])
{
	string_to_int(telephone);
}

void check_person_group(char group[])
{
	choose_group(group);
}

void check_person_mails(char mails[])
{
	check_mails(mails);
}

