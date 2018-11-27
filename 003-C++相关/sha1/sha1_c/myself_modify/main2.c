
/*
* sha1test.c
*
* Description:
* This file will exercise the SHA-1 code performing the three
* tests documented in FIPS PUB 180-1 plus one which calls
* SHA1Input with an exact multiple of 512 bits, plus a few
* error test checks.
*
* Portability Issues:
* None.
*
*/

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "SHA1.h"
#include <stdlib.h>

#define TEST1 "www.shbst.com"
int main()
{
	SHA1Context sha;
	int i ;
	uint8_t Message_Digest[20];
    char strRes[2];
    char result[50];
    
	SHA1Reset(&sha);
	SHA1Input(&sha,
				(const unsigned char *) TEST1,
				strlen(TEST1));
	SHA1Result(&sha, Message_Digest);	

	memset(result, 0, 50);
	for(i = 0; i < 20 ; ++i)
	{
	    printf("%02X ", Message_Digest[i]);
        
        if (0x00 == Message_Digest[i])  // 0x0
        {
            sprintf(strRes, "00");
        }
        else if (Message_Digest[i] < 0x10)
        {
            sprintf(strRes, "0%x", Message_Digest[i]);
        }
        else
        {        
	        sprintf(strRes, "%2x", Message_Digest[i]);
        }    
        sprintf(result + i*2, "%c%c", strRes[0], strRes[1]);
        
//	    printf("strRes = %s\n", strRes);        
//      printf("i = %d i*2 = %d\n", i, i*2);
//      printf("result + i*2 = %p\n", result + i*2);
	}
	printf("\n");	
	printf("result = %s\n", result);	
	for (i = 0; i < 40; i++)
	{
	    printf("%c", result[i]);
	}
	printf("\n");
	return 0;
}
// 3d cb b4 f3 d1 b9 8b a3 8c fc 39 7
// 3d cb b4 f3 d1 b9 8b a3 8c fc 39 07 6d 32 56 04 73 27 7c f0
// 3d cb b4 f3 d1 b9 8b a3 8c fc 39 07 6d 32 56 04 73 27 7c f0

