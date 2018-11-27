#include <iostream>
#include <stdlib.h>

using namespace std;


int main()
{
    int row,column;
    cin >> row >> column;
    //申请空间
    int **a =  new int* [row];    
    for(int i = 0; i < row; i++)
    {
        a[i] = new int[column];
    }

    //使用空间
    for(int j = 0; j < row; j++)
    {
        for(int k = 0; k < column; k++)
        {
            a[j][k] = rand() % 100;
        }
    }
    
    for(int j = 0; j < row; j++)
    {
        cout << endl;
        for(int k = 0; k < column; k++)
        {
            cout << a[j][k] << " ";
        }
    }
    cout<<endl;
    //释放空间
    for(int i = 0; i < row; i++)
    {
        delete []a[i];
    }
    delete a;
    a = NULL;

    return 0;
}
