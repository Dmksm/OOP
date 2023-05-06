#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../main/CalculatorHandler.h"

SCENARIO("Work of standard operations")
{
	Calculator calc;
	WHEN("First initialize")
	{
		REQUIRE(!calc.GetVar("a").has_value());
		REQUIRE(!calc.GetVar("b").has_value());
		calc.Var("a");
		calc.Var("b");
		THEN("val is NAN")
		{
			REQUIRE(std::isnan(calc.GetVar("a").value()));
			REQUIRE(std::isnan(calc.GetVar("b").value()));
		}
	}
	WHEN("Boundary values at the input") 
	{
		calc.Let("a", 4);
		calc.Let("b", "a");
		constexpr double max = std::numeric_limits<double>::max(), 
			min = std::numeric_limits<double>::min(), 
			negativeMax = -std::numeric_limits<double>::max();
		THEN("Сalculations do not go beyond the boundary values")
		{
			REQUIRE(calc.GetVar("a").value() == 4);
			REQUIRE(calc.GetVar("b").value() == 4);
			calc.Let("max", max);
			calc.Let("min", min);
			calc.Let("negative_max", negativeMax);

			REQUIRE(std::isnan(Div(calc.GetVar("max").value(), 0)));

			REQUIRE(Sub(calc.GetVar("negative_max").value(), max) == negativeMax);
			REQUIRE(Sub(calc.GetVar("max").value(), negativeMax) == max);

			REQUIRE(Sum(calc.GetVar("max").value(), max) == max);
			REQUIRE(Sum(calc.GetVar("negative_max").value(), negativeMax) == negativeMax);

			REQUIRE(Div(calc.GetVar("min").value(), max) == min);
			REQUIRE(Div(calc.GetVar("max").value(), -min) == -max);

			REQUIRE(Mult(calc.GetVar("min").value(), min) == min);
			REQUIRE(Mult(calc.GetVar("max").value(), max) == max);
		}
	}

	WHEN("Basic initialize operations")
	{
		calc.Var("a");
		calc.Let("b", 4);
		calc.Let("c", 5);
		calc.Fn("valA", "a");
		calc.Fn("sum", "c", Operation::Sum, "b");
		THEN("normal work with vars and functions")
		{
			REQUIRE(std::isnan(calc.GetFn("valA").value()));
			REQUIRE(calc.GetFn("sum").value() == 9);
		}
	}
	//проверка функции на изменение динамически
}