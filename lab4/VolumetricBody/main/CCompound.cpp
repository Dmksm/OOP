#include "CCompound.h"
#include "stdafx.h"
#include "CBody.h"

double GetCompoundDensity(std::vector<std::shared_ptr<CBody>> bodies) //работает с полями класса - лучше сделать методом класса
{
	double mass = 0, volume = 0;
	for (auto body : bodies)
	{
		mass += (*body).GetMass(); 
		volume += (*body).GetVolume();
	}
	return mass / volume;
}

CCompound::CCompound(std::vector<std::shared_ptr<CBody>> bodies)
	: CBody("Compound", GetCompoundDensity(bodies))
	, m_bodies(bodies)
{
}

bool CCompound::AddChildBody(std::shared_ptr<CBody> child)
{
	m_bodies.push_back(child);
	return true;
}

double CCompound::GetVolume() const
{
	double volume = 0;
	for (auto body : m_bodies)
	{
		double bodyVolume = (*body).GetVolume();
		if (volume <= std::numeric_limits<double>::max() - bodyVolume)
		{
			volume += bodyVolume;
		}
		else
		{
			volume = std::numeric_limits<double>::max();
		}
	}
	return volume;
}

void CCompound::AppendProperties(std::ostream& strm) const
{
	strm << "\tpieces of compound bodies:";
	for (auto body: m_bodies)
	{
		strm << " " << (*body).ToString();
	}
	strm << std::endl;
}