#pragma once
#include "stdafx.h"
class CBody;

class CRemoteControl //название прилдумывать в контексте программы
{
public:
	CRemoteControl(std::vector<std::shared_ptr<CBody>>& bodies, std::istream& input, std::ostream& output);
	bool HandleCommand();
	bool Help();

private:
	bool InitBodies();
	bool GetHighestMassBody();
	bool GetLighterBodyInWater();
	bool Info();

private:
	using Handler = std::function<bool(std::istream& args)>;

	using ActionMap = std::map<std::string, Handler>;

	std::vector<std::shared_ptr<CBody>>& m_bodies;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap; // значения по умолчанию инициализировать в заголовке сразу
};