#pragma once

#include "stdafx.h"

class CAR
{
public:
	void TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);
	bool IsTurnedOn() const;
	std::string GetDirection() const;
	int GetSpeed() const;
	int GetGear() const;

private:
	using SpeedForGear = std::map<int, std::pair<int, int>>;;

	bool m_isOn = false;
	int m_selectedGear = 0;
	int m_selectedSpeed = 0;

	const SpeedForGear m_speedForGear = { 
		{ -1, { 0, 20 } },
		{ 0, { 0, INT_MAX } },
		{ 1, { 0, 30 } },
		{ 2, { 20, 50 } },
		{ 3, { 30, 60 } },
		{ 4, { 40, 90 } },
		{ 5, { 50, 150 } }
	};
};