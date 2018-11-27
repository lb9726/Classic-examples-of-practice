#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>


int MyStrlen(char *p);

void InitAarry(char *name[],char *str[],int *length[],int a,int n);

void ReadInfotoArray(char *array[],int i,STNODE *head);

int GetLines(STNODE *head);

int AppendColumn(char *array[]);

void generate_node(PERSONINFO people,STNODE *head);

void read_file_use_fscanf(char filename[30],STNODE *head);

STNODE * readfiletolist(char filename[30]);

char * int_form_string(int num);

void ShowInfo_In_order(STNODE *head);

void PrintInfoIntoTable(char *array[],char *str[],int max[],int a,int n);

void GainColumnMaxLength(char *array[],int *length[],int max[],int erwei[][9],int c,int n);

int GetMax(int erwei[][9],int *length[],int max[],int c,int n);

void AddBlank(char *array[], int *length[],int c,int n);

void linking(char *array[],char *str[],int a,int n);

void FreeSpace(char *name[],char *str[],int *length[],int a,int n);

