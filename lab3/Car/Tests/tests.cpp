#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../main/CarHandler.h"

SCENARIO("Car is off")
{	
	WHEN("Start work with car")
	{
		THEN("Car is off on start and can turn on")
		{
			CAR car;
			REQUIRE(car.IsTurnedOn() == false);
			REQUIRE(car.GetDirection() == "standing still");
			REQUIRE(car.GetSpeed() == 0);
			REQUIRE(car.GetGear() == 0);
			car.TurnOnEngine();
			REQUIRE(car.IsTurnedOn() == true);
			REQUIRE(car.GetDirection() == "standing still");
			REQUIRE(car.GetSpeed() == 0);
			REQUIRE(car.GetGear() == 0);
		}
	}
	WHEN("Start work with car that turned Off")
	{
		THEN("Car is off")
		{
			CAR car;
			car.SetGear(3);
			car.SetSpeed(14);
			REQUIRE(car.IsTurnedOn() == false);
			REQUIRE(car.GetDirection() == "standing still");
			REQUIRE(car.GetSpeed() == 0);
			REQUIRE(car.GetGear() == 0);
		}
	}
	WHEN("Set anavailabe gear for different speed")
	{
		THEN("Car dont change gear")
		{
			CAR car;

			car.SetGear(-1);
			REQUIRE(car.GetGear() == 0);
			car.SetGear(0);
			REQUIRE(car.GetGear() == 0);
			car.SetGear(1);
			REQUIRE(car.GetGear() == 0);
			car.SetGear(2);
			REQUIRE(car.GetGear() == 0);
			car.SetGear(3);
			REQUIRE(car.GetGear() == 0);
			car.SetGear(4);
			REQUIRE(car.GetGear() == 0);
			car.SetGear(5);
			REQUIRE(car.GetGear() == 0);
		}
	}
}

SCENARIO("Car is on")
{
	WHEN("Set speed out of range for different gear")
	{
		THEN("Failed set")
		{
			CAR car;
			car.TurnOnEngine();

			car.SetSpeed(-1);
			REQUIRE(car.GetSpeed() == 0);

			car.SetGear(-1);

			car.SetSpeed(-1);
			REQUIRE(car.GetSpeed() == 0);
			car.SetSpeed(21);
			REQUIRE(car.GetSpeed() == 0);

			car.SetGear(1);

			car.SetSpeed(-1);
			REQUIRE(car.GetSpeed() == 0);
			car.SetSpeed(31);
			REQUIRE(car.GetSpeed() == 0);

			car.SetSpeed(20);
			car.SetGear(2);

			car.SetSpeed(19);
			REQUIRE(car.GetSpeed() == 20);
			car.SetSpeed(51);
			REQUIRE(car.GetSpeed() == 20);

			car.SetSpeed(30);
			car.SetGear(3);

			car.SetSpeed(29);
			REQUIRE(car.GetSpeed() == 30);
			car.SetSpeed(61);
			REQUIRE(car.GetSpeed() == 30);

			car.SetSpeed(60);
			car.SetGear(4);

			car.SetSpeed(39);
			REQUIRE(car.GetSpeed() == 60);
			car.SetSpeed(91);
			REQUIRE(car.GetSpeed() == 60);

			car.SetGear(5);

			car.SetSpeed(49);
			REQUIRE(car.GetSpeed() == 60);
			car.SetSpeed(151);
			REQUIRE(car.GetSpeed() == 60);
		}
	}
	WHEN("Set anavailabe gear for different speed")
	{
		THEN("Car dont change gear")
		{
			CAR car;
			car.TurnOnEngine();

			REQUIRE(car.GetGear() == 0);

			car.SetGear(1);
			REQUIRE(car.GetGear() == 1);

			car.SetSpeed(21);
			car.SetGear(0);
			REQUIRE(car.GetGear() == 0);

			REQUIRE(car.SetSpeed(21) == false);

			car.SetSpeed(20);
			REQUIRE(car.GetSpeed() == 20);
		}
	}
}