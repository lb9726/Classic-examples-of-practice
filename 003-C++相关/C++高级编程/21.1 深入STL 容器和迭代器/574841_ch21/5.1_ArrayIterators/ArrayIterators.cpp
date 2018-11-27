#include <vector>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
  int arr[10]; // normal C++ array
  vector<int> vec; // STL vector
  int i;

  //
  // Initialize each element of the array to the value of
  // its index.
  //
  for (i = 0; i < 10; i++) {
    arr[i] = i;
  }

  //
  // Insert the contents of the array into the
  // end of the vector.
  //
  vec.insert(vec.begin(), arr, arr + 10);
  /*
  需要注意，指示数组第一个元素的迭代器只是第一个元素的地址。指示最后位置的迭代器必须是越过最后一个元素的位置,
  因此这是第一个元素的地址加10。
  */
  // print the contents of the vector
  for (i = 0; i < 10; i++) {
    cout << vec[i] << " ";
  }
  cout << endl;
  return (0);
}
