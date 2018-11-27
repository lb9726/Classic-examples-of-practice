#include <numeric>
#include <vector>
#include <cmath>
#include <functional>
using namespace std;

double geomericMean(const vector<int>& nums)
{
    double mult = accumulate(nums.begin(), nums.end(), 1, multiplies<int>());
    return (pow(mult, 1.0 / nums.size()));
}
