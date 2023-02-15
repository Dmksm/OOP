#include <iostream>
#include <string>
#include <fstream>
#include <regex>

void ReplaceSubstring(std::string &line, const std::string &searchString,
	const std::string &replacementString)
{
	const int minSearchStringLength = 1;
	const size_t searchStringLength = searchString.length();
	if (searchStringLength >= minSearchStringLength)
	{
		size_t pos = line.find(searchString);
		const size_t notFound = std::string::npos;
		while (pos != notFound)
		{
			line.replace(pos, searchStringLength, replacementString);
			pos = line.find(searchString);
		}
	}
}

void CopyStreamWithReplacement(std::istream& input, std::ostream& output,
	const std::string& searchString, const std::string& replacementString)
{
	std::string line;
	while (getline(input, line))
	{
		ReplaceSubstring(line, searchString, replacementString);
		output << line << std::endl;
	}
}

void CloseFiles(std::ifstream &inputFile, std::ofstream &outputFile)
{
	inputFile.close();
	outputFile.close();
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
	CloseFiles(inputFile, outputFile);
	return 0;
}