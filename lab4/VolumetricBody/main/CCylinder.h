#pragma once

#include "CBody.h"

class CCylinder final : public CBody
{
public:
	CCylinder(double density, double baseRadius, double height);

	double GetBaseRadius() const;
	double GetHeight() const;
	double GetVolume() const override;

private:
	void AppendProperties(std::ostream& strm) const override;
	double m_base_radius;
	double m_height;
};