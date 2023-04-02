#pragma once
#include "stdafx.h"

class CAR;

class CRemoteControl
{
public:
	CRemoteControl(CAR& car, std::istream& input, std::ostream& output);
	bool HandleCommand();

private:
	bool EngineOn();
	bool EngineOff();
	bool Info();
	bool SetGear(std::istream& args);
	bool SetSpeed(std::istream& args);

private:
	using Handler = std::function<bool(std::istream& args)>;

	using ActionMap = std::map<std::string, Handler>;

	CAR& m_car;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
};