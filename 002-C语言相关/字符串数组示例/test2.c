#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<string.h>
int main()
{	
	char **name;
    *name = (char *)malloc(sizeof(char *)*30); printf("name = %p\n",name);
	strcpy(*name,"哈哈哈哈和");
	printf("%s\n",name);printf("name = %p\n",name);
	int len = strlen(*name);
	printf("len = %d\n",len);
	return 0;
}

/*
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
*/
/*
int main()
{	
	
	char **name;
    name[1] = (char *)malloc(sizeof(char *)*30); 
	strcpy(name[1],"哈哈哈哈和");
	int len = strlen(name[1]);
	printf("len = %d\n",len);
	return 0;
}

编译没有错误，没有警告，但是运行出现段错误


int main()
{	
	
	char **name;
    name = (char *)malloc(sizeof(char *)*30); 
	strcpy(name[1],"哈哈哈哈和");
	int len = strlen(name[1]);
	printf("len = %d\n",len);
	return 0;
}
编译没有错误，没有警告，但是运行出现段错误

int main()
{	
	
	char **name;
    *name = (char **)malloc(sizeof(char *)*30); 
	strcpy(*name,"哈哈哈哈和");
	int len = strlen(*name);
	printf("len = %d\n",len);
	return 0;
}

编译没有错误，有警告，但是运行结果为len = 15
int main()
{	
	
	char **name;
    *name = (char *)malloc(sizeof(char *)*30); 
	strcpy(*name,"哈哈哈哈和");
	int len = strlen(*name);
	printf("len = %d\n",len);
	return 0;
}

编译没有错误，没有警告，运行结果为len = 15

int main()
{	
	char **name;
    *name = (char *)malloc(sizeof(char *)*30); printf("name = %p\n",name);
	strcpy(*name,"哈哈哈哈和");
	printf("%s\n",name);printf("name = %p\n",name);
	int len = strlen(*name);
	printf("len = %d\n",len);
	return 0;
}
编译没有错误有警告，运行段错误
test2.c: In function ‘main’:
test2.c:10:2: warning: format ‘%s’ expects argument of type ‘char *’, but argument 2 has type ‘char **’ [-Wformat=]
  printf("%s\n",name);printf("name = %p\n",name);
  ^
libo@libo:~/Desktop/Classic-examples-of-practice/字符串数组示例$ ./test2
段错误 (核心已转储)

*/





