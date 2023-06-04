#include "CHttpUrl.h"
#include "CController.h"

using namespace std;

int main()
{
	CHttpUrl url("http://ya.ru:80/target.jpeg");
	CController controller(url, cin, cout);

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