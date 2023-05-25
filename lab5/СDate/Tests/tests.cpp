#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

SCENARIO("Entering compound body")
{
	WHEN("Enter one nesting compound body")
	{
		THEN("Car is off on start and can turn on")
		{
		}
	}
	WHEN("Enter double nesting compound body")
	{
		THEN("Car is off on start and can turn on")
		{
		}
	}
}