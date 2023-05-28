#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../main/CDate.h"

SCENARIO("Init Date")
{
	WHEN("Init Date")
	{
		THEN("available date methods")
		{
			CDate date;
			REQUIRE(typeid(date.GetDay()) == typeid(unsigned));
			REQUIRE(typeid(date.GetMonth()) == typeid(Month));
			REQUIRE(typeid(date.GetWeekDay()) == typeid(WeekDay));
			REQUIRE(typeid(date.GetYear()) == typeid(unsigned));

			REQUIRE(date.GetDay() == 1);
			REQUIRE(date.GetMonth() == Month::JANUARY);
			REQUIRE(date.GetWeekDay() == WeekDay::THURSDAY);
			REQUIRE(date.GetYear() == 1970);

			CDate date2(29, Month::FEBRUARY, 1972);
			REQUIRE(typeid(date2.GetDay()) == typeid(unsigned));
			REQUIRE(typeid(date2.GetMonth()) == typeid(Month));
			REQUIRE(typeid(date2.GetWeekDay()) == typeid(WeekDay));
			REQUIRE(typeid(date2.GetYear()) == typeid(unsigned));

			REQUIRE(date2.GetDay() == 29);
			REQUIRE(date2.GetMonth() == Month::FEBRUARY);
			REQUIRE(date2.GetWeekDay() == WeekDay::TUESDAY);
			REQUIRE(date2.GetYear() == 1972);

			CDate date3(31, Month::DECEMBER, 9999);
			REQUIRE(typeid(date3.GetDay()) == typeid(unsigned));
			REQUIRE(typeid(date3.GetMonth()) == typeid(Month));
			REQUIRE(typeid(date3.GetWeekDay()) == typeid(WeekDay));
			REQUIRE(typeid(date3.GetYear()) == typeid(unsigned));

			REQUIRE(date3.GetDay() == 31);
			REQUIRE(date3.GetMonth() == Month::DECEMBER);
			REQUIRE(date3.GetWeekDay() == WeekDay::FRIDAY);
			REQUIRE(date3.GetYear() == 9999);
		}
	}
}

SCENARIO("Changing Date")
{
	WHEN("Trying change date on date before 1 Junuary 1970")
	{
		CDate date;
		THEN("Get exception")
		{
			REQUIRE_THROWS_AS(date - 1, std::invalid_argument);
			REQUIRE_THROWS_AS(date + -1, std::invalid_argument);
			REQUIRE_THROWS_AS(date += -1, std::invalid_argument);
			REQUIRE_THROWS_AS(date -= 1, std::invalid_argument);
			REQUIRE_THROWS_AS(--date, std::invalid_argument);
			REQUIRE_THROWS_AS(date--, std::invalid_argument);
		}
	}
	WHEN("Trying change date on date after 31 December 9999")
	{
		CDate date(31, Month::DECEMBER, 9999);
		THEN("Get exception")
		{
			REQUIRE_THROWS_AS(date - -1, std::invalid_argument);
			REQUIRE_THROWS_AS(date + 1, std::invalid_argument);
			REQUIRE_THROWS_AS(date += 1, std::invalid_argument);
			REQUIRE_THROWS_AS(date -= -1, std::invalid_argument);
			REQUIRE_THROWS_AS(++date, std::invalid_argument);
			REQUIRE_THROWS_AS(date++, std::invalid_argument);
		}
	}
}

SCENARIO("Changing leap date")
{
	GIVEN("leap day and the coming days")
	{
		CDate leapDate(29, Month::FEBRUARY, 1972), 
			dateAfterLeapDay(1, Month::MARCH, 1972),
			dateBeforeLeapDay(28, Month::FEBRUARY, 1972);

		WHEN("Trying to change the date and get value")
		{
			THEN("If prefix operation then get new value else old value")
			{
				unsigned dayPlus1 = (++dateAfterLeapDay).GetDay();
				REQUIRE(dateAfterLeapDay.GetDay() == 2);
				REQUIRE(dayPlus1 == 2);

				unsigned oldDay = (dateAfterLeapDay++).GetDay();
				REQUIRE(dateAfterLeapDay.GetDay() == 3);
				REQUIRE(oldDay == 2);
			}
		}

		WHEN("Trying to change the date from a leap day to a leap day")
		{
			THEN("Get new date")
			{
				CDate date = leapDate;
				date++;
				REQUIRE((date == dateAfterLeapDay));

				date--;
				REQUIRE((date == leapDate));

				date--;
				REQUIRE((date == dateBeforeLeapDay));

				date++;
				REQUIRE((date == leapDate));
			}
		}
	}
}

SCENARIO("Printing and entering date")
{
	GIVEN("input and output stream")
	{
		std::stringstream stream;
		WHEN("Trying to change the date and get value")
		{
			THEN("If prefix operation then get new value else old value")
			{
				CDate date;
				stream << "29.2.1972";
				stream >> date;

				date += 2;

				stream.str("");
				stream.clear();

				stream << date;
				REQUIRE(stream.str() == "2.3.1972");
			}
		}
	}
}

SCENARIO("Comparing date")
{
	WHEN("Comparing leap date")
	{
		CDate leapDate(29, Month::FEBRUARY, 1972), leapDate2(29, Month::FEBRUARY, 1972);
		THEN("Get right comparing result")
		{
			REQUIRE(leapDate == leapDate2);
			REQUIRE(!(leapDate > leapDate2));
			REQUIRE(leapDate >= leapDate2);
			REQUIRE(leapDate <= leapDate2);
			REQUIRE(!(leapDate > leapDate2));
			REQUIRE(!(leapDate < leapDate2));

			leapDate2++;
			REQUIRE(!(leapDate == leapDate2));
			REQUIRE(leapDate != leapDate2);
			REQUIRE(!(leapDate >= leapDate2));
			REQUIRE(leapDate <= leapDate2);
			REQUIRE(!(leapDate > leapDate2));
			REQUIRE(leapDate < leapDate2);
		}
	}

	WHEN("Comparing date with last day of year")
	{
		CDate lastDayOfYear(31, Month::DECEMBER, 1972), firstDayOfNextYear(1, Month::JANUARY, 1973);
		THEN("Get right comparing result")
		{
			REQUIRE(!(lastDayOfYear == firstDayOfNextYear));
			REQUIRE(lastDayOfYear < firstDayOfNextYear);
			REQUIRE(!(lastDayOfYear >= firstDayOfNextYear));
			REQUIRE(lastDayOfYear <= firstDayOfNextYear);
			REQUIRE(!(lastDayOfYear > firstDayOfNextYear));
			REQUIRE(lastDayOfYear < firstDayOfNextYear);
		}
	}
}