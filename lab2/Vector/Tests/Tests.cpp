#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../Vector/ProcessVector.h"

SCENARIO("Read input")
{
	WHEN("Empty input")
	{
		THEN("Empty vector")
		{
			float min;
			std::vector<float> emptyVector;
			std::istringstream input("");
			ReadInput(emptyVector, input, min);
			REQUIRE(emptyVector.empty());
		}
	}
	WHEN("Character and float input")
	{
		THEN("Vector consisted of float values")
		{
			float min;
			std::vector<float> emptyVector, vector = {-1, -0.001, 0, 5.99};
			std::istringstream input("-1 -0.001 0 5.99 ");
			ReadInput(emptyVector, input, min);
			REQUIRE(emptyVector == vector);
		}
	}
}

SCENARIO("Handle vector")
{
	WHEN("Vector consisted of float values")
	{
		THEN("Vector consisted of float values * min")
		{
			float min = 1;
			std::vector<float> vector = { 1, 1.001, 30, 5.99 },
							   resultVector = { 1, 1.001, 30, 5.99 };
			HandleVector(vector, min);
			REQUIRE(vector == resultVector);
		}
	}
	WHEN("Vector consisted of float values")
	{
		THEN("Vector consisted of float values * min")
		{
			float min = -1;
			std::vector<float> vector = { -1, -0.001, 0, 5.99 }, 
				resultVector = { 1, 0.001, 0, -5.99 };
			HandleVector(vector, min);
			REQUIRE(vector == resultVector);
		}
	}
	WHEN("Empty vector")
	{
		THEN("Empty vector")
		{
			float min;
			std::vector<float> emptyVector;
			std::istringstream input("");
			HandleVector(emptyVector, min);
			REQUIRE(emptyVector.empty());
		}
	}
	WHEN("Vector consisted of max and min float values")
	{
		THEN("Vector consisted of max and min float values")
		{
			float min = -FLT_MAX;
			std::vector<float> vector = { -FLT_MAX, FLT_MIN, FLT_MAX },
							   resultVector = { FLT_MAX, -FLT_MAX * FLT_MIN, -FLT_MAX };
			HandleVector(vector, min);
			REQUIRE(vector == resultVector);
		}
	}
}

SCENARIO("Sort in ascending order")
{
	WHEN("Empty vector")
	{
		THEN("Empty vector")
		{
			float min;
			std::vector<float> emptyVector;
			std::istringstream input("");
			SortInAscendingOrder(emptyVector);
			REQUIRE(emptyVector.empty());
		}
	}
	WHEN("Vector consisted of negative, zero and positive values")
	{
		THEN("Vector consisted of negative, zero and positive values in ascending order")
		{
			std::vector<float> vector = { 5.99, 0, -1, FLT_MIN, FLT_MIN, FLT_MAX,
				-FLT_MAX, - 0.001 },
							   resultVector = { -FLT_MAX, - 1, -0.001, 0, FLT_MIN,
				FLT_MIN, 5.99, FLT_MAX };
			SortInAscendingOrder(vector);
			REQUIRE(vector == resultVector);
		}
	}
}

SCENARIO("Print vector")
{
	WHEN("Empty vector")
	{
		THEN("Empty vector")
		{
			float min;
			std::vector<float> emptyVector;
			std::istringstream input("");
			std::ostringstream out;
			PrintVector(emptyVector, out);
			REQUIRE(out.str() == "");
		}
	}
	WHEN("Vector consisted of float values")
	{
		THEN("Vector consisted of float values")
		{
			float min;
			std::vector<float> vector = { -1534.45, 0, 1235.1};
			std::ostringstream out;
			PrintVector(vector, out);
			REQUIRE(out.str() == "-1534.45 0 1235.1 ");
		}
	}
}