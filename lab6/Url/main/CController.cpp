#include "CController.h"
#include "CHttpUrl.h"
#include "CUrlParsingError.h"

using namespace std;
using namespace std::placeholders;

CController::CController(std::vector<CHttpUrl> urls, std::istream& input, std::ostream& output)
	: m_urls(urls)
	, m_input(input)
	, m_output(output)
{
}

bool CController::Help()
{
	m_output << "help" << std::endl
			 << "info" << std::endl
			 << "init" << std::endl;
	return true;
}

bool CController::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}

	return false;
}

bool CController::Info()
{
	for (CHttpUrl url : m_urls)
	{
		try
		{
			std::string protocol = (url.GetProtocol() == Protocol::HTTP) ? "http" : "https";
			std::cout << "url: " << url.GetUrl() << std::endl
					  << "protocol: " << protocol << std::endl
					  << "domain: " << url.GetDomain() << std::endl
					  << "port: " << url.GetPort() << std::endl
					  << "document: " << url.GetDocument() << std::endl
					  << std::endl;
		}
		catch (CUrlParsingError e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	return true;
}

bool CController::Init()
{
	std::string httpUrl;
	std::cout << "Чтобы завершить введите 'stop'" << std::endl;
	while ((std::cin >> httpUrl) && (httpUrl != "stop"))
	{
		try
		{
			CHttpUrl url(httpUrl);
			m_urls.push_back(url);
		}
		catch (CUrlParsingError e)
		{
			std::cout << e.what() << std::endl;
			return false;
		}
	}
	return true;
}