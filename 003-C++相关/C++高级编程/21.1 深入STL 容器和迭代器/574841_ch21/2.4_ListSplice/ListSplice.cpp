#include <list>
#include <string>
#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
  list<string> dictionary, bWords;

  // Add the a words
  dictionary.push_back("aardvark");
  dictionary.push_back("ambulance");
  dictionary.push_back("archive");

  // Add the c words
  dictionary.push_back("canticle");
  dictionary.push_back("consumerism");
  dictionary.push_back("czar");

  // create another list of the b words
  bWords.push_back("bathos");
  bWords.push_back("balderdash");
  bWords.push_back("brazen");

  // splice the b words into the main dictionary.
  list<string>::iterator it;
  int i;

  // Iterate up to the spot where we want to insert bs
  // for loop body intentionally empty -- we're just moving up three elements
  for (it = dictionary.begin(), i = 0; i < 3; ++it, ++i);

  // Add in the bwords. This action removes the elements from bWords.
  dictionary.splice(it, bWords);

  // print out the dictionary
  for (it = dictionary.begin(); it != dictionary.end(); ++it) {
    cout << *it << endl;
  }

  return (0);
}
/*
aardvark
ambulance
archive
bathos
balderdash
brazen
canticle
consumerism
czar

list::splice实现list拼接的功能。将源list的内容部分或全部元素删除，拼插入到目的list。

函数有以下三种声明：
void splice ( iterator position, list<T,Allocator>& x );  // 
void splice ( iterator position, list<T,Allocator>& x, iterator i );
void splice ( iterator position, list<T,Allocator>& x, iterator first, iterator last );

函数说明：在list间移动元素：
将x的元素移动到目的list的指定位置，高效的将他们插入到目的list并从x中删除。
目的list的大小会增加，增加的大小为插入元素的大小。x的大小相应的会减少同样的大小。
前两个函数不会涉及到元素的创建或销毁。

第三个函数会。
指向被删除元素的迭代器会失效。
参数：
position
目的list的位置，用来标明 插入位置
x
源list、first,last
x里需要被移动的元素的迭代器。区间为[first, last).
包含first指向的元素，不包含last指向的元素。
*/




