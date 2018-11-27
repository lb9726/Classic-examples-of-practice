#include <stdio.h>
// 定义枚举类型
enum days {monday,tuesday,wednesday,thursday,friday,saturday,sunday};
typedef enum days days; // 我们可以使用 days 来代替 enum days
days yesterday(days today){
    return (today+6)%7;
}
days tomorrow(days today){
    return (today+1)%7;
}
// 常量字符串数组
const char * const thedays[] = {"monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday"};
int main(void){
    days today;
    printf("today    \tyesterday  \ttomorrow\n"
          "============================================\n");
    for (today=monday;today<=sunday;today++)
        printf("%s = %d \t %s = %d \t %s = %d\n",
    thedays[today], today,
    thedays[yesterday(today)], yesterday(today),
    thedays[tomorrow(today)], tomorrow(today));
}
