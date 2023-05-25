#include "CController.h"
#include "CDate.h"

using namespace std;

int main()
{
	CDate date;
	CController controller(date, cin, cout);

	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		if (!controller.HandleCommand())
		{
			cout << "Unknown command!" << endl;
		}
	}
	return 0;
}