#include "CarHandler.h";

bool Car::IsTurnedOn() const
{
	return m_isOn;
}

int Car::GetSpeed() const
{
	return m_selectedSpeed;
}

unsigned Car::GetGear() const
{
	return m_selectedGear;
}

void Car::TurnOnEngine()
{
	m_isOn = true;
}

bool Car::TurnOffEngine()
{
	if (m_selectedGear == 0 && m_selectedSpeed == 0)
	{
		m_isOn = false;
	}
	return !m_isOn;
}

std::string Car::GetDirection() const //поправит ьситуцию когда ехали назад переклюсили на 0 и едем вперед посему то
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

bool Car::SetGear(int gear)
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

bool Car::SetSpeed(int speed)
{
	const int MAX_SPEED = 150;
	bool isAvailableSpeed = (speed >= 0) && (speed <= MAX_SPEED) && //учесть ограничение в 150 
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