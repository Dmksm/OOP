#pragma once
#include "stdafx.h"

class CHttpUrl;

class CController
{
public:
	CController(CHttpUrl& url, std::istream& input, std::ostream& output);
	bool HandleCommand();
	bool Help();
	bool CreateUrl();
	bool Info();
	bool GetPort();

private:

private:
	using Handler = std::function<bool(std::istream& args)>;

	using ActionMap = std::map<std::string, Handler>;

	CHttpUrl& m_url;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap = {
		{ "help", std::bind(&CController::Help, this) },
		{ "1", std::bind(&CController::CreateUrl, this) },
		{ "2", std::bind(&CController::Info, this) },
		{ "3", std::bind(&CController::GetPort, this) }
	};
};