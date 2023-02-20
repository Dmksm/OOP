#include <iostream>
#include <string>
#include <fstream>

std::string ReplaceSubstring(const std::string &line, const std::string &searchString,
	const std::string &replacementString)
{
	const int minSearchStringLength = 1;
	const size_t searchStringLength = searchString.length();
	std::string resultString = line;
	if (searchStringLength >= minSearchStringLength)
	{
		const size_t notFound = std::string::npos;
		const size_t startPos = 0;
		const std::string emptyValue = "";
		resultString = emptyValue;
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
//проверить на милионе символов за сек
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
//параметры закинуть в опциональную структуру на гит хабе есть , и вернуть или ошибку или готовые файлы
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