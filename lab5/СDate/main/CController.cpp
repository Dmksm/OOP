#include "CController.h"
#include "CDate.h"

using namespace std;
using namespace std::placeholders;

CController::CController(CDate& date, std::istream& input, std::ostream& output)
	: m_date(date)
	, m_input(input)
	, m_output(output)
{
}

bool CController::Increment()
{
	try
	{
		++m_date;
	}
	catch (std::invalid_argument const& ex)
	{
		std::cout << "Error! " << ex.what() << std::endl;
	}
	return true;
}

bool CController::Decrement()
{
	try
	{
		--m_date;
	}
	catch (std::invalid_argument const& ex)
	{
		std::cout << "Error! " << ex.what() << std::endl;
	}
	return true;
}

bool CController::Help()
{
	m_output << "info" << std::endl
			 << "help" << std::endl
			 << "readdate" << std::endl
			 << "increment" << std::endl
			 << "decrement" << std::endl;
	return true;
}

bool CController::ReadDate(std::istream& args)
{
	args >> m_date;
	return true;
}

bool CController::Info()
{
	std::cout << "Current date: " << m_date << std::endl;
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