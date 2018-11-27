#include "Array.h"

#include <stdexcept>
#include <iostream>
using namespace std;

// Microsoft Visual Studio requires you to omit the following line.
// However, some compilers require it.
// const int Array::kAllocSize;

Array::Array()
{
    mSize = kAllocSize;
    mElems = new int[mSize];
}

Array::~Array()
{
    delete [] mElems;
}

void Array::resize(int newSize)
{
    int* newElems = new int[newSize]; // Allocate the new array of the new size
    cout <<__PRETTY_FUNCTION__<<"newSize = "<<newSize<<endl;
    // The new size is always bigger than the old size
    for (int i = 0; i < mSize; ++i)
    {
        // Copy the elements from the old array to the new one
        newElems[i] = mElems[i]; // i < newSize 时会，mElems[i]感觉可能会越界，但是运行却没有问题
        cout <<__PRETTY_FUNCTION__<<"mElems[i] = "<<mElems[i]<<endl;
        cout <<"is call "<<__PRETTY_FUNCTION__<<" i = "<< i <<endl;
    }
    if (mSize < newSize)
    {
        for (int j = mSize; j < newSize; ++j)
        {
            newElems[j] = 0;
        }
    }
    mSize = newSize; // store the new size
    delete [] mElems; // free the memory for the old array
    mElems = newElems; // Store the pointer to the new array
}

int& Array::operator[](int x)
{
    if (x < 0)
    {
        throw out_of_range("");
    }
    cout << "x = "<< x <<endl;
    if (x >= mSize)
    {
        // Allocate kAllocSize past the element the client wants
        resize (x + kAllocSize);
    }
    return (mElems[x]);
}

const int& Array::operator[](int x) const
{
    if (x < 0 || x >= mSize)
    {
        throw out_of_range("");
    }
    return (mElems[x]);
}
