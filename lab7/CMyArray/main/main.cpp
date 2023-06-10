#include "../main/CMyArray.h"
int main()
{
	CMyArray<int> intArr;
	CMyArray<float> floatArr;
	CMyArray<bool> boolArr;
	CMyArray<char> chArr;
	CMyArray<std::string> stringArr;

	intArr.Append(999);
	intArr.Resize(10, 11);
	std::cout << "intArr.GetSize() " << intArr.GetSize();
	intArr.Resize(3);
	std::cout << "intArr.GetSize() " << intArr.GetSize();
	intArr.Append(999);
	CMyArray<int> intArr2(intArr), intArr3;
	intArr3.Append(1);
	intArr3 = std::move(intArr2);
	std::cout << " intArr3.GetSize() " << intArr3.GetSize() << std::endl;

	CMyArray<float> myIntArr;
	myIntArr.Append(3.72f);
	std::cout << *myIntArr.begin() << " " << *myIntArr.end() << std::endl;
	myIntArr.Append(27.24f);
	std::cout << *(myIntArr.begin() + 1) << " " << *myIntArr.end() << std::endl;

	return 0;
}