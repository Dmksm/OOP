#include "HTMLDecodeHandler.h"

std::map <std::string, char> SPECIAL_SEQUENCES_LIST =
{
    {"&quot;", '\"'},
    {"&apos;", '\''},
    {"&lt;", '<'},
    {"&gt;", '>'},
    {"&amp;", '&'}
};

const int MAX_SEQUENCE_LENGTH = 6;

void AddChar(std::string& decodedHtml, char ch, HTML_SEQUENCE& htmlSequence)
{
    const char startSpecialSymbol = '&';

    if (ch == startSpecialSymbol)
    {
        htmlSequence.isHtmlSequence = true;
    }

    if (!htmlSequence.isHtmlSequence)
    {
        decodedHtml += ch;
    }
    else
    {
        htmlSequence.sequence += ch;
    }
}

void AddHtmlSequence(std::string& decodedHtml, HTML_SEQUENCE& htmlSequence)
{
	htmlSequence.isHtmlSequence = false;

    if (htmlSequence.sequence.length() > MAX_SEQUENCE_LENGTH ||
        SPECIAL_SEQUENCES_LIST.find(htmlSequence.sequence) == SPECIAL_SEQUENCES_LIST.end())
    {
        decodedHtml += htmlSequence.sequence;
    }
    else
    {
        decodedHtml += SPECIAL_SEQUENCES_LIST[htmlSequence.sequence];
    }

    htmlSequence.sequence = "";
}

void DecodeByChar(std::string& decodedHtml, char ch, HTML_SEQUENCE& htmlSequence)
{
    AddChar(decodedHtml, ch, htmlSequence);

	const char END_SPECIAL_SYMBOL = ';';
	if (htmlSequence.isHtmlSequence && ((ch == END_SPECIAL_SYMBOL) ||
        (htmlSequence.sequence.length() > MAX_SEQUENCE_LENGTH)))
	{
		AddHtmlSequence(decodedHtml, htmlSequence);
	}
}

std::string HtmlDecode(const std::string& html)
{
    std::string decodedHtml;
    HTML_SEQUENCE htmlSequence;

    for (char ch : html)
    {
        DecodeByChar(decodedHtml, ch, htmlSequence);
    }
	decodedHtml += htmlSequence.sequence;

    return decodedHtml;
}