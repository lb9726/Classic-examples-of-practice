/*
根据方法五的思想，本人编写了my_debug.h（见程序7）和my_debug.c 文件（见程序8）。
该文件可以应用于C语言程序中，支持根据不同的功能模块分别定义不同的调试等级。
*/

 #ifndef JUDGESTRING_H
 #define JUDGESTRING_H
 
 #include <stdio.h>
 
 // 模块功能号
 enum {
 
 	MY_SECTION_FACT = 0,
    MY_SECTION_nnn1,
    MY_SECTION_nnn2,
    MY_SECTION_nnnn, 
    MY_SECTION_END,
 };
 
 // 非my_debug.c文件的外部变量声明
 #ifndef MY_DEBUG_C
 extern int __my_allow_debug_levels[MY_SECTION_END];
 #endif
 
 // (内部使用) 判断"SECTION"模块功能号是否允许"DEBUG_LEVEL"等级的调试信息输出
 #define __my_unallow_debug(SECTION, DEBUG_LEVEL) ( DEBUG_LEVEL > __my_allow_debug_levels[SECTION] )
 
 // (内部使用) 调试信息输出函数
 #define __my_debug(FORMAT, ARG...) printf("%s : %d  %s: " FORMAT, __FILE__, __LINE__, __FUNCTION__, ##ARG)
 
 // 初始化"SECTION"模块功能号的调试等级
 #define my_init_debug_levels(SECTION, ALLOW_DEBUG_LEVEL) ( __my_allow_debug_levels[SECTION] = ALLOW_DEBUG_LEVEL )
 
 // 调试信息输出函数，该信息为"SECTION"模块功能号"DEBUG_LEVEL"等级的调试信息
 #define my_debug(SECTION, DEBUG_LEVEL) ( __my_unallow_debug(SECTION, DEBUG_LEVEL) ) ? (void) 0 : __my_debug
 
 #endif //MY_DEBUG_H
// 程序7: my_debug.h
/* 
 程序8: my_debug.c

要使用上述文件，先得根据功能模块的数目扩展my_debug.h中的“模块功能号”枚举类型，然后在程序相应位置中调用宏定义my_init_debug_levels 初始化相应模块的调试等级，在所有需要输出调试信息的位置如下编写即可。

my_debug(MY_SECTION_FACT, 250)("i=%d ; f=%d/n", i, f);
下面我们来看看如何在fact.c中使用它们（见程序9）。
*/

