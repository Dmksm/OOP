#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../main/CHttpUrl.h"

SCENARIO("Entering url")
{
	WHEN("Entering url without port")
	{
		CHttpUrl url("https://learn.microsoft.com/ru-ru/cpp/cpp/cdecl?view=msvc-170");
		THEN("")
		{
			REQUIRE(url.GetUrl() == "https://learn.microsoft.com/ru-ru/cpp/cpp/cdecl");
			REQUIRE(url.GetDocument() == "/ru-ru/cpp/cpp/cdecl");
			REQUIRE(url.GetDomain() == "learn.microsoft.com");
			REQUIRE(url.GetPort() == 443);
			REQUIRE(url.GetProtocol() == Protocol::HTTPS);
		}
	}
	WHEN("Entering url without document")
	{
		CHttpUrl urlWithSlash("http://translate.yandex.ru:8900/?page=1");
		CHttpUrl url("http://translate.yandex.ru:789");
		THEN("")
		{
			REQUIRE(urlWithSlash.GetUrl() == "http://translate.yandex.ru:8900/");
			REQUIRE(urlWithSlash.GetDocument() == "/");
			REQUIRE(urlWithSlash.GetDomain() == "translate.yandex.ru");
			REQUIRE(urlWithSlash.GetPort() == 8900);
			REQUIRE(urlWithSlash.GetProtocol() == Protocol::HTTP);

			REQUIRE(url.GetUrl() == "http://translate.yandex.ru:789/");
			REQUIRE(url.GetDocument() == "/");
			REQUIRE(url.GetDomain() == "translate.yandex.ru");
			REQUIRE(url.GetPort() == 789);
			REQUIRE(url.GetProtocol() == Protocol::HTTP);
		}
	}
	WHEN("Entering url without port and document")
	{
		CHttpUrl url("https://en.wikipedia.org");
		THEN("")
		{
			REQUIRE(url.GetUrl() == "https://en.wikipedia.org/");
			REQUIRE(url.GetDocument() == "/");
			REQUIRE(url.GetDomain() == "en.wikipedia.org");
			REQUIRE(url.GetPort() == 443);
			REQUIRE(url.GetProtocol() == Protocol::HTTPS);
		}
	}
	WHEN("Entering url with domain, document, protocol and port")
	{
		CHttpUrl url("en.wikipedia.org", "w/index.php", Protocol::HTTPS, 1789);
		THEN("")
		{
			REQUIRE(url.GetUrl() == "https://en.wikipedia.org:1789/w/index.php");
			REQUIRE(url.GetDocument() == "/w/index.php");
			REQUIRE(url.GetDomain() == "en.wikipedia.org");
			REQUIRE(url.GetPort() == 1789);
			REQUIRE(url.GetProtocol() == Protocol::HTTPS);
		}
	}
}