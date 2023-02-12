#define _OPEN_SYS_ITOA_EXT
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <limits>

bool CheckInAvailableRange(const int& num, const int& min,
	const int& max)
{
	return ((min <= num) && (num <= max));
}

int ConvertCharToDec(const char& val, const int& numSystem, bool& wasError)
{
	int codeDiffValue = 55;
	if (std::isdigit(val))
	{
		codeDiffValue = 48;
	}
	const int result = (int)val - codeDiffValue;
	const int minResult = 0;
	const int maxResult = numSystem - 1;
	if (!CheckInAvailableRange(result, minResult, maxResult))
	{
		wasError = 1;
	}
	return result;
}

int StringToInt(const std::string& str, int radix, bool& wasError, bool& isNegative)
{
	int result = 0;
	const int intMaxValue = std::numeric_limits<int>::max();
	int startValue = 0;
	const char minus = *"-";
	if (str[0] == minus)
	{
		isNegative = 1;
		startValue = 1;
	}
	for (size_t i = startValue; i < str.length(); i++)
	{
		int val = ConvertCharToDec(str[i], radix, wasError);
		if (wasError)
		{
			return result;
		}
		if (result <= ((intMaxValue - val) / radix))
		{
			result *= radix;
			result += val;
		}
		else
		{
			wasError = 1;
			break;
		}
	}
	return result;
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
	const int minNumberSystem = 2;
	const int maxNumberSystem = 36;
	if (!CheckInAvailableRange(sourceNotation, minNumberSystem, maxNumberSystem) ||
		!CheckInAvailableRange(destinationNotation, minNumberSystem, maxNumberSystem))
	{
		std::cout << "Error! " << sourceNotation << " and " << destinationNotation <<
			" must be between " << minNumberSystem << " and " << maxNumberSystem << " !\n";
		return 1;	
	}
	const std::string value = argv[3];
	bool wasError = 0;
	bool isNegative = 0;
	int dec = StringToInt(value, sourceNotation, wasError, isNegative);
	if (wasError)
	{
		std::cout << "An error occurred while executing the program!\n";
		return 1;
	}
	const int bufferSize = sizeof(int) * 8 + 1;
	char buffer[bufferSize];
	errno_t errorCode = _itoa_s(dec, buffer, destinationNotation);
	if (errorCode != 0)
	{
		std::cout << "Error!\n";
		return 1;
	}
	if (isNegative)
	{
		std::cout << "-";
	}
	printf("%s\n", buffer);
	return 0;
}