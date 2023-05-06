﻿#include "CarHandler.h";

#include "CRemoteControl.h";

using namespace std;

int main()
{
	Car car; //Классы первая тоько большая
	CRemoteControl remoteControl(car, cin, cout);

	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		if (!remoteControl.HandleCommand())
		{
			cout << "Unknown command!" << endl;
		}
	}
	return 0;
}