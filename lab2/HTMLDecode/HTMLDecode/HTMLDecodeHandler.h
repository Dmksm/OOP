#pragma once

#include <iostream>
#include <string>
//в заголовочном файле только инклюды для функций а размещать где используетсся
#include <map>

//не копировать данные в строку например стринг вью 
struct HTML_SEQUENCE
{
    bool isHtmlSequence = false;
    std::string sequence;
};

//оставить только функции для пользователя внутреенни исопльзовать только внутри
void AddHtmlSequence(std::string& decodedHtml, HTML_SEQUENCE& htmlSequence);

void AddChar(std::string& decodedHtml, char ch, HTML_SEQUENCE& htmlSequence);

void DecodeByChar(std::string& decodedHtml, char ch, HTML_SEQUENCE& htmlSequence);

std::string HtmlDecode(const std::string& html);