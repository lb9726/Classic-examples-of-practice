#include<stdio.h>
#include<stdlib.h>
 
 #define NONE "\e[0m"
 #define BLACK "\e[0;30m"
 #define L_BLACK "\e[1;30m"
 #define RED "\e[0;31m"
 #define L_RED "\e[1;31m"
 #define GREEN "\e[0;32m"
 #define L_GREEN "\e[1;32m"
 #define BROWN "\e[0;33m"
 #define YELLOW "\e[1;33m"
 #define BLUE "\e[0;34m"
 #define L_BLUE "\e[1;34m"
 #define PURPLE "\e[0;35m"
 #define L_PURPLE "\e[1;35m"
 #define CYAN "\e[0;36m"
 #define L_CYAN "\e[1;36m"
 #define GRAY "\e[0;37m"
 #define WHITE "\e[1;37m"
 
 #define BOLD "\e[1m"
 #define UNDERLINE "\e[4m"
 #define BLINK "\e[5m"
 #define REVERSE "\e[7m"
 #define HIDE "\e[8m"
 #define CLEAR "\e[2J"
 #define CLRLINE "\r\e[K" //or "\e[1K\r"
 
 
 void setcolor()
 {
 	printf(BLACK "我是谁 1\n" NONE);
	printf(L_BLACK "我是谁 2\n" NONE);
	printf(RED "我是谁 3\n" NONE);
	printf(L_RED "我是谁 4\n" NONE);
	printf(GREEN "我是谁 5\n" NONE);
	printf(L_GREEN "我是谁 6\n" NONE);
	
	printf(BROWN "我是谁 7\n" NONE);
	printf(YELLOW "我是谁 8\n" NONE);
	printf(BLUE "我是谁 9\n" NONE);
	printf(L_BLUE "我是谁 10\n" NONE);
	printf(PURPLE "我是谁 11\n" NONE);
	printf(L_PURPLE "我是谁 12\n" NONE);
	
	printf(CYAN "我是谁 13\n" NONE);
	printf(L_CYAN "我是谁 14\n" NONE);
	printf(GRAY "我是谁 15\n" NONE);
	printf(WHITE "我是谁 16\n" NONE);
	
	
	printf(BOLD "我是谁 17\n" NONE);
	printf(UNDERLINE "我是谁 18\n" NONE);
	printf(BLINK "我是谁 19\n" NONE);
	printf(REVERSE "我是谁 20\n" NONE);
	printf(HIDE "我是谁 21\n" NONE);
	//printf(CLEAR "我是谁 22\n" NONE);
	printf(CLRLINE "我是谁 23\n" NONE);
}
	
int main(void)
{
	printf("This is a character control test!\n" );
    sleep(3);
    printf("[%2u]" CLEAR "CLEAR\n" NONE, __LINE__);
  
    printf("[%2u]" BLACK "BLACK " L_BLACK "L_BLACK\n" NONE, __LINE__);
    printf("[%2u]" RED "RED " L_RED "L_RED\n" NONE, __LINE__);
    printf("[%2u]" GREEN "GREEN " L_GREEN "L_GREEN\n" NONE, __LINE__);
    printf("[%2u]" BROWN "BROWN " YELLOW "YELLOW\n" NONE, __LINE__);
    printf("[%2u]" BLUE "BLUE " L_BLUE "L_BLUE\n" NONE, __LINE__);
    printf("[%2u]" PURPLE "PURPLE " L_PURPLE "L_PURPLE\n" NONE, __LINE__);
    printf("[%2u]" CYAN "CYAN " L_CYAN "L_CYAN\n" NONE, __LINE__);
    printf("[%2u]" GRAY "GRAY " WHITE "WHITE\n" NONE, __LINE__);
    printf("[%2u]\e[1;31;40m Red \e[0m\n",  __LINE__);

     printf("[%2u]" BOLD "BOLD\n" NONE, __LINE__);
     printf("[%2u]" UNDERLINE "UNDERLINE\n" NONE, __LINE__);
     printf("[%2u]" BLINK "BLINK\n" NONE, __LINE__);
     printf("[%2u]" REVERSE "REVERSE\n" NONE, __LINE__);
     printf("[%2u]" HIDE "HIDE\n" NONE, __LINE__);
 
     printf("Cursor test begins!\n" );
     printf("=======!\n" );
     sleep(10);
     printf("[%2u]" "\e[2ACursor up 2 lines\n" NONE, __LINE__);
    sleep(10);
     printf("[%2u]" "\e[2BCursor down 2 lines\n" NONE, __LINE__);
     sleep(5);
     printf("[%2u]" "\e[?25lCursor hide\n" NONE, __LINE__);
     sleep(5);
     printf("[%2u]" "\e[?25hCursor display\n" NONE, __LINE__);
     sleep(5);
 
     printf("Test ends!\n" );
     sleep(3);
     printf("[%2u]" "\e[2ACursor up 2 lines\n" NONE, __LINE__);
     sleep(5);
     printf("[%2u]" "\e[KClear from cursor downward\n" NONE, __LINE__);
 
     printf("setcolor begin\n");
     setcolor();
     return 0 ;
}



	
