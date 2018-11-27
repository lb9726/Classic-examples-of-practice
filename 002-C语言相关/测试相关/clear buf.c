#include<stdio.h>
int main(int argc, char const *argv[])
{
    char ch1;
    char ch2;
    scanf("%c",&ch1);
    printf("ch1 = %d\n",ch1);
    setbuf(stdin,NULL);
    scanf("%c",&ch2);
    printf("ch2 = %d\n",ch2 );
    return 0;
}

/*

#include<stdio.h>

int main(void)
       {
           char buf[BUFSIZ];
           setbuf(stdin, buf);
           printf("Hello, world!\n");
           return 0;
       }

程序输出有两种方式：一种是即时处理方式，另一种是先暂存起来，然后再大块写入的方式，前者往往造成较高的系统负担。因此，c语言实现通常都允许程序员进行实际的写操作之前控制产生的输出数据量。

这种控制能力一般是通过库函数setbuf实现的。如果buf是一个大小适当的字符数组，那么：

setbuf(stdout，buf);

语句将通知输入/输出库，所有写入到stdout的输出都应该使用buf作为输出缓冲区，直到buf缓冲区被填满或者程序员直接调用fflush（译注：对于由写操作打开的文件，调用fflush将导致输出缓冲区的内容被实际地写入该文件），buf缓冲区中的内容才实际写入到stdout中。缓冲区的大小由系统头文件<stdio.h>中的BUFSIZ定义。

下面的程序的作用是把标准输入的内容复制到标准输出中，演示了setbuf库函数最显而易见的用法：

#include <stdio.h>

main()

{

int c;

char buf[BUFSIZ];

setbuf(stdout, buf);

    while((c=getchar())!=EOF)

        putchar(c);

}

    遗憾的是，这个程序是错误的，仅仅是因为一个细微的原因。程序中对库函数setbuf的调用，通知了输入/输出库所有字符的标准输出应该首先缓存在buf中。要找到问题出自何处，我们不妨思考一下buf缓冲区最后一次被清空是在什么时候？答案是在main函数结束之后，作为程序交回控制给操作系统之前C运行时库所必须进行的清理工作的一部分。但是，在此之前buf字符数组已经被释放！

    要避免这种类型的错误有两种办法。第一种办法是让缓冲数组成为静态数组，既可以直接显式声明buf为静态：

static char buf[BUFSIZ];

也可以把buf声明完全移到main函数之外。第二种办法是动态分配缓冲区，在程序中并不主动释放分配的缓冲区（译注：山于缓冲区是动态分配的，所以main函数结束时并不会释放该缓冲区，这样C运行时库进行清理工作时就不会发生缓冲区已释放的情况）：

char *malloc();

setbuf(stdout，malloc(BUFSIZ));

    如果读者关心一些编程“小技巧”，也许会注意到这里其实并不需要检查malloc函数调用是否成功。如果malloc函数调用失败，将返回一个null指针。setbuf函数的第二个参数取值可以为null，此时标准输出不需要进行缓冲。这种情况下，程序仍然能够工作，只不过速度较慢而已。
*/





/*
语言清空输入缓冲区的N种方法对比
C语言中有几个基本输入函数：

//获取字符系列
int fgetc(FILE *stream);
int getc(FILE *stream);
int getchar(void);
//获取行系列
char *fgets(char * restrict s, int n, FILE * restrict stream);
char *gets(char *s);//可能导致溢出，用fgets代替之。
//格式化输入系列
int fscanf(FILE * restrict stream, const char * restrict format, …);
int scanf(const char * restrict format, …);
int sscanf(const char * restrict str, const char * restrict format, …);
这里仅讨论输入函数在标准输入（stdin）情况下的使用。纵观上述各输入函数，
获取字符系列的的前三个函数fgetc、getc、getchar。以getchar为例，将在stdin缓冲区为空时，等待输入，直到回车换行时函数返回。若stdin缓冲区不为空，getchar直接返回。getchar返回时从缓冲区中取出一个字符，并将其转换为int，返回此int值。
MINGW 4.4.3中FILE结构体源码：

typedef struct _iobuf
{
	char*	_ptr;//指向当前缓冲区读取位置
	int	_cnt;//缓冲区中剩余数据长度
	char*	_base;
	int	_flag;
	int	_file;
	int	_charbuf;
	int	_bufsiz;
	char*	_tmpfname;
} FILE;
各编译器实现可能不一样，这里获取字符系列函数只用到_ptr和_cnt。
MINGW 4.4.3中getchar()实现：

__CRT_INLINE int __cdecl __MINGW_NOTHROW getchar (void)
{
  return (--stdin->_cnt >= 0)
    ?  (int) (unsigned char) *stdin->_ptr++
    : _filbuf (stdin);
}
其中stdin为FILE指针类型，在MINGW 4.4.3中，getc()和getchar()实现为内联函数，fgetc()实现为函数。顺便说一句，C99标准中已经加入对内联函数的支持了。

获取行系列的fgets和gets，其中由于gets无法确定缓冲区大小，常导致溢出情况，这里不推荐也不讨论gets函数。对于fgets函数，每次敲入回车，fgets即返回。fgets成功返回时，将输入缓冲区中的数据连换行符’\n’一起拷贝到第一个参数所指向的空间中。若输入数据超过缓冲区长度，fgets会截取数据到前n-1（n为fgets第二个参数，为第一个参数指向空间的长度），然后在末尾加入’\n’。因此fgets是安全的。通常用fgets(buf, BUF_LEN, stdin);代替gets(buf);。
格式化输入系列中，fscanf从文件流进行格式化输入很不好用。常用的还是scanf，格式化输入系列函数舍去输入数据（根据函数不同可能是标准输入也可能是字符串输入，如：sscanf）前的空白字符（空格、制表符、换行符）直至遇到非空白字符，然后根据格式参数尝试对非空白字符及后续字符进行解析。该系列函数返回成功解析赋值的变量数，若遇文件尾或错误，返回EOF。
=================分 割 线=================

提到缓冲区，就不得不提setbuf和setvbuf两个缓冲区设置函数，其声明如下：

void setbuf(FILE * restrict stream, char * restrict buf);
int setvbuf(FILE * restrict stream, char * restrict buf, int mode, size_t size);
setvbuf的mode参数有：

_IOFBF（满缓冲）：缓冲区空时读入数据；缓冲区满时向流写入数据。
_IOLBF（行缓冲）：每次从流读入一行数据或向流写入数据。如：stdio,stdout
_IONBF（无缓冲）：直接从流读入数据，或者直接向流写入数据，而没有缓冲区。如：stderr
setbuf(stream, buf);在：

buf == NULL：等价于(void)setvbuf(stream, NULL, _IONBF, 0);
buf指向长度为BUFSIZ的缓冲区：等价于(void)setvbuf(stream, buf, _IOFBF, BUFSIZ);
注：BUFSIZ宏在stdio.h中定义。

 

这里还要提一下传说中的setbuf的经典错误，在《C陷阱和缺陷》上有提到：

int main()
{
    int c;
    char buf[BUFSIZ];
    setbuf(stdout,buf);
    while((c = getchar()) != EOF)
        putchar(c);
    
    return 0;
}
问题是这样的：程序交回控制给操作系统之前C运行库必须进行清理工作，其中一部分是刷新输出缓冲，但是此时main函数已经运行完毕，buf缓冲区作用域在main函数中，此时buf字符数组已经释放，导致输出诡异乱码。

解决方案：可以将buf设置为static，或者全局变量，或者调用malloc来动态申请内存。

=================分 割 线=================

下面来看看几种流行的缓冲区清空方法：

fflush(stdin);式
由C99标准文档中：

If stream points to an output stream or an update stream in which the most recent
operation was not input, the fflush function causes any unwritten data for that stream
to be delivered to the host environment to be written to the ﬁle; otherwise, the behavior is
undeﬁned.
可以看出fflush对输入流为参数的行为并未定义。但由MSDN上的fflush定义：

If the file associated with stream is open for output, fflush writes to that file the 
contents of the buffer associated with the stream. If the stream is open for input, 
fflush clears the contents of the buffer. 
可以看出fflush(stdin)在VC上还是有效地！鉴于各编译器对fflush的未定义行为实现不一样，不推荐使用fflush(stdin)刷新输入缓冲区。

setbuf(stdin, NULL);式
由前面对setbuf函数的介绍，可以得知，setbuf(stdin, NULL);是使stdin输入流由默认缓冲区转为无缓冲区。都没有缓冲区了，当然缓冲区数据残留问题会解决。但这并不是我们想要的。

scanf("%*[^\n]");式（《C语言程序设计 现代方法 第二版》中提到）
这里用到了scanf格式化符中的“*”，即赋值屏蔽；“%[^集合]”，匹配不在集合中的任意字符序列。这也带来个问题，缓冲区中的换行符’\n’会留下来，需要额外操作来单独丢弃换行符。

经典式
int c;
while((c = getchar()) != '\n' && c != EOF);
由代码知，不停地使用getchar()获取缓冲区中字符，直到获取的字符c是换行符’\n’或者是文件结尾符EOF为止。这个方法可以完美清除输入缓冲区，并且具备可移植性。

scanf("%*[^\n]");
scanf("%*c");
就可以去掉\n了。

*/
