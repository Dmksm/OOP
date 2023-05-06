#include "CCone.h"

CCone::CCone(double density, double baseRadius, double height)
	: CBody("Cone", density)
	, m_base_radius(baseRadius)
	, m_height(height)
{
}

double CCone::GetBaseRadius() const
{
	return m_base_radius;
}

double CCone::GetVolume() const
{
	return (pow(m_base_radius, 2) * M_PI * m_height) * 1 / 3;
}

double CCone::GetHeight() const
{
	return m_height;
}

void CCone::AppendProperties(std::ostream& strm) const
{
	strm << "\tbase_radius = " << GetBaseRadius() << "\theight = " << GetHeight() << std::endl;
}