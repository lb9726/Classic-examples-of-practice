#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    int i=123;
    int j=456;
    int const a;
    const int b;
    const int *c;
    int const *d;
    int *const e;
//    int *f const;  Test_const.c:14:12: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘const’
//    int const * g const;  Test_const.c:15:19: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘const’
    int const * const g ;
    const int * const p;
    a = i;  // Test_const.c:17:5: error: assignment of read-only variable ‘a’
    b = j;  // Test_const.c:18:5: error: assignment of read-only variable ‘b’
    
    c = &i; // OK 
    *c = i; // Test_const.c:21:5: error: assignment of read-only location ‘*c’
    
    d = &i; // OK
    *d = i; // Test_const.c:24:5: error: assignment of read-only location ‘*d’
    
    e = &i; // Test_const.c:26:5: error: assignment of read-only variable ‘e’
    *e = i; // OK
    
    g = &i; // Test_const.c:29:5: error: assignment of read-only variable ‘g’
    *g = i; // Test_const.c:30:5: error: assignment of read-only location ‘*g’
 
    p = &i; // Test_const.c:33:5: error: assignment of read-only variable ‘p’
    *p = i; // Test_const.c:34:5: error: assignment of read-only location ‘*p’
    
    return 0;
}
