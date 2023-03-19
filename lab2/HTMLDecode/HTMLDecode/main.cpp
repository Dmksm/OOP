#include "HTMLDecodeHandler.h"

int main()
{
    std::string html;
	while (getline(std::cin, html))
	{
		std::cout << HtmlDecode(html) << std::endl;
	}
    return 0;
}