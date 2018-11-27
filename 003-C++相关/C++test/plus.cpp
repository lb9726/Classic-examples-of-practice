#include <functional>
#include <iostream>
using namespace std;

int main()
{
    plus<int> myPlus;
    int res = myPlus(4, 5);
    cout << res << endl;
    return 0;
}
