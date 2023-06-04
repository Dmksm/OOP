#include "CUrlParsingError.h"

CUrlParsingError::CUrlParsingError(std::string msg)
	: invalid_argument(msg)
{
	std::cout << "Got a error!" << msg << std::endl;
}