#include <fstream>
#include <iostream>
#include <string>
#include <vector>

const int rows = 100;
const int columns = 100;

struct Position
{
	int column = 0;
	int row = 0;
};

void CloseFiles(std::ifstream& inputFile, std::ofstream& outputFile)
{
	inputFile.close();
	outputFile.close();
}

bool CheckInputParametersNumber(int paramNumber)
{
	const int parametersNumber = 3;
	if (paramNumber != parametersNumber)
	{
		std::cout << "The number of parameters must be " << parametersNumber << " !\n";
		return false;
	}
	return true;
}

bool CheckOpenFile(std::ifstream& file, const std::string& fileName)
{
	if (!file.is_open())
	{
		std::cout << "Unable to open " << fileName << " file!\n";
		return false;
	}
	return true;
}

bool CheckOnAvailableSymbol(char symbol, int& startPositionCount,
	int& finishPositionCount, bool& isStartPoint)
{
	const char startPoint = 'A';
	const char finishPoint = 'B';
	const char way = ' ';
	const char wall = '#';
	if ((symbol != startPoint) && (symbol != finishPoint) && (symbol != way) && (symbol != wall))
	{
		std::cout << "The labyrinth must consist of available symbols: '" << startPoint << "' or '" << finishPoint << "' or '" << way << "' or '" << wall << "'\n";
		return false;
	}
	isStartPoint = false;
	if (symbol == startPoint)
	{
		isStartPoint = true;
		startPositionCount++;
	}
	if (symbol == finishPoint)
	{
		finishPositionCount++;
	}
	return true;
}

bool CharacterAddition(std::vector<std::vector<char>>& labyrinth, const std::string& line,
	int currLine, int& startPointsNumber, int& finishPointsNumber, Position startPosition)
{
	int availableLength = line.length();
	if (availableLength > rows)
	{
		availableLength = rows;
	}

	for (int currElem = 0; currElem < availableLength; currElem++)
	{
		char symbol = line[currElem];
		bool isStartPoint = false;
		if (!CheckOnAvailableSymbol(symbol, startPointsNumber,
				finishPointsNumber, isStartPoint))
		{
			return false;
		}
		if (isStartPoint)
		{
			startPosition.column = currLine;
			startPosition.row = currElem;
		}
		labyrinth[currLine][currElem] = symbol;
	}

	return true;
}

bool CheckStartAndEndPointNumbers(int startPointsNumber, int finishPointsNumber)
{
	const int expectedStartPointsNumber = 1;
	const int expectedFinishPointsNumber = 1;
	if ((startPointsNumber != expectedStartPointsNumber) || (finishPointsNumber != expectedFinishPointsNumber))
	{
		std::cout << "The number of start and end points must be equal to "
				  << expectedStartPointsNumber << " and " << expectedFinishPointsNumber << " respectively\n";
		return false;
	}
	return true;
}

bool GetLabyrinth(std::ifstream& input, std::vector<std::vector<char>>& labyrinth,
	Position& startPosition)
{
	int currLine = -1;
	std::string line;
	int startPointsNumber = 0;
	int finishPointsNumber = 0;
	while (getline(input, line) && (currLine++ < columns))
	{
		if (!CharacterAddition(labyrinth, line, currLine, startPointsNumber,
				finishPointsNumber, startPosition))
		{
			return false;
		}
	}

	if (!CheckStartAndEndPointNumbers(startPointsNumber, finishPointsNumber))
	{
		return false;
	}
	return true;
}

void PrintLabyrinth(std::ofstream& output, std::vector<std::vector<char>>& labyrinth)
{
	for (int currLine = 0; currLine < labyrinth.size(); currLine++)
	{
		for (int currElem = 0; currElem < labyrinth[currLine].size(); currElem++)
		{
			output << labyrinth[currLine][currElem];
		}
		output << std::endl;
	}
}

void PrintWay(std::vector<std::vector<char>> labyrinth, Position startPosition)
{

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

	Position startPosition;
	std::vector<std::vector<char>> labyrinth(rows, std::vector<char>(columns));
	if (!GetLabyrinth(inputFile, labyrinth, startPosition))
	{
		return 3;
	}

	PrintWay(labyrinth, startPosition);

	const std::string outputFileName = argv[2];
	std::ofstream outputFile(outputFileName);
	PrintLabyrinth(outputFile, labyrinth);

	CloseFiles(inputFile, outputFile);
	return 0;
}
