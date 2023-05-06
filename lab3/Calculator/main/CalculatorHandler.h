#pragma once
#include "stdafx.h"

class Calculator 
{
public:
	enum class Operation : char
	{
		Sum = '+',
		Sub = '-',
		Mult = '*',
		Div = '/',
	};
	using FunctionCache = std::unordered_map<std::string,
		std::tuple<std::string, std::optional<Operation>, std::optional<std::string>>>;

	void Var(const std::string& name);
	void Let(const std::string& name, double val);
	void Let(const std::string& name, const std::string& declaredName);
	void Fn(const std::string& name, const std::string& declaredName);
	void Fn(const std::string& fnName, const std::string& firstName,
		Operation operation, const std::string& secondName);
	std::optional<double> GetVar(const std::string& name) const;
	std::optional<double> GetFn(const std::string& name) const;
	bool IsVarExist(const std::string& name) const;
	std::unordered_map<std::string, double> GetVars() const;
	bool IsFnExist(const std::string& name) const;
	FunctionCache GetFns() const;

private:
	std::optional<double> GetIdentifierValue(std::string identifierName) const;
	std::unordered_map<std::string, double> m_vars;
	FunctionCache m_fns;
};