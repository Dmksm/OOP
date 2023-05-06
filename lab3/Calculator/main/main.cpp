#include "CalculatorHandler.h"

#include "CRemoteControl.h"

using namespace std;

int main()
{
	Calculator calculator;
	CRemoteControl remoteControl(calculator, cin, cout);

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