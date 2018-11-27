#include <stdio.h>  
#include <string.h>  
  
int main(){  
    char str1[] = "abcd" ;  
    char str2[9];  
    printf("address_str1= %p\n",str1);  
    printf("address_str2= %p\n",str2);  
  
    strcpy(str2,"1234123412341234");  
  
    printf("str1=%s\n",str1);  
    printf("str2=%s\n",str2);  
      
    return 0;  
}  

/*
char str1[] = "abcd" ;  
char str2[2];  2～4 时str1均为空

strcpy(str2,"1234123412341234"); 
address_str1= 0x7fff22067c60
address_str2= 0x7fff22067c50
地址相差为16
str1=
str2=1234123412341234

////////////////////
char str1[] = "abcd" ;  
char str2[8];  5~8
printf("address_str1= %p\n",str1);  
printf("address_str2= %p\n",str2);  
strcpy(str2,"1234123412341234");  
printf("str1=%s\n",str1);  
printf("str2=%s\n",str2);  

address_str1= 0x7fff946a3430
address_str2= 0x7fff946a3440
str1=abcd
str2=1234123412341234
*** stack smashing detected ***: ./yuejie_strcpy terminated
已放弃 (核心已转储)
*/




