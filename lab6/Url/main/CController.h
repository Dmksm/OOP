#pragma once
#include "stdafx.h"

class CHttpUrl;

class CController //здесь можно не делать диалог с пользователем, лучше работу с пользователем под контректуню задачу делать а расширяемость лучше для класса больше уделить ему внимание
{
public:
	CController(std::vector<CHttpUrl> url, std::istream& input, std::ostream& output);
	bool HandleCommand();
	bool Help();
	bool Init();
	bool Info();

private:

private:
	using Handler = std::function<bool(std::istream& args)>;

	using ActionMap = std::map<std::string, Handler>;

	std::vector<CHttpUrl> m_urls;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap = {
		{ "h", std::bind(&CController::Help, this) },
		{ "help", std::bind(&CController::Help, this) },
		{ "info", std::bind(&CController::Info, this) },
		{ "init", std::bind(&CController::Init, this) }
	};
};