#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

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
        [min](float number) { return number * min; });
}

void SortInAscendingOrder(std::vector<float>& vector)
{
    sort(vector.begin(), vector.end());
}

void PrintVector(std::vector<float>& vector, std::ostream& output)
{
    for (float number: vector)
    {
        const char separator = ' ';
        output << number << separator;
    }
}

int main()
{
    std::vector <float> vector;
    float min = std::numeric_limits<float>::max();
    ReadInput(vector, std::cin, min);
    HandleVector(vector, min);
    SortInAscendingOrder(vector);
    PrintVector(vector, std::cout);
}