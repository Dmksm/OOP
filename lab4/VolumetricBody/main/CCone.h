#pragma once

#include "CBody.h"

class CCone final : public CBody
{
public:
	CCone(double density, double baseRadius, double height);

	double GetBaseRadius() const;
	double GetHeight() const;
	double GetVolume() const override;

private:
	void AppendProperties(std::ostream& strm) const override;
	double m_base_radius; //������� ���� ������ m_ �����
	double m_height;
};