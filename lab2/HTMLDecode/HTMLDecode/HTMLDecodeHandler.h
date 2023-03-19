#pragma once

#include <iostream>
#include <string>
#include <map>

struct HTML_SEQUENCE
{
    bool isHtmlSequence = false;
    std::string sequence;
};

void AddHtmlSequence(std::string& decodedHtml, HTML_SEQUENCE& htmlSequence);

void AddChar(std::string& decodedHtml, char ch, HTML_SEQUENCE& htmlSequence);

void DecodeByChar(std::string& decodedHtml, char ch, HTML_SEQUENCE& htmlSequence);

std::string HtmlDecode(const std::string& html);