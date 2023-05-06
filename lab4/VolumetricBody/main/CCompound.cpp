#include "CCompound.h"
#include "stdafx.h"
#include "CBody.h"

double GetCompoundDensity(std::vector<CBody&> bodies)
{
	int mass = 0;
	int volume = 0;
	for (auto body : bodies)
	{
		mass += body.GetMass();
		volume += body.GetVolume();
	}
	return mass / volume;
}

bool CheckAvailableChild(CBody& child)
{
	return true;
}

CCompound::CCompound(std::vector<CBody&> bodies)
	: CBody("Compound", GetCompoundDensity(bodies))
	, m_bodies(bodies)
{
}

bool CCompound::AddChildBody(CBody& child)
{
	if (CheckAvailableChild(child))
	{
		return false;
	}
	CCompound::CCompound(m_bodies);
	return true;
}

double CCompound::GetVolume() const
{
	double volume = 0;
	for (auto body : m_bodies)
	{
		double bodyVolume = body.GetVolume();
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
		strm << " " << body.ToString();
	}
	strm << std::endl;
}