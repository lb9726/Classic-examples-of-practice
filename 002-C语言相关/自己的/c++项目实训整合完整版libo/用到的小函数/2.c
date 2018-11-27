#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
void get_rand_str(char s[],int number)
{
char str[64] = "00123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
int i;
char ss[2];
//printf("%c %c\n",str[1],str[62]);
srand((unsigned int)time((time_t *)NULL));
for(i=1;i<=number;i++){
sprintf(ss,"%c",str[(rand()%62)+1]);
//printf(ss);
strcat(s,ss);
}
}
int main()
{
char s[5];
int i,j;
get_rand_str(s,5);
puts(s);
}
