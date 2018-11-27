#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

void addblank(char **p)
{
	p=(char **)malloc(sizeof(char *)*8);
	
}

int main()
{
	 char *str[2][2]={"无","无","无","无"};
	 int i,j; int t = strlen(str[1][1]);printf("t= %d\n",t);
	 char *p = "李波波波李波波波";int k = strlen(p);printf("k= %d\n",k);
	 for(i=0;i<2;i++)
	 {
	 	for(j=0;j<2;j++)
	 	{
	 		memcpy(&str[i][j],&p,k);
	 		//str[0][0] = p;
	 		printf("%-4s",str[i][j]);printf(" ");
	 	}
	 	printf("\n");
	 } 
	 return 0;
}

/*
可以看到 0012FF38 0012FF3C 0012FF40 0012FF44,这四个是元素单元所在的地址，每个地址相差四个字节，这是由于每个元素是一个指针变量占四个字节。。。

       char **s;

       char **为二级指针， s保存一级指针 char *的地址，关于二级指针就在这里不详细讨论了 ，简单的说一下二级指针的易错点。  

       举例：

       char *a [ ] = {"China","French","America","German"};

       char **s =   a;

       为什么能把 a赋给s,因为数组名a代表数组元素内存单元的首地址，即 a = &a[0] = 0012FF38;

       而 0x12FF38即 a[0]中保存的又是 00422FB8 ,这个地址， 00422FB8为字符串"China"的首地址。

       即 *s = 00422FB8 = "China";

         这样便可以通过s 操作 a 中的数据

      printf("%s",*s);

      printf("%s",a[0]);

      printf("%s",*a);

      都是一样的。。。

      但还是要注意，不能a = s，前面已经说到，a 是一个常量。。

      再看一个易错的点：

      char **s = "hello world";

      这样是错误的，

       因为  s 的类型是 char **  而 "hello world "的类型是 char *

       虽然都是地址， 但是指向的类型不一样，因此，不能这样用。，从其本质来分析，"hello world",代表一个地址，比如0x003001,这个地址中的内容是 'h'

  ,为 char 型，而 s 也保存一个地址 ，这个地址中的内容(*s) 是char *　，是一个指针类型，　所以两者类型是不一样的。　。。

　　如果是这样呢？
　　char  **s;

       *s = "hello world";

       貌似是合理的，编译也没有问题，但是 printf("%s",*s),就会崩溃

       why??

      咱来慢慢推敲一下。。

       printf("%s",*s); 时，首先得有s 保存的地址，再在这个地址中找到 char *  的地址，即*s;

      举例：

       s = 0x1000;

      在0x1000所在的内存单元中保存了"hello world"的地址 0x003001 ， *s = 0x003001;

      这样printf("%s",*s);

      这样会先找到 0x1000,然后找到0x003001;

      如果直接 char  **s;

      *s = "hello world";

       s 变量中保存的是一个无效随机不可用的地址， 谁也不知道它指向哪里。。。。，*s 操作会崩溃。。

       所以用 char **s 时，要给它分配一个内存地址。

      char  **s ;

      s = (char **) malloc(sizeof(char**));

      *s =  "hello world";

      这样 s 给分配了了一个可用的地址，比如 s = 0x412f;

      然后在 0x412f所在的内存中的位置，保存 "hello world"的值。。

    再如：

    #include  <stdio.h>

   void  buf( char **s)

    {

           *s = "message";

    }

    int main()

     {

        char *s ;

        buf(&s);

        printf("%s\n",s);

     }

    二级指针的简单用法。。。。，说白了，二级指针保存的是一级指针的地址，它的类型是指针变量，而一级指针保存的是指向数据所在的内存单元的地址，虽然都是地址，但是类型是不一样的。。。


*/
