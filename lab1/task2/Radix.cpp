#include <iostream>
#include <stdlib.h>
#include <limits>
#include <algorithm>
#include <math.h>

bool CheckInAvailableRange(int num)
{
	const int minNumberSystem = 2;
	const int maxNumberSystem = 36;
	bool isNumberInRange = ((minNumberSystem <= num) && (num <= maxNumberSystem));
	if (!isNumberInRange)
	{
		std::cout << "Error! " << num << " must be between " << minNumberSystem 
			<< " and " << maxNumberSystem << " !\n";
	}
	return isNumberInRange;
}

int ConvertCharToDec(char ch, int radix, bool& wasError)
{
	const int diffForChar = 55;
	const int diffForDigit = '0';
	int dec = ch;
	if (std::isdigit(ch))
	{
		dec -= diffForDigit;
	}
	else
	{
		dec -= diffForChar;
	}
	const int minDecValue = 0;
	const int maxDecValue = radix - 1;
	wasError = (dec > maxDecValue) || (dec < minDecValue);
	return dec;
}

bool CheckIntOverflow(int intValue, int addedValue, int radix)
{
	const int intMaxLimit = std::numeric_limits<int>::max();
	const int intMinLimit = std::numeric_limits<int>::min();
	return (intValue > ((intMaxLimit - addedValue) / radix)) ||
		(intValue < ((intMinLimit + addedValue) / radix));
}

int StringToInt(const std::string& str, int radix, bool& wasError)
{
	const int firstElem = 0;
	int startStringElement = firstElem;
	const char minus = *"-";
	const bool isNegative = str[0] == minus;
	if (isNegative)
	{
		const int secondElem = 1;
		startStringElement = secondElem;
	}
	int resultInt = 0;
	
	for (size_t i = startStringElement; i < str.length(); i++)
	{
		int dec = ConvertCharToDec(str[i], radix, wasError);
		wasError = wasError || (CheckIntOverflow(resultInt, dec, radix));
		if (wasError)
		{
			return resultInt;
		}
		resultInt *= radix;
		if (isNegative)
		{
			resultInt -= dec;
		}
		else
		{
			resultInt += dec;
		}
	}
	
	return resultInt;
}

bool CheckParametersNumberPassed(int parametersNumber)
{
	const int expectedParametersNumber = 4;
	if (parametersNumber != expectedParametersNumber)
	{
		std::cout << "The number of parameters must be " <<
			expectedParametersNumber << " !\n";
		return false;
	}
	return true;
}

char ConvertIntToChar(int number)
{
	const int maxDecDigit = 9;
	const int diffForChar = 55;
	if (number > maxDecDigit)
	{
		return number + diffForChar;
	}
	const int diffCodeForDigit = '0';
	return number + diffCodeForDigit;
}

std::string IntToString(int n, int radix, bool& wasError)
{
	const int zero = 0;
	unsigned int number = n;
	const bool isNegative = n < zero;
	if (isNegative)
	{
		number = abs(n);
	}
	std::string resultString = "";
	int excess;
	while (number >= radix)
	{  
		excess = number % radix;
		number /= radix;
		resultString += ConvertIntToChar(excess);
	}
	resultString += ConvertIntToChar(number);
	if (isNegative)
	{
		const char minus = '-';
		resultString += minus;
	}
	std::reverse(resultString.begin(), resultString.end());
	return resultString;
}

void ConvertValueFromSourceToDestination(const std::string& value, int sourceNotation,
	int destinationNotation, bool& wasError)
{
	int dec = StringToInt(value, sourceNotation, wasError);
	if (wasError)
	{
		std::cout << "An error occurred while string to int conversion!\n";
		return;
	}
	std::string resultString = IntToString(dec, destinationNotation, wasError);
	if (wasError)
	{
		std::cout << "An error occurred while int to string conversion!\n";
		return;
	}
	std::cout << resultString << "\n";
}

int main(int argc, char* argv[])
{
	if (!CheckParametersNumberPassed(argc))
	{
		return 1;
	}
	bool wasError = 0;
	const int sourceNotation = atoi(argv[1]);
	const int destinationNotation = atoi(argv[2]);
	if (!CheckInAvailableRange(sourceNotation) ||
		!CheckInAvailableRange(destinationNotation))
	{
		return 2;
	}
	ConvertValueFromSourceToDestination(argv[3], sourceNotation,
		destinationNotation, wasError);
	if (wasError)
	{
		return 3;
	}
	return 0;
} 