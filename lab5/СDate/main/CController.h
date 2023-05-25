#pragma once
#include "stdafx.h"
class CDate;

class CController //название прилдумывать в контексте программы
{
public:
	CController(CDate& m_date, std::istream& input, std::ostream& output);
	bool HandleCommand();
	bool ReadDate(std::istream& args);
	bool Decrement();
	bool Increment();
	bool Help();

private:
	bool Info();

private:
	using Handler = std::function<bool(std::istream& args)>;

	using ActionMap = std::map<std::string, Handler>;

	CDate& m_date;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap{
		{ "info", bind(&CController::Info, this) },
		{ "help", bind(&CController::Help, this) },
		{ "readdate", bind(&CController::ReadDate, this, _1) },
		{ "decrement", bind(&CController::Decrement, this) },
		{ "increment", bind(&CController::Increment, this) }
	};
};