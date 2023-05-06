#include "ProcessVector.h"

int main()
{
    std::vector <float> vector;
    float min = std::numeric_limits<float>::max(); //min_element в stl 
    ReadInput(vector, std::cin, min);
    HandleVector(vector, min);
    SortInAscendingOrder(vector);
    PrintVector(vector, std::cout);
	return 0;
}