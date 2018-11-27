//16进制转10进制
#include<stdio.h>
#include<string.h>
int convert(char *p)
{
	int n;
	if(*p >= '0'&&*p <= '9')
    {	
        n = *p-'0';
        p++;
    }
	else if (*p =='a'||*p =='A')
	{ 
	    n = 10;
	    p++;
	}
	else if(*p =='b'||*p =='B')
	{ 
	    n = 11;
	    p++;
	}	
	else if(*p =='c'||*p =='C')
	{ 
	    n = 12;
	    p++;
	}	
	else if(*p =='d'||*p =='D')
	{ 
	    n = 13;
	    p++;
	}	
	else if(*p == 'e'||*p =='E')
	{ 
	    n = 14;
	    p++;
	}
	else if(*p =='f'||*p =='F')
	{ 
	    n = 15;
	    p++;
	}	
	while(*p)
	{
		switch(*p)
		{	case '0':case '1':case '2':case '3':case '4':case '5':
		    case '6':case '7':case '8' :case '9': n = n * 16 + *p - '0'; p++; break;
			case 'a':case'A': n = n * 16 + 10; p++; break;
			case 'b':case'B': n = n * 16 + 11; p++; break;
			case 'c':case'C': n = n * 16 + 12; p++; break;
			case 'D':case'd': n = n * 16 + 13; p++; break;
			case 'e':case'E': n = n * 16 + 14; p++; break;
			case 'f':case'F': n = n * 16 + 15; p++; break;
																	
		}
	}
	return n;
}

void youhua(char *p)
{
	while(*p)
	{	if(*p == '\n')
		{
		 	*p = '\0';
		 	break;
		}	
		p++;
	}
	return;
}

int main()
{   
	char s[20];
    printf("please enter a string s\n");
    fgets(s, 20, stdin);
    youhua(s);
	puts(s);
	int ret = convert(s);
	printf("the number is %d\n", ret);
	return 0;
}
