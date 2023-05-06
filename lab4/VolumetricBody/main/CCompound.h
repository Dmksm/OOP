#pragma once

#include "CBody.h"

class CCompound final : public CBody
{
public:
	CCompound(std::vector<CBody&> bodies);
	bool AddChildBody(CBody& child);
	double GetVolume() const override;

private:
	void AppendProperties(std::ostream& strm) const override;
	std::vector<CBody&> m_bodies;
};