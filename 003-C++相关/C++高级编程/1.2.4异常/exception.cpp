#include <stdexcept>
#include <iostream>
#include <stdexcept>

double divideNumbers(double inNumberator, double inDenominator)
{
	if (inDenominator == 0)
	{
		throw std::exception();
	}
	return (inNumberator / inDenominator);
}

int main()
{
    try {
        std::cout << divideNumbers(2.5, 0.5) << std::endl;
        std::cout << divideNumbers(2.3, 0) << std::endl;
    }catch(std::exception exception) {
        std::cout << "An exception was caught!" << std::endl;
    }
}
