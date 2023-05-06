#include "CCompound.h"
#include "stdafx.h"
#include "CBody.h"

bool CheckAvailableChild(CBody& child)
{
	return true;
}

bool CCompound::AddChildBody(CBody& child)
{
	if (CheckAvailableChild(child))
	{
		return false;
	}
	m_bodies.push_back(child);
	return true;
}

double CCompound::GetMass() const noexcept
{
	return 2;
}

double CCompound::GetVolume() const
{
	return 2;
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