#pragma once
#include "stdafx.h"

class CUrlParsingError : public std::invalid_argument
{
public:
	CUrlParsingError(std::string msg);
};