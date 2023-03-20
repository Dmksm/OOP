#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../GeneratePrimeNumbersSet/GeneratePrimeNumbersSetHandler.h"

SCENARIO("Generating prime numbers set")
{
	WHEN("input upper bound is -2")
	{
		THEN("generated set is empty")
		{
			int upperBound = -2;
			std::set<int> set;
			REQUIRE(GeneratePrimeNumbersSet(upperBound) == set);
		}
	}
	WHEN("input upper bound is 1")
	{
		THEN("generated set is empty")
		{
			int upperBound = 1;
			std::set<int> set;
			REQUIRE(GeneratePrimeNumbersSet(upperBound) == set);
		}
	}
	WHEN("input upper bound is 2")
	{
		THEN("generated set will contains 2")
		{
			int upperBound = 2;
			std::set<int> set = {2};
			REQUIRE(GeneratePrimeNumbersSet(upperBound) == set);
		}
	}
	WHEN("input upper bound is 100")
	{
		THEN("generated set will contaims first 100 prime numbers")
		{
			int upperBound = 100000000;
			std::set<int> set = {};
			REQUIRE(GeneratePrimeNumbersSet(upperBound).size() == 5761455);
		}
	}
	WHEN("input upper bound is 100")
	{
		THEN("generated set will contaims first 100 prime numbers")
		{
			int upperBound = 100;
			std::set<int> set = {
				2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31,
				37, 41, 43, 47, 53, 59, 61, 67, 71, 73,
				79, 83, 89, 97};
			REQUIRE(GeneratePrimeNumbersSet(upperBound) == set);
		}
	}
	WHEN("input upper bound is 1000")
	{
		THEN("generated set will contaims first 1000 prime numbers")
		{
			int upperBound = 1000;
			std::set<int> set = { 
				2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31,
				37, 41, 43, 47, 53, 59, 61, 67, 71, 73,
				79, 83, 89, 97, 101, 103, 107, 109, 113, 127,
				131, 137, 139, 149, 151, 157, 163, 167, 173, 179,
				181, 191, 193, 197, 199, 211, 223, 227, 229, 233,
				239, 241, 251, 257, 263, 269, 271, 277, 281, 283,
				293, 307, 311, 313, 317, 331, 337, 347, 349, 353,
				359, 367, 373, 379, 383, 389, 397, 401, 409, 419,
				421, 431, 433, 439, 443, 449, 457, 461, 463, 467,
				479, 487, 491, 499, 503, 509, 521, 523, 541, 547,
				557, 563, 569, 571, 577, 587, 593, 599, 601, 607,
				613, 617, 619, 631, 641, 643, 647, 653, 659, 661,
				673, 677, 683, 691, 701, 709, 719, 727, 733, 739,
				743, 751, 757, 761, 769, 773, 787, 797, 809, 811,
				821, 823, 827, 829, 839, 853, 857, 859, 863, 877,
				881, 883, 887, 907, 911, 919, 929, 937, 941, 947,
				953, 967, 971, 977, 983, 991, 997 
			};
			REQUIRE(GeneratePrimeNumbersSet(upperBound) == set);
		}
	}
}
SCENARIO("Getting numbers set")
{
	WHEN("input sieve is 2")
	{
		THEN("generated set is 2")
		{
			std::set<int> set, resultSet = {2};
			std::vector<bool> sieve = {0, 0, 1};
			GetNumbersSet(set, sieve);
			REQUIRE(set == resultSet);
		}
	}
	WHEN("input sieve is first 11 numbers")
	{
		THEN("generated set is first 11 primary numbers")
		{
			std::set<int> set, resultSet = { 2, 3, 5, 7, 11 };
			std::vector<bool> sieve = { 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0};
			GetNumbersSet(set, sieve);
			REQUIRE(set == resultSet);
		}
	}
}
SCENARIO("Sift numbers")
{
	WHEN("input size sieve is 2")
	{
		THEN("result sieve is first 2 values")
		{
			std::vector<bool> sieve(2, true),
				resultSieve = {1, 1};
			SiftNumbers(sieve);
			REQUIRE(sieve == resultSieve);
		}
	}

	WHEN("input size sieve is 15")
	{
		THEN("result sieve is first 15 values")
		{
			std::vector<bool> sieve(15, true), 
				resultSieve = { 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1 };
			SiftNumbers(sieve);
			REQUIRE(sieve == resultSieve);
		}
	}
}