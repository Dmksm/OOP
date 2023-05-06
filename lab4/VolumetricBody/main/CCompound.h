#pragma once

#include "CBody.h"

class CCompound final : public CBody
{
public:
	bool AddChildBody(CBody& child);
	double GetVolume() const override;
	double GetMass() const noexcept override;

private:
	void AppendProperties(std::ostream& strm) const override;
	std::vector<CBody&> m_bodies;
};