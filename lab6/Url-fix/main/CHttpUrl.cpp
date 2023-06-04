#include "CHttpUrl.h"
#include "CUrlParsingError.h"
#include "stdafx.h"

struct UrlComponents
{
	std::string domain;
	std::string document;
	Protocol protocol = Protocol::HTTP;
	unsigned short port = 80;
};

std::string ToUrlWithoutPort(
	std::string const& domain,
	std::string const& document,
	Protocol protocol,
	unsigned short port)
{
	std::string addChar = "";
	if (document[1] != '/')
	{
		addChar = "/" + document;
	}
	std::string protocolFormatted = (static_cast<bool>(protocol)) ? "HTTP" : "HTTPS";

	return protocolFormatted + "://" + domain + ":" + std::to_string(port) + addChar + document;
}

void ValidateUrlParameters(
	std::string const& domain,
	std::string const& document,
	unsigned short port)
{
	const std::regex regexPattern("([a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)");

	if ((domain.empty() || document.empty()) || !regex_match(domain + document, regexPattern))
	{
		throw CUrlParsingError("Invalid parameters!");
	}
}

std::string ToHttpUrl(
	std::string const& domain,
	std::string const& document,
	Protocol protocol,
	unsigned short port)
{
	ValidateUrlParameters(domain, document, port);
	return ToUrlWithoutPort(domain, document, protocol, port);
}

std::string ToHttpUrl(
	std::string const& domain,
	std::string const& document,
	Protocol protocol)
{
	unsigned short port = (static_cast<bool>(protocol)) ? 80 : 443;
	return ToHttpUrl(domain, document, protocol, port);
}

UrlComponents FromUrl(std::string url)
{
	UrlComponents urlComponents;
	
	size_t endPos = url.find("://");
	std::string protocol = url.substr(0, endPos);
	if (protocol == "http")
	{
		urlComponents.protocol = Protocol::HTTP;
	}
	else if (protocol == "https")	
	{
		urlComponents.protocol = Protocol::HTTPS;
	}
	else
	{
		throw CUrlParsingError("Invalid name of protocol!");
	}
	
	endPos += 3;
	url = url.substr(endPos);
	endPos = url.find("/");

	urlComponents.domain = url.substr(0, endPos);
	urlComponents.document = url.substr(endPos + 1);

	return urlComponents;
}

CHttpUrl::CHttpUrl(std::string const& url)
	: m_url(url)
{
}

/* инициализирует URL на основе переданных параметров.
	ѕри недопустимости входных параметров выбрасывает исключение
	std::invalid_argument
	≈сли им€ документа не начинаетс€ с символа /, то добавл€ет / к имени документа
*/
CHttpUrl::CHttpUrl(
	std::string const& domain,
	std::string const& document,
	Protocol protocol)
	: m_url(ToHttpUrl(domain, document, protocol))
{
}

/* инициализирует URL на основе переданных параметров.
	ѕри недопустимости входных параметров выбрасывает исключение
	std::invalid_argument
	≈сли им€ документа не начинаетс€ с символа /, то добавл€ет / к имени документа
*/
CHttpUrl::CHttpUrl(
	std::string const& domain,
	std::string const& document,
	Protocol protocol,
	unsigned short port)
	: m_url(ToHttpUrl(domain, document, protocol, port))
{
}

// возвращает строковое представление URL-а. ѕорт, €вл€ющийс€ стандартным дл€
// выбранного протокола (80 дл€ http и 443 дл€ https) в эту строку
// не должен включатьс€
std::string CHttpUrl::GetURL() const //todo 80 and 443 
{
	UrlComponents components = FromUrl(m_url);
	std::string protocol = (static_cast<bool>(components.protocol)) ? "HTTP" : "HTTPS";
	return protocol + "://" + components.domain + components.document;
}

// возвращает доменное им€
std::string CHttpUrl::GetDomain() const
{
	return FromUrl(m_url).domain;
}

/*
	¬озвращает им€ документа. ѕримеры:
		/
		/index.html
		/images/photo.jpg
*/
std::string CHttpUrl::GetDocument() const
{
	return FromUrl(m_url).document;
}

// возвращает тип протокола
Protocol CHttpUrl::GetProtocol() const
{
	return FromUrl(m_url).protocol;
}

// возвращает номер порта
unsigned short CHttpUrl::GetPort() const
{
	return FromUrl(m_url).port;
}