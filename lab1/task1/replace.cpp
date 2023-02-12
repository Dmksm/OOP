#include <iostream>
#include <string>
#include <fstream>
#include <regex>

void CopyStreamWithReplacement(std::istream& input, std::ostream& output,
	const std::string& searchString, const std::string& replacementString)
{
	std::string line;
	const int minSearchStringLength = 1;
	while (getline(input, line))
	{
		if (searchString.length() >= minSearchStringLength)
		{
			line = std::regex_replace(line, std::regex(searchString), replacementString);
		}
		output << line << std::endl;
	}
}

int main(int argc, char* argv[])
{
	const int parametersNumber = 5;
	if (argc != parametersNumber)
	{
		std::cout << "The number of parameters must be " << parametersNumber << " !\n";
		return 1;
	}
	const std::string inputFileName = argv[1];
	const std::string outputFileName = argv[2];
	const std::string searchString = argv[3];
	const std::string replacementString = argv[4];
	std::ifstream inputFile(inputFileName);
	std::ofstream outputFile(outputFileName);
	if (!inputFile.is_open() || !outputFile.is_open())
	{
		std::cout << "Unable to open " << inputFileName << " or " << outputFileName <<
			" file!\n";
		return 1;
	}
	CopyStreamWithReplacement(inputFile, outputFile, searchString, replacementString);
	outputFile.flush();
	return 0;
}