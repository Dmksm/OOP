#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../main/CBody.h"
#include "../main/CCone.h"
#include "../main/CCylinder.h"
#include "../main/CParallelepiped.h"
#include "../main/CSphere.h"

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