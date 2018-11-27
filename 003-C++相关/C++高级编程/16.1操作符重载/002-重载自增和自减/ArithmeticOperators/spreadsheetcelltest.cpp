#include <iostream>
#include "spreadsheetcell.h"

using namespace std;

int main(int argc, char** argv)
{
    int i, j = 4;
    i = -j; // unary minus 一元减号
    i = +i; // unary plus 一元正号
    j = +(-i); // apply unary plus to the result of applying unary minus to i
    j = -(-i); // apply unary minus to the result of applying unary minus to i

    i = i + 1;
    i += 1;
    ++i;
    i++;

    SpreadsheetCell c1, c2, c3;
    c1.set(4);
    c2.set(4);

    c1++;
    ++c1;
    c3 = -c1;

    return (0);
}
