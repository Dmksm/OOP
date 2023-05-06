#include "CRemoteControl.h"
#include "CalculatorHandler.h"

using namespace std;
using namespace std::placeholders;

Calculator::Operation StringToEnum(const std::string& str)
{
	static const std::map<std::string, Calculator::Operation> enum_map = {
		{ "+", Calculator::Operation::Sum },
		{ "-", Calculator::Operation::Sub },
		{ "/", Calculator::Operation::Div },
		{ "*", Calculator::Operation::Mult },
	};
	auto it = enum_map.find(str);
	return it->second;
}

bool isValidIdentifier(std::string identifier)
{
	std::regex pattern("^[a-zA-Z_][a-zA-Z0-9_]*$");
	if (identifier.find(" ") != std::string::npos)
	{
		return false;
	}
	return std::regex_match(identifier, pattern);
}

CRemoteControl::CRemoteControl(Calculator& calc, std::istream& input, std::ostream& output)
	: m_calc(calc)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		  { "var", bind(&CRemoteControl::Var, this, _1) },
		  { "let", bind(&CRemoteControl::Let, this, _1) },
		  { "printfns", bind(&CRemoteControl::PrintFns, this) }, 
		  { "printvars", bind(&CRemoteControl::PrintVars, this) }, 
		  { "fn", bind(&CRemoteControl::Fn, this, _1) },
		  { "print", bind(&CRemoteControl::Print, this, _1) },
	  })
{
}

bool CRemoteControl::HandleCommand()
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

bool CRemoteControl::PrintFns()
{
	for (auto it : m_calc.GetFns())
	{
		std::cout << it.first << " : ";
		std::optional<double> val = m_calc.GetFn(it.first);
		if (val.has_value())
		{
			std::cout << std::setprecision(2) << fixed << val.value();
		}
		else
		{
			std::cout << std::nan("1");
		}
		std::cout << std::endl;
	}
	return true;
}

bool CRemoteControl::PrintVars()
{
	for (auto it : m_calc.GetVars())
	{
		std::cout << it.first << " : " << std::setprecision(2) << fixed << it.second << std::endl;
	}
	return true;
}

bool CRemoteControl::Var(std::istream& args)
{
	std::string name;
	args >> name;
	if (!isValidIdentifier(name))
	{
		std::cout << " Invalid identifier \"" << name << "\"" << std::endl;
		return true;
	}

	m_calc.Var(name);
	return true;
}

bool CRemoteControl::Let(std::istream& args)
{
	std::string name, val;
	getline(args, name, '=');
	name = name.substr(1);

	if (!isValidIdentifier(name))
	{
		std::cout << " Invalid identifier \"" << name << "\"" << std::endl;
		return true;
	}
	args >> val;
	try 
	{
		double d = std::stod(val);
		m_calc.Let(name, round(d * 100) / 100);
	}
	catch (exception e)
	{
		if (isValidIdentifier(val))
		{
			m_calc.Let(name, val);
		}
		else
		{
			std::cout << "Invalid identifier \"" << val << "\"" << std::endl;
		}
	}
	
	return true;
}

bool CRemoteControl::Fn(std::istream& args)
{
	std::string fnName, operand1, operand2, operation;
	getline(args, fnName, '=');
	fnName = fnName.substr(1);

	args >> operand1;
	if (isValidIdentifier(operand1))
	{
		m_calc.Fn(fnName, operand1);
		return true;
	}

	size_t pos = operand1.find("+");
	if (pos == std::string::npos)
	{
		pos = operand1.find("-");
		if (pos == std::string::npos)
		{
			pos = operand1.find("/");
			if (pos == std::string::npos)
			{
				pos = operand1.find("*");
				if (pos == std::string::npos)
				{
					std::cout << "Invalid identifier \"" << operand1 << "\"" << std::endl;
					return true;
				}
			}
		}
	}
	
	operation = operand1.substr(pos, 1);
	operand2 = operand1.substr(pos + 1);
	operand1 = operand1.substr(0, pos);
	m_calc.Fn(fnName, operand1, StringToEnum(operation), operand2);
	
	return true;
}

bool CRemoteControl::Print(std::istream& args)
{
	std::string name;
	args >> name;
	if (m_calc.GetVar(name).has_value())
	{
		std::cout << m_calc.GetVar(name).value() << std::endl;
	}
	else if (m_calc.GetFn(name).has_value())
	{
		std::cout << m_calc.GetFn(name).value() << std::endl;
	}
	else
	{
		std::cout << "Undefined name \"" << name << "\"" << std::endl;
	}

	return true;
}