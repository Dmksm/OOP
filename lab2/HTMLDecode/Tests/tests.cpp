#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../HTMLDecode/HTMLDecodeHandler.h"

SCENARIO("Adding html sequence")
{
	WHEN("input sequence is &quot;")
	{
		THEN("add \" sequence")
		{
			std::string decodedHtml, resultHtml = "\"";
			HTML_SEQUENCE htmlSequence;
			htmlSequence.sequence = "&quot;";
			AddHtmlSequence(decodedHtml, htmlSequence);
			REQUIRE(decodedHtml == resultHtml);
		}
	}
	WHEN("input sequence is &lt;")
	{
		THEN("add < sequence")
		{
			std::string decodedHtml, resultHtml = "<";
			HTML_SEQUENCE htmlSequence;
			htmlSequence.sequence = "&lt;";
			AddHtmlSequence(decodedHtml, htmlSequence);
			REQUIRE(decodedHtml == resultHtml);
		}
	}
	WHEN("input sequence is &gt;")
	{
		THEN("add > sequence")
		{
			std::string decodedHtml, resultHtml = ">";
			HTML_SEQUENCE htmlSequence;
			htmlSequence.sequence = "&gt;";
			AddHtmlSequence(decodedHtml, htmlSequence);
			REQUIRE(decodedHtml == resultHtml);
		}
	}
	WHEN("input sequence is &amp;")
	{
		THEN("add & sequence")
		{
			std::string decodedHtml, resultHtml = "&";
			HTML_SEQUENCE htmlSequence;
			htmlSequence.sequence = "&amp;";
			AddHtmlSequence(decodedHtml, htmlSequence);
			REQUIRE(decodedHtml == resultHtml);
		}
	}
	WHEN("input sequence is not html sequence")
	{
		THEN("add not html sequence")
		{
			std::string decodedHtml, resultHtml = "&;";
			HTML_SEQUENCE htmlSequence;
			htmlSequence.sequence = "&;";
			AddHtmlSequence(decodedHtml, htmlSequence);
			REQUIRE(decodedHtml == resultHtml);
		}
	}
}

SCENARIO("Adding char")
{
	WHEN("input char is 'a'")
	{
		THEN("add 'a'")
		{
			std::string decodedHtml, resultHtml = "a";
			HTML_SEQUENCE htmlSequence;
			char ch = 'a';
			AddChar(decodedHtml, ch, htmlSequence);
			REQUIRE(decodedHtml == resultHtml);
			REQUIRE(htmlSequence.sequence == "");
		}
	}
	WHEN("input char is 'z'")
	{
		THEN("add 'z'")
		{
			std::string decodedHtml, resultHtml = "z";
			HTML_SEQUENCE htmlSequence;
			char ch = 'z';
			AddChar(decodedHtml, ch, htmlSequence);
			REQUIRE(decodedHtml == resultHtml);
			REQUIRE(htmlSequence.sequence == "");
		}
	}
	WHEN("input char is 'A'")
	{
		THEN("add 'A'")
		{
			std::string decodedHtml, resultHtml = "A";
			HTML_SEQUENCE htmlSequence;
			char ch = 'A';
			AddChar(decodedHtml, ch, htmlSequence);
			REQUIRE(decodedHtml == resultHtml);
			REQUIRE(htmlSequence.sequence == "");
		}
	}
	WHEN("input char is 'Z'")
	{
		THEN("add 'Z'")
		{
			std::string decodedHtml, resultHtml = "Z";
			HTML_SEQUENCE htmlSequence;
			char ch = 'Z';
			AddChar(decodedHtml, ch, htmlSequence);
			REQUIRE(decodedHtml == resultHtml);
			REQUIRE(htmlSequence.sequence == "");
		}
	}
	WHEN("input char is '&'")
	{
		THEN("add '&'")
		{
			std::string decodedHtml, resultHtml = "";
			HTML_SEQUENCE htmlSequence;
			char ch = '&';
			AddChar(decodedHtml, ch, htmlSequence);
			REQUIRE(decodedHtml == resultHtml);
			REQUIRE(htmlSequence.sequence == "&");
		}
	}
	WHEN("input char is ';'")
	{
		THEN("add ';'")
		{
			std::string decodedHtml, resultHtml = ";";
			HTML_SEQUENCE htmlSequence;
			char ch = ';';
			AddChar(decodedHtml, ch, htmlSequence);
			REQUIRE(decodedHtml == resultHtml);
			REQUIRE(htmlSequence.sequence == "");
		}
	}
	WHEN("input char is ' '")
	{
		THEN("add ' '")
		{
			std::string decodedHtml, resultHtml = " ";
			HTML_SEQUENCE htmlSequence;
			char ch = ' ';
			AddChar(decodedHtml, ch, htmlSequence);
			REQUIRE(decodedHtml == resultHtml);
			REQUIRE(htmlSequence.sequence == "");
		}
	}
}

SCENARIO("Decode HTML")
{
	WHEN("input HTML is empty")
	{
		THEN("result is empty")
		{
			std::string html, resultHtml;
			REQUIRE(HtmlDecode(html) == resultHtml);
		}
	}
	WHEN("input HTML is one character")
	{
		THEN("result is one character")
		{
			std::string html = "&", resultHtml = "&";
			REQUIRE(HtmlDecode(html) == resultHtml);
		}
	}
	WHEN("input HTML is not html sequence")
	{
		THEN("result is one character")
		{
			std::string html = "&;", resultHtml = "&;";
			REQUIRE(HtmlDecode(html) == resultHtml);
		}
	}
	WHEN("input HTML is html sequence")
	{
		THEN("result is one character")
		{
			std::string html = "&lt;&quot; &apos;5&gt;&;&amp;", resultHtml = "<\" \'5>&;&";
			REQUIRE(HtmlDecode(html) == resultHtml);
		}
	}
}