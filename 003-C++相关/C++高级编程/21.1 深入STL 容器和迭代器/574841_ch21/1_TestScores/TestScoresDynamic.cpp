#include <vector>
#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
  vector<double> doubleVector; // create a vector with zero elements
  double max, temp;
  size_t i;

  // Read the first score before the loop in order to initialize max
  cout << "Enter score 1: ";
  cin >> max;
  doubleVector.push_back(max);

  for (i = 1; true; i++) {
    cout << "Enter score " << i + 1 << " (-1 to stop): ";
    cin >> temp;
    if (temp == -1) {
      break;
    }
    doubleVector.push_back(temp);
    if (temp > max) {
      max = temp;
    }
  }

  max /= 100;
  for (i = 0; i < doubleVector.size(); i++) { 
    doubleVector[i] /= max;
    cout << doubleVector[i] << " ";
  }
  cout << endl;
  return (0);
}

/*
这个版本的程序使用了默认构造函数来创建一个包含0个元素的vector。读入每个分数后，它会通过push_back()方法增加到vector中。push_back()会负责为这个新元素分配空间。需要注意，最后一个for循环对vector使用了size()方法来确定容器中元素的个数。size()返回一个无符号整数，所以为了做到兼容，i的类型改为size_t。
*/
