#include "CalculatorHandler.h"

constexpr double max = std::numeric_limits<double>::max(), 
	negativeMax = -std::numeric_limits<double>::max(), 
	min = std::numeric_limits<double>::min();

bool IsOppositeSigns(double a, double b)
{
	return (a < 0 && b > 0) || (a > 0 && b < 0);
}

double Sum(double a, double b)
{
	if (b < 0)
	{
		if (a < negativeMax - b)
		{
			return negativeMax;
		}
	}
	else
	{
		if (a > max - b)
		{
			return max;
		}
	}
	
	return a + b;
}

double Sub(double a, double b)
{
	if (b < 0)
	{
		if (a > max + b)
		{
			return max;
		}
	}
	else
	{
		if (a < negativeMax + b)
		{
			return negativeMax;
		}
	}

	return a - b;
}

double Mult(double a, double b)
{
	if (b < 1)
	{
		if (std::abs(a) < min / std::abs(b))
		{
			if (IsOppositeSigns(a, b))
			{
				return -min;
			}
			return min;
		}
	}
	else
	{
		if (std::abs(a) > max / std::abs(b))
		{
			if (IsOppositeSigns(a, b))
			{
				return -max;
			}
			return max;
		}
	}

	return a * b;
}

double Div(double a, double b)
{
	if (b == 0)
	{
		std::cout << "Cannot divide by zero." << std::endl;
		return std::nan("1");
	}
	if (b < 1)
	{
		if (std::abs(a) > max * std::abs(b))
		{
			if (IsOppositeSigns(a, b))
			{
				return -max;
			}
			return max;
		}
	}
	else
	{
		if (std::abs(a) < min * std::abs(b))
		{
			if (IsOppositeSigns(a, b))
			{
				return -min;
			}
			return min;
		}
	}
	
	return a / b;
}

void Calculator::Var(const std::string& name)
{
	if ((m_vars.find(name) != m_vars.end()) || (m_fns.find(name) != m_fns.end()))
	{
		std::cout << "name " << name << " is already exist " << std::endl;
		return;
	}
	m_vars[name] = std::nan("1");
}

void Calculator::Let(const std::string& name, double val)
{
	m_vars[name] = val;
}

void Calculator::Let(const std::string& name, const std::string& declaredName)
{
	std::optional<double> result = GetIdentifierValue(declaredName);
	(result.has_value()) ? m_vars[name] = result.value() : m_vars[name] = std::nan("1");
}

void Calculator::Fn(const std::string& name, const std::string& declaredName)
{
	if ((m_vars.find(name) != m_vars.end()) || (m_fns.find(name) != m_fns.end()))
	{
		std::cout << "name " << name << " is already exist" << std::endl;
		return;
	}
	if ((m_vars.find(declaredName) == m_vars.end()) && (m_fns.find(declaredName) == m_fns.end()))
	{
		std::cout << "name " << declaredName << " is not exist " << std::endl;
		return;
	}

	m_fns[name] = { declaredName, std::nullopt, std::nullopt };
}

void Calculator::Fn(const std::string& fnName, const std::string& firstName,
	Operation operation, const std::string& secondName)
{
	if ((m_vars.find(firstName) == m_vars.end()) && (m_fns.find(firstName) == m_fns.end()))
	{
		std::cout << "name " << firstName << " is not exist " << std::endl;
		return;
	}
	if ((m_vars.find(secondName) == m_vars.end()) && (m_fns.find(secondName) == m_fns.end()))
	{
		std::cout << "name " << secondName << " is not exist " << std::endl;
		return;
	}
	if ((m_vars.find(fnName) != m_vars.end()) || (m_fns.find(fnName) != m_fns.end()))
	{
		std::cout << "name " << fnName << " is already exist" << std::endl;
		return;
	}

	m_fns[fnName] = { firstName, operation, secondName };
}

std::optional<double> Calculator::GetVar(const std::string& name) const
{
	auto it = m_vars.find(name);
	if (it == m_vars.end())
	{
		return std::nullopt;
	}
	return m_vars.at(name);
}

std::optional<double> Calculator::GetFn(const std::string& name) const
{
	auto it = m_fns.find(name);
	if (it == m_fns.end())
	{
		return std::nullopt;
	}

	std::optional<double> fnResult = std::nan("1");
	if (std::get<1>(it->second).has_value() && std::get<2>(it->second).has_value())
	{
		std::optional<double> firstOperand = GetVar(std::get<0>(it->second));
		std::optional<double> secondOperand = GetVar(std::get<2>(it->second).value());
		if (!firstOperand.has_value())
		{
			firstOperand = GetFn(std::get<0>(it->second));
		}
		if (!secondOperand.has_value())
		{
			secondOperand = GetFn(std::get<2>(it->second).value());
		}

		Operation operation = std::get<1>(it->second).value();
		switch (operation)
		{
			case Operation::Sum:
				fnResult = Sum(firstOperand.value(), secondOperand.value());
				break;
			case Operation::Sub:
				fnResult = Sub(firstOperand.value(), secondOperand.value());
				break;
			case Operation::Div:
				fnResult = Div(firstOperand.value(), secondOperand.value());
				break;
			case Operation::Mult:
				fnResult = Mult(firstOperand.value(), secondOperand.value());
		}
	}
	else
	{
		std::string identifierName = std::get<0>(it->second);
		fnResult = GetIdentifierValue(identifierName);
	}

	return fnResult;
}

std::unordered_map<std::string, double> Calculator::GetVars() const 
{
	return m_vars;
}

Calculator::FunctionCache Calculator::GetFns() const
{
	return m_fns;
}

std::optional<double> Calculator::GetIdentifierValue(std::string identifierName) const
{
	std::optional<double> result;
	result = GetVar(identifierName);
	if (!result.has_value())
	{
		result = GetFn(identifierName);
	}
	return result;
}