#include "ProcessVector.h"

void ReadInput(std::vector<float>& vector, std::istream& input, float& min)
{
	float number;
	while (input >> number)
	{
		vector.push_back(number);
		if (min > number)
		{
			min = number;
		}
	}
}

void HandleVector(std::vector<float>& vector, float& min)
{
	std::transform(vector.begin(), vector.end(), vector.begin(),
		[min](float number) {
			if (abs(number) > abs(FLT_MAX / min))
			{
				if (((number > 0) && (min > 0)) || ((number < 0) && (min < 0)))
				{
					return FLT_MAX;
				}
				if (((number > 0) && (min < 0)) || ((number < 0) && (min > 0)))
				{
					return -FLT_MAX;
				}
			}
			return number * min; 
		}
	);
}

void SortInAscendingOrder(std::vector<float>& vector)
{
	sort(vector.begin(), vector.end());
}

void PrintVector(const std::vector<float>& vector, std::ostream& output)
{
	for (float number : vector)
	{
		const char SEPARATOR = ' ';
		output << number << SEPARATOR;
	}
}