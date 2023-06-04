#pragma once

#include "stdafx.h"
#include "CUrlParsingError.h"

enum class Protocol
{
	HTTP,
	HTTPS
};

class CUrlParsingError;

class CHttpUrl
{
public:
	CHttpUrl(std::string const& url);

	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = Protocol::HTTP);

	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol,
		unsigned short port);

	std::string GetUrl() const;

	std::string GetDomain() const;

	std::string GetDocument() const;

	Protocol GetProtocol() const;

	unsigned short GetPort() const;

private:
	std::string m_url;
};