#include "CController.h"
#include "CHttpUrl.h"

using namespace std;
using namespace std::placeholders;

CController::CController(CHttpUrl& url, std::istream& input, std::ostream& output)
	: m_url(url)
	, m_input(input)
	, m_output(output)
{
}

bool CController::Help()
{
	m_output << "help	- Help" << std::endl
			 << "1		- Create url" << std::endl
			 << "2		- Info" << std::endl
			 << "3		- Get port" << std::endl;
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

bool CController::GetPort()
{
	std::cout << m_url.GetPort() << std::endl;
	return true;
}

bool CController::Info()
{
	std::cout << m_url.GetURL() << std::endl;
	return true;
}

bool CController::CreateUrl()
{
	std::string domain, document, protocol, port;
	try
	{
		std::cout << "Enter a domain ";
		std::cin >> domain;

		std::cout << "Enter a document ";
		std::cin >> document;

		std::cout << "Enter a protocol or 's' for skip ";
		std::cin >> protocol;

		std::cout << "Enter a port or 's' for skip ";
		std::cin >> port;

		Protocol protocolFormatted = Protocol::HTTP;
		if (protocol == "http")
		{
		}
		else if (protocol == "https")
		{
			protocolFormatted = Protocol::HTTPS;
		}
		else if (protocol != "s")
		{
			throw std::exception("Unexpected protocol");
		}

		if (port == "s")
		{
			m_url = CHttpUrl(domain, document, protocolFormatted);
		}
		else
		{
			unsigned short protocolPort;
			protocolPort = static_cast<unsigned short>(std::strtoul(port.c_str(), NULL, 0));
			m_url = CHttpUrl(domain, document, protocolFormatted, protocolPort);
		}
	}
	catch (...)
	{
		return false;
	}
	return true;
}