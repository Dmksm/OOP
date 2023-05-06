#include "CCylinder.h"

CCylinder::CCylinder(double density, double baseRadius, double height)
	: CBody("Cylinder", density)
	, m_base_radius(baseRadius)
	, m_height(height)
{
}

double CCylinder::GetBaseRadius() const
{
	return m_base_radius;
}

double CCylinder::GetVolume() const
{
	return (pow(m_base_radius, 2) * M_PI * m_height) * 1 / 3;
}

double CCylinder::GetHeight() const
{
	return m_height;
}

void CCylinder::AppendProperties(std::ostream& strm) const
{
	strm << "\tbase_radius = " << GetBaseRadius() << "\theight = " << GetHeight() << std::endl;
}