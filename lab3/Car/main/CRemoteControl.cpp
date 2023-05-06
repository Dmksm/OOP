#include "CRemoteControl.h"
#include "CarHandler.h" // forward definition посмотреть 

using namespace std;
using namespace std::placeholders;

CRemoteControl::CRemoteControl(Car& car, std::istream& input, std::ostream& output)
	: m_car(car)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		  { "engineon", bind(&CRemoteControl::EngineOn, this) },
		  { "engineOff", bind(&CRemoteControl::EngineOff, this) },
		  { "info", bind(&CRemoteControl::Info, this) }, 
		  { "setgear", bind(&CRemoteControl::SetGear, this, _1) }, 
		  { "setspeed", bind(&CRemoteControl::SetSpeed, this, _1) }
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
	std::string arg;
	args >> arg;
	int gear;
	try
	{
		gear = std::stoi(arg);
	}
	catch (exception e)
	{
		std::cout << "Unexpected argument " << arg << std::endl;
		return false;
	} // подогнать под 20 стандарт для использования современных функций
	(m_car.SetGear(gear)) ? std::cout << "Car set gear to " << to_string(m_car.GetGear()) :
		std::cout << "Car did not set gear to " << to_string(gear);
	std::cout << endl;

	return true;
}

bool CRemoteControl::SetSpeed(std::istream& args)
{
	std::string arg;
	args >> arg;
	int speed;
	try
	{
		speed = std::stoi(arg);
	}
	catch (exception e)
	{
		std::cout << "Unexpected argument " << arg << std::endl;
		return false;
	}
	(m_car.SetSpeed(speed)) ? std::cout << "Car set speed to " << to_string(m_car.GetSpeed()) :
		std::cout << "Car did not set speed to " << to_string(speed);
	std::cout << endl;

	return true;
}