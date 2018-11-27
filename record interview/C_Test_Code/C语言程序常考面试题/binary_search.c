//写出二分查找的代码
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

int binary_search(int *arr, int key, int n)
{
    int low = 0;
    int hign = n - 1;
    int mid;
    while (low <= high)
    {
        mid = (hign + low)/2;
        if (arr[mid] > k)
        {
           high = mid - 1;
        }
        else if (arr[mid] < k)
        {
            high = mid + 1;
        }
        else 
            return mid;
    }
    return -1;
}
