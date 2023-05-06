#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>

void ReadInput(std::vector<float>& vector, std::istream& input, float& min);

void HandleVector(std::vector<float>& vector, float& min);

void SortInAscendingOrder(std::vector<float>& vector);

void PrintVector(const std::vector<float>& vector, std::ostream& output);