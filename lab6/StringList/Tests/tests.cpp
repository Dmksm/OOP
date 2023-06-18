#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../main/CStringList.h"

SCENARIO("Constructing string lists")
{
	GIVEN("Basic string lists and string")
	{
		CStringList list1, list2, list3;
		std::string s;
		WHEN("Copy and move lists")
		{
			THEN("New list with data first list and move data to new list")
			{
				REQUIRE(list1.GetSize() == 0);
				REQUIRE_THROWS_AS(list1.GetBackElement(), std::logic_error);

				list2.Append("a");
				list2.Append("b");
				REQUIRE(list2.GetSize() == 2);
				REQUIRE(list2.GetBackElement() == "b");

				list1 = list2;
				REQUIRE(list1.GetSize() == 2);
				REQUIRE(list1.GetBackElement() == "b");

				++list1.begin() = "c";
				REQUIRE(list1.GetBackElement() == "c");
				REQUIRE(list2.GetBackElement() == "b");

				list3 = std::move(list2);
				REQUIRE(list3.GetSize() == 2);
				REQUIRE(list3.GetBackElement() == "b");

				REQUIRE(list2.GetSize() == 0);
				REQUIRE_THROWS_AS(list2.GetBackElement(), std::logic_error);
			}
		}

		WHEN("Add data to start of list and end of list")
		{
			THEN("New data in end of list or start of list")
			{
				REQUIRE(list1.IsEmpty());
				list1.Prepend("Furia");
				REQUIRE(!list1.IsEmpty());
				REQUIRE(list1.GetSize() == 1);
				REQUIRE(list1.GetBackElement() == "Furia");
				list1.Prepend("Oreal");
				REQUIRE(list1.GetSize() == 2);
				REQUIRE(list1.GetBackElement() == "Furia");
			}
		}

		WHEN("Checking count elements")
		{
			THEN("Get count elements")
			{
				list1.Append("A");
				REQUIRE(list1.GetSize() == 1);
				REQUIRE(list1.GetBackElement() == "A");
				list1.Clear();
				REQUIRE(list1.GetSize() == 0);
				REQUIRE_THROWS_AS(list1.GetBackElement(), std::logic_error);
			}
		}

		WHEN("Use iterators and range-based for algorithm")
		{
			THEN("Noramal work with iterators")
			{
				list1.Append("free");
				list1.Append("mock");
				REQUIRE(*list1.begin() == "free");
				REQUIRE(*++list1.begin() == "mock");
				REQUIRE(++ ++list1.begin() == list1.end());

				for (std::string elem : list1)
				{
					s += elem;
				}
				REQUIRE(s == "freemock");
				

				list1.begin() = "lyambda";
				++list1.begin() = "maxima";
				s.clear();
				for (std::string elem : list1)
				{
					s += elem;
				}
				REQUIRE(s == "lyambdamaxima");
			}
		}
		WHEN("Erase element")
		{
			THEN("List without deleted element")
			{
				list2.Append("Lom");
				list2.Append("RGB");
				list2.Append("Si");
				REQUIRE(list2.Erase(++ ++list2.begin()) == list2.end());
				REQUIRE(list2.GetSize() == 2);
				REQUIRE(*++list2.begin() == "RGB");
				REQUIRE(++++list2.begin() == list2.end());
				list2.Append("Do");
				list2.Append("Mi");
				list2.Erase(++ ++list2.begin());
				for (std::string elem : list2)
				{
					s += elem;
				}
				REQUIRE(s == "LomRGBMi");

				list1.Append("Baga");
				list1.Append("Yaga");
				list1.Erase(list1.begin());
				REQUIRE(list1.GetSize() == 1);
				REQUIRE(++list1.begin() == list1.end());

				s.clear();
				for (std::string elem : list1)
				{
					s += elem;
				}
				REQUIRE(s == "Yaga");
			}
		}

		WHEN("Insert element")
		{
			THEN("List with new element")
			{
				list1.Insert(list1.cbegin(), "Cool");
				REQUIRE(*list1.begin() == "Cool");
				REQUIRE(++list1.begin() == list1.end());
				REQUIRE(list1.GetSize() == 1);
				list1.Insert(list1.cend(), "Freedom");

				list1.Insert(list1.cend(), "Hotel");
				REQUIRE(*list1.Insert(++list1.cbegin(), "Busy") == "Busy");
				for (std::string elem : list1)
				{
					s += elem;
				}
				REQUIRE(s == "CoolBusyFreedomHotel");
			}
		}
		WHEN("Use reverse iterators and range-based for algorithm")
		{
			THEN("Noramal work with reverse iterators")
			{
				list1.Append("Fargo");
				list1.Append("Madam");
				list1.Append("Bravo");
				for (auto it = list1.rbegin(); it != list1.rend(); ++it)
				{
					s += *it;
				}
				REQUIRE(s == "BravoMadamFargo");
			}
		}
	}
}