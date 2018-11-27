#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void st()
{
    printf(" %s() ceshi 1 %d !\n",__PRETTY_FUNCTION__ , __LINE__);
    printf(" %s() ceshi 2 %d !\n",__FUNCTION__ , __LINE__);
}

int main()
{
    printf(" %s() opening file occurs error %d！\n",__PRETTY_FUNCTION__ , __LINE__);
    printf(" %s() opening file occurs error %d！\n",__FUNCTION__, __LINE__);
    st();
    return 0;
}


