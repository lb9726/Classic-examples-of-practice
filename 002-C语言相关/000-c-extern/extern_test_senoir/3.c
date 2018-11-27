#include "3.h"

void delete_string(char str[], char ch)
{
    int i, j;
    for (i = j = 0; str[i] != '\0'; ++i)
    {
        if (ch != str[i])
        {
            str[j++] = str[i];
        }        
    }
    str[j] = '\0';
}
