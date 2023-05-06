#pragma once
#include "stdafx.h"

class Calculator;

class CRemoteControl
{
public:
	CRemoteControl(Calculator& calc, std::istream& input, std::ostream& output);
	bool HandleCommand();

private:
	bool Var(std::istream& args);
	bool Let(std::istream& args);
	bool Fn(std::istream& args);
	bool Print(std::istream& args);
	bool PrintVars();
	bool PrintFns();

private:
	using Handler = std::function<bool(std::istream& args)>;

	using ActionMap = std::map<std::string, Handler>;

	Calculator& m_calc;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
};