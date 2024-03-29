#pragma once
#include <set>
#include <vector>
#include <iostream>

bool IsUpperBoundInRange(int upperBound);

void SiftNumbers(std::vector<bool>& sieve, int upperBound);

void GetNumbersSet(std::set<int>& set, std::vector<bool>& sieve, int upperBound);

std::set<int> GeneratePrimeNumbersSet(int upperBound);

bool GetUpperBound(int argc, char* argv[], int& upperBound);