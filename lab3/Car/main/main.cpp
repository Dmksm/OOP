
#include "CarHandler.h";

#include "CRemoteControl.h";

using namespace std;

int main()
{
	CAR car;
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
