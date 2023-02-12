#include <iostream>

bool checkInAvailableRange(const int& numberSystem, const int& min,
	const int& max)
{
	return ((min <= numberSystem) && (numberSystem <= max));
}

int main(int argc, char* argv[])
{
	const int parametersNumber = 4;
	if (argc != parametersNumber)
	{
		std::cout << "The number of parameters must be " << parametersNumber << " !\n";
		return 1;
	}
	const int sourceNotation = atoi(argv[1]);
	const int destinationNotation = atoi(argv[2]);
	const int value = atoi(argv[3]);
	const int minNumberSystem = 2;
	const int maxNumberSystem = 36;
	if (!checkInAvailableRange(sourceNotation, minNumberSystem, maxNumberSystem) ||
		!checkInAvailableRange(destinationNotation, minNumberSystem, maxNumberSystem))
	{
		std::cout << "Error! " << sourceNotation << " and " << destinationNotation <<
			" must be between " << minNumberSystem << " and " << maxNumberSystem << " !\n";
		std::cout << "Error! " << minNumberSystem <= sourceNotation << " and " << minNumberSystem <= destinationNotation << " must be between " << minNumberSystem << " and " << maxNumberSystem << " !\n";
		return 1;
	}
	return 0;
}
