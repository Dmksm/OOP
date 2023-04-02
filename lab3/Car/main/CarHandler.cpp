#include "CarHandler.h";

bool CAR::IsTurnedOn() const
{
	return m_isOn;
}

int CAR::GetSpeed() const
{
	return m_selectedSpeed;
}

int CAR::GetGear() const
{
	return m_selectedGear;
}

void CAR::TurnOnEngine()
{
	m_isOn = true;
}

bool CAR::TurnOffEngine()
{
	if (m_selectedGear == 0 && m_selectedSpeed == 0)
	{
		m_isOn = false;
	}
	return !m_isOn;
}

std::string CAR::GetDirection() const
{
	if (m_selectedGear < 0)
	{
		return "backward";
	}
	if (m_selectedSpeed == 0)
	{
		return "standing still";
	}
	return "forward";
}

bool CAR::SetGear(int gear)
{
	bool isAvailableGear = (gear >= -1) && (gear <= 5) &&
		(m_speedForGear.at(gear).first <= m_selectedSpeed) &&
		(m_selectedSpeed <= m_speedForGear.at(gear).second);

	bool isAvailableDirection = true;
	if (m_selectedSpeed != 0 && (
			(gear == -1) || 
			(m_selectedGear == -1 && gear == 1) ||
			(m_selectedGear == 0 && gear == 1)
		)
	)
	{
		isAvailableDirection = false;
	}

	if (isAvailableGear && m_isOn && isAvailableDirection)
	{
		m_selectedGear = gear;
		return true;
	}
	
	return false;
}

bool CAR::SetSpeed(int speed)
{
	bool isAvailableSpeed = (speed >= 0) && (speed <= INT_MAX) && 
		(speed >= m_speedForGear.at(m_selectedGear).first) &&
		(speed <= m_speedForGear.at(m_selectedGear).second);

	if (m_selectedGear == 0 && speed >= m_selectedSpeed)
	{
		isAvailableSpeed = false;
	}

	if (isAvailableSpeed && m_isOn)
	{
		m_selectedSpeed = speed;
		return true;
	}
	return false;
}