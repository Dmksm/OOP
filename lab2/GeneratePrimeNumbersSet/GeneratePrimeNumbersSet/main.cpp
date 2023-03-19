#include "GeneratePrimeNumbersSetHandler.h"

int main(int argc, char* argv[])
{
	int upperBound = 0;
	if (!GetUpperBound(argc, argv, upperBound))
	{
		return 1;
	}
	
	for (int num : GeneratePrimeNumbersSet(upperBound))
	{
		std::cout << num << " ";
	}
	return 0;
}