#include "CParallelepiped.h"

CParallelepiped::CParallelepiped(double density, double width, double height, double depth)
	: CBody("Parallelepiped", density)
	, m_width(width)
	, m_height(height)
	, m_depth(depth)
{
}

double CParallelepiped::GetWidth() const
{
	return m_width;
}

double CParallelepiped::GetVolume() const
{
	return m_width * m_height * m_depth;
}

double CParallelepiped::GetDepth() const
{
	return m_depth;
}

double CParallelepiped::GetHeight() const
{
	return m_height;
}

void CParallelepiped::AppendProperties(std::ostream& strm) const
{
	strm << "\twidth = " << GetWidth() << "\theight = " << GetHeight() << "\tdepth = " << GetDepth() << std::endl;
}