//方法二，利用vector创建二维数组
#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;

int main()
{  
    int row,column;  
    cin>>row>>column;      //申请空间  
    vector<vector<int> > a(row, vector<int>(column));  
      
  
    //使用空间  
    for (int j = 0; j < row; ++j)  
    {
        for (int k = 0; k< column; ++k)  
        {
            a[j][k] = rand()%100;  
        }
    }
  
    for (int j = 0; j < row; ++j)  
    {  
        cout<<endl;  
        for (int k = 0; k < column; ++k)  
        {  
            a[j][k] = rand()%100;  
            cout<<a[j][k]<<"     ";  
        }  
    }         
    return 0;       
}
