#include "CHttpUrl.h"
#include "CUrlParsingError.h"

struct UrlComponents
{
	std::string domain = "localhost";
	std::string document;
	Protocol protocol = Protocol::HTTP;
	unsigned short port = 80;
};

void ValidateUrl(const std::string& url)
{
	std::regex urlRegex(R"(^https?://[0-9a-z\.-]+(:[1-9][0-9]*)?(/[^\s]*)*$)");

	if (!std::regex_match(url, urlRegex))
	{
		throw CUrlParsingError("Unvalid url: " + url);
	}
}

std::string ToHttpUrl(
	std::string const& domain,
	std::string const& document,
	Protocol protocol,
	unsigned short port)
{
	std::string delimeter;
	if (document[0] != '/')
	{
		delimeter = "/";
	}
	std::string protocolFormatted = (static_cast<bool>(protocol)) ? "https" : "http";

	std::string url = protocolFormatted + "://" + domain
		+ ":" + std::to_string(port) + delimeter + document;
	try
	{
		ValidateUrl(url);
	}
	catch (CUrlParsingError e)
	{
		throw std::invalid_argument("Invalid argument!");
	}

	return url;
}

void CutProtocolFromUrlAndPasteItIntoComponents(UrlComponents& urlComponents, std::string& url)
{
	size_t endPos = url.find("://");
	std::string protocol = url.substr(0, endPos);
	Protocol formatedProtocol;

	if (protocol == "http")
	{
		formatedProtocol = Protocol::HTTP;
	}
	else if (protocol == "https")
	{
		formatedProtocol = Protocol::HTTPS;
	}
	else
	{
		throw CUrlParsingError("Invalid name of protocol! Given: " + protocol);
	}

	url = url.substr(endPos + 3);
	urlComponents.protocol = formatedProtocol;
}

size_t AddPortAndDomainAndReturnDocumentPos(UrlComponents& urlComponents, const std::string& url)
{
	size_t startPortPos = url.find(":");
	size_t startDocumentPos = url.find("/");

	unsigned short port = (urlComponents.protocol == Protocol::HTTP) ? 80 : 443;
	std::string domain = url.substr(0, startDocumentPos);
	if (startPortPos < startDocumentPos)
	{
		domain = url.substr(0, startPortPos);
		try
		{
			std::string stringPort = url.substr(startPortPos + 1, startDocumentPos);
			port = static_cast<unsigned short>(std::stoul(stringPort.c_str(), NULL, 0));
		}
		catch (std::exception& e)
		{
			throw CUrlParsingError(e.what());
		}
	}

	urlComponents.port = port;
	urlComponents.domain = domain;
	
	return startDocumentPos;
}

void AddDocument(UrlComponents& urlComponents, const std::string& url, size_t startDocumentPos)
{
	std::string document = "/";
	if (startDocumentPos != std::string::npos)
	{
		size_t queryPos = url.find("?");
		document += url.substr(startDocumentPos + 1, queryPos - startDocumentPos - 1);
	}

	urlComponents.document = document;
}

UrlComponents FromUrl(std::string url)
{
	UrlComponents urlComponents;
	CutProtocolFromUrlAndPasteItIntoComponents(urlComponents, url);
	size_t startDocumentPos = AddPortAndDomainAndReturnDocumentPos(urlComponents, url);
	AddDocument(urlComponents, url, startDocumentPos);

	return urlComponents;
}

bool CheckUrl(const std::string& url)
{
	ValidateUrl(url);
	return true;
}

CHttpUrl::CHttpUrl(std::string const& url)
	: m_url(CheckUrl(url) ? url : "")
{
}

CHttpUrl::CHttpUrl(
	std::string const& domain,
	std::string const& document,
	Protocol protocol)
	: m_url(ToHttpUrl(domain, document, protocol, (static_cast<bool>(protocol)) ? 80 : 443))
{
}

CHttpUrl::CHttpUrl(
	std::string const& domain,
	std::string const& document,
	Protocol protocol,
	unsigned short port)
	: m_url(ToHttpUrl(domain, document, protocol, port))
{
}

std::string CHttpUrl::GetUrl() const
{
	UrlComponents components = FromUrl(m_url);

	std::string port;
	if (components.port != 80 && components.port != 443)
	{
		port = ":" + std::to_string(components.port);
	}

	std::string protocol = (static_cast<bool>(components.protocol)) ? "https" : "http";
	return protocol + "://" + components.domain + 
		port + components.document;
}

std::string CHttpUrl::GetDomain() const
{
	return FromUrl(m_url).domain;
}

std::string CHttpUrl::GetDocument() const
{
	return FromUrl(m_url).document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return FromUrl(m_url).protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return FromUrl(m_url).port;
}