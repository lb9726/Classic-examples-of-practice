
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
	char *strRes;
	char *result = (char *)malloc(50);

	SHA1Reset(&sha);
	SHA1Input(&sha,
				(const unsigned char *) TEST1,
				strlen(TEST1));
	SHA1Result(&sha, Message_Digest);	
	printf("\t");
	memset(result, 0, 50);
	for(i = 0; i < 20 ; ++i)
	{
	    printf("%02X ", Message_Digest[i]);
	    sprintf(strRes,"%x", Message_Digest[i]);
	    printf("strRes = %s\n", strRes);
	    printf("strRes[0] = %c\n", strRes[0]);
	    printf("strRes[1] = %c\n", strRes[1]);
	    if (0 == i)
	        memcpy(result, strRes, 2);
	    else 
	        strncat(result, strRes, 2);
	}
	printf("\n");	
	printf("result = %s\n", result);	
	return 0;
}


