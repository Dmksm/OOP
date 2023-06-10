#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../main/CMyArray.h"

SCENARIO("Entering url")
{
	GIVEN("Basic arrays")
	{
		CMyArray<int> intArr;
		CMyArray<float> floatArr;
		CMyArray<bool> boolArr;
		CMyArray<CMyArray<int>> intArrList;
		CMyArray<char> chArr;
		CMyArray<std::string> stringArr;

		
		REQUIRE(intArrList.GetSize() == 0);
		REQUIRE(intArrList.GetCapacity() == 0);
		intArr.Append(999);
		floatArr.Append(0.0001f);
		boolArr.Append(true);
		intArrList.Append(intArr);
		char ch = 'L';
		chArr.Append(ch);
		std::string msg = "My array is the best!";
		stringArr.Append(msg);

		WHEN("Push back element")
		{
			intArr.Append(1);
			floatArr.Append(9.872f);
			boolArr.Append(false);
			intArrList.Append(intArr);
			chArr.Append('H');
			stringArr.Append("Yokusume :)");

			REQUIRE(intArrList.GetCapacity() == 2);
			REQUIRE(intArrList.GetBack().GetCapacity() == 2);
			REQUIRE(intArrList.GetSize() == 2);
			REQUIRE(intArrList.GetBack().GetSize() == 2);

			THEN("Array with new back element")
			{
				REQUIRE(intArr.GetBack() == 1);
				REQUIRE(floatArr.GetBack() == 9.872f);
				REQUIRE(boolArr.GetBack() == false);
				REQUIRE(intArrList.GetBack().GetBack() == 1);
				REQUIRE(chArr.GetBack() == 'H');
				REQUIRE(stringArr.GetBack() == "Yokusume :)");
			}
		}

		WHEN("Get element by index")
		{
			THEN("Return element on position = index")
			{
				REQUIRE(intArr[0] == 999);
				REQUIRE_THROWS_AS(intArrList[1], std::out_of_range);
				intArr.Append(5);
				REQUIRE(intArr[0] == 999);
				REQUIRE(intArr[1] == 5);
			}
		}

		WHEN("Resize array")
		{
			THEN("Get array with new size")
			{
				intArr.Append(2);
				REQUIRE(intArr[1] == 2);
				intArr.Resize(7);

				REQUIRE(intArr[1] == 2);
				REQUIRE(intArr[2] == 0);
				REQUIRE(intArr[6] == 0);
				REQUIRE_THROWS_AS(intArr[7], std::out_of_range);

				intArr.Resize(3);
				REQUIRE(intArr.GetSize() == 3);
				REQUIRE(intArr[2] == 0);
				REQUIRE_THROWS_AS(intArr[3], std::out_of_range);

				intArr.Resize(0);
				REQUIRE(intArr.GetSize() == 0);
				REQUIRE_THROWS_AS(intArr[0], std::out_of_range);
			}
		}

		WHEN("Constucting array")
		{
			THEN("Get new array")
			{
				CMyArray<int> intArr2(intArr), intArr3, intArr4;
				REQUIRE(intArr.GetSize() == intArr2.GetSize());
				REQUIRE(intArr[0] == intArr2[0]);

				intArr3.Append(45);
				intArr2 = intArr3;
				REQUIRE(intArr3.GetSize() == intArr2.GetSize());
				REQUIRE(intArr3[0] == intArr2[0]);
				REQUIRE(intArr3[0] == 45);

				intArr4 = std::move(intArr2);
				REQUIRE(intArr4.GetBack() == 45);
			}
		}

		WHEN("Work with iterators")
		{
			THEN("Normal working array iterators")
			{
				CMyArray<float> myIntArr;

				myIntArr.Append(0.2f);
				myIntArr.Append(3.45f);
				REQUIRE(*(myIntArr.begin()) == 0.2f);
				REQUIRE(*(myIntArr.begin() + 1) == 3.45f);
			}
		}
	}
}