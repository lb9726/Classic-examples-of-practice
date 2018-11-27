#include <stdio.h>  
#include <stdlib.h>  
#include "md5.h"  
#include <string.h>
int main(int argc, char *argv[])  
{  
    int i;  
    unsigned char encrypt[] ="www.shbst.com";  
    unsigned char decrypt[16];      
    MD5_CTX md5;  
    MD5Init(&md5);                
    MD5Update(&md5, encrypt, strlen((char *)encrypt));  
    MD5Final(&md5, decrypt);          
    printf("加密前:%s\n加密后:", encrypt);  
    for(i = 0; i < 16; i++)  
    {  
        printf("%02x", decrypt[i]);  
    }
    printf("\n");  
    return 0;  
}
/*
admin 21232f297a57a5a743894a0e4a801fc3
abcd  e2fc714c4727ee9395f324cd2e7f331f
www.shbst.com   d03bc75a01af7050620c579769bb7c45
*/

