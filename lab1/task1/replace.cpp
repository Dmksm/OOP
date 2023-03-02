#include <iostream>
#include <string>
#include <fstream>

std::string ReplaceSubstring(const std::string &line, const std::string &searchString,
	const std::string &replacementString)
{//переменные как можно ближе к их , использовать метод empty для строк, не выносить в переменную что имеется у строки string.length();
	const int minSearchStringLength = 1;
	const size_t searchStringLength = searchString.length();
	std::string resultString = line; // лучше не тратить много ресурсов на 
	if (searchStringLength >= minSearchStringLength)
	{
		const size_t notFound = std::string::npos; // не нужно констану , для нуля тоже нет смысла кнстанту 
		const size_t startPos = 0;
		const std::string emptyValue = "";//по умолчанию пустая строка поэтому убраить 
		resultString = emptyValue; // убрать предыдущее действие 
		size_t pos = startPos;
		
		while (pos < line.length())
		{
			size_t searchStringPos = line.find(searchString, pos);
			resultString.append(line, pos, searchStringPos - pos);
			

			if (searchStringPos == std::string::npos)
			{
				break;
			}

			resultString.append(replacementString);	
			pos = searchStringPos + searchStringLength;
		}
		
	}
	return resultString;
}

void CopyStreamWithReplacement(std::istream& input, std::ostream& output,
	const std::string& searchString, const std::string& replacementString)
{
	std::string line;
	while (getline(input, line))
	{
		output << ReplaceSubstring(line, searchString, replacementString) << std::endl;
	}
}

bool CheckInputParametersNumber(int paramNumber)
{
	const int parametersNumber = 5;
	if (paramNumber != parametersNumber)
	{
		std::cout << "The number of parameters must be " << parametersNumber << " !\n";
		return false;
	}
	return true;
}

bool CheckOpenFile(std::ifstream &file, const std::string &fileName)
{
	if (!file.is_open())
	{
		std::cout << "Unable to open " << fileName << " file!\n";
		return false;
	}
	return true;
}

int main(int argc, char* argv[])
{
	if (!CheckInputParametersNumber(argc))
	{
		return 1;
	}
	const std::string inputFileName = argv[1];
	std::ifstream inputFile(inputFileName);
	if (!CheckOpenFile(inputFile, inputFileName))
	{
		return 2;
	}
	const std::string outputFileName = argv[2];
	std::ofstream outputFile(outputFileName);
	const std::string searchString = argv[3];
	const std::string replacementString = argv[4];

	CopyStreamWithReplacement(inputFile, outputFile, searchString, replacementString);
	return 0;
}