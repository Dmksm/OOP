#include "CRemoteControl.h"

using namespace std;

struct Convert
{
	unsigned char operator()(unsigned char const& c)
	{
		return tolower(c);
	}
};

int main()
{
	vector<shared_ptr<CBody>> bodies;
	CRemoteControl remoteControl(bodies, cin, cout);

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