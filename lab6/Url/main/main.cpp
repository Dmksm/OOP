
#include "CHttpUrl.h"
#include "CController.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	std::vector<CHttpUrl> urls;

	CController controller(urls, cin, cout);

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