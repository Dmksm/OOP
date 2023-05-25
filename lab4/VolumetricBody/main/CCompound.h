#pragma once

#include "CBody.h"

class CCompound final : public CBody
{
public:
	CCompound(std::vector<std::shared_ptr<CBody>> bodies);
	bool AddChildBody(std::shared_ptr<CBody> child); //обработку зацикливания добавить
	double GetVolume() const override;

private:
	void AppendProperties(std::ostream& strm) const override;
	std::vector<std::shared_ptr<CBody>> m_bodies;
};