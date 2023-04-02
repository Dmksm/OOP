#include "GeneratePrimeNumbersSetHandler.h"

bool IsUpperBoundInRange(int upperBound)
{
	const int MAX_UPPER_BOUND = 100000000;
	const int MIN_UPPER_BOUND = 2;
	if (upperBound > MAX_UPPER_BOUND || upperBound < MIN_UPPER_BOUND)
	{
		std::cout << "No prime numbers found for upper bound = " << upperBound <<
			" ! Enter a number from a valid range: " <<
			MIN_UPPER_BOUND << " - " << MAX_UPPER_BOUND << std::endl;
		return false;
	}
	return true;
}

void SiftNumbers(std::vector<bool>& sieve, int upperBound)
{
	for (size_t i = 3; i * i <= upperBound; i += 2)
	{
		if (sieve[(i - 1) / 2] == true)
		{
			for (size_t j = i * i; j <= upperBound; j += 2 * i)
			{
				sieve[(j - 1) / 2] = false;
			}
		}
	}
}

//выделятьпамять только столько сколько используем (
void GetNumbersSet(std::set<int>& set, std::vector<bool>& sieve, int upperBound)
{
	set.insert(set.end(), 2);
	for (size_t i = 3; i <= upperBound; i += 2)
	{
		if (sieve[(i - 1) / 2] == true)
		{
			set.insert(set.end(), i);
		}
	}
}


std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	std::set<int> resultSet;
	if (!IsUpperBoundInRange(upperBound))
	{
		return resultSet;
	}

	std::vector<bool> sieve(upperBound / 2 + 1, true);
	SiftNumbers(sieve, upperBound);
	GetNumbersSet(resultSet, sieve, upperBound);
	return resultSet;
}

bool GetUpperBound(int argc, char* argv[], int& upperBound)
{
	if (argc == 2)
	{
		upperBound = atoi(argv[1]);
		return true;
	}
	return false;
}