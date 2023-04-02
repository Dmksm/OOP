#include "CRemoteControl.h"
#include "CarHandler.h"

using namespace std;
using namespace std::placeholders;

CRemoteControl::CRemoteControl(CAR& car, std::istream& input, std::ostream& output)
	: m_car(car)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		  { "EngineOn", bind(&CRemoteControl::EngineOn, this) },
		  { "EngineOff", bind(&CRemoteControl::EngineOff, this) },
		  { "Info", bind(&CRemoteControl::Info, this) }, 
		  { "SetGear", bind(&CRemoteControl::SetGear, this, _1) }, 
		  { "SetSpeed", bind(&CRemoteControl::SetSpeed, this, _1) }
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

bool CRemoteControl::EngineOn()
{
	m_car.TurnOnEngine();
	m_output << "Car is turned on" << endl;
	return true;
}

bool CRemoteControl::EngineOff()
{
	if (m_car.TurnOffEngine())
	{
		m_output << "Car is turned off" << endl;
	}
	else
	{
		m_output << "Failed! Car is turned on" << endl;
	}
	return true;
}

bool CRemoteControl::Info()
{
	string info = (m_car.IsTurnedOn()) ? "Car is turned on" : "Car is turned off";
	info += ", direction is " + m_car.GetDirection() + ", speed is " + to_string(m_car.GetSpeed());
	info += ", gear is " + to_string(m_car.GetGear());
	m_output << info << endl;

	return true;
}

bool CRemoteControl::SetGear(std::istream& args)
{
	int gear;
	args >> gear;
	(m_car.SetGear(gear)) ? std::cout << "Car set gear to " << to_string(m_car.GetGear()) :
		std::cout << "Car did not set gear to " << to_string(gear);
	std::cout << endl;

	return true;
}

bool CRemoteControl::SetSpeed(std::istream& args)
{
	int speed;
	args >> speed;
	(m_car.SetSpeed(speed)) ? std::cout << "Car set speed to " << to_string(m_car.GetSpeed()) :
		std::cout << "Car did not set speed to " << to_string(speed);
	std::cout << endl;

	return true;
}