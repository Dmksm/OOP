#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

const int rows = 100;
const int columns = 100;

struct Position
{
	int column = 0;
	int row = 0;
};

struct FieldCell
{
	char symbol;
	int mark = -1;
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
	const char wall = '#'; //если используется в разных функциях выносить в глобальную обсласть
	if ((symbol != startPoint) && (symbol != finishPoint) && (symbol != way) &&
		(symbol != wall))
	{
		std::cout << "The labyrinth must consist of available symbols: '" << startPoint <<
			"' or '" << finishPoint << "' or '" << way << "' or '" << wall << "'\n";
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

bool CharacterAddition(std::vector<std::vector<FieldCell>>& labyrinth, const std::string& line,
	int currLine, int& startPointsNumber, int& finishPointsNumber, Position& startPosition) //переназвать на добавление линии вместо currLine line index
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
		labyrinth[currLine][currElem].symbol = symbol;
	}

	return true;
}

bool CheckStartAndEndPointNumbers(int startPointsNumber, int finishPointsNumber)
{
	const int expectedStartPointsNumber = 1;
	const int expectedFinishPointsNumber = 1;
	if ((startPointsNumber != expectedStartPointsNumber) ||
		(finishPointsNumber != expectedFinishPointsNumber))
	{
		std::cout << "The number of start " << startPointsNumber << " and end points " <<
			finishPointsNumber << " must be equal to " << expectedStartPointsNumber <<
			" and " << expectedFinishPointsNumber << " respectively\n";
		return false;
	}
	return true;
}

bool GetLabyrinth(std::ifstream& input, std::vector<std::vector<FieldCell>>& labyrinth,
	Position& startPosition)
{
	int currLine = -1;
	std::string line;
	int startPointsNumber = 0;
	int finishPointsNumber = 0;
	while (getline(input, line) && (++currLine < columns))
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

void PrintLabyrinth(std::ofstream& output, std::vector<std::vector<FieldCell>>& labyrinth)
{
	for (size_t currLine = 0; currLine < labyrinth.size();)
	{
		for (size_t currElem = 0; currElem < labyrinth[currLine].size(); currElem++)
		{
			output << labyrinth[currLine][currElem].symbol;
		}
		if (++currLine < labyrinth.size())
		{
			output << std::endl;
		}
	}
}

void AddQueue(std::vector<std::vector<FieldCell>>& labyrinth, const Position& pos,
	std::queue<Position>& queue, int mark)
{
	const int minColumnPosition = 0;
	const int minRowPosition = 0;
	const char wall = '#';
	const int standardMark = -1;
	if (pos.column >= minColumnPosition && pos.column <= columns - 1 &&
		pos.row >= minRowPosition && pos.row <= rows - 1 &&
		labyrinth[pos.column][pos.row].symbol != wall &&
		labyrinth[pos.column][pos.row].mark == standardMark)
	{
		labyrinth[pos.column][pos.row].mark = ++mark;
		queue.push(pos);
	}
}

void MoveQueue(std::vector<std::vector<FieldCell>>& labyrinth, const Position& pos,
	std::queue<Position>& queue, int mark)
{
	const Position topPos = { pos.column - 1, pos.row };
	AddQueue(labyrinth, topPos, queue, mark);
	const Position bottomPos = { pos.column + 1, pos.row };
	AddQueue(labyrinth, bottomPos, queue, mark);
	const Position leftPos = { pos.column, pos.row - 1 };
	AddQueue(labyrinth, leftPos, queue, mark);
	const Position rightPos = { pos.column, pos.row + 1 };
	AddQueue(labyrinth, rightPos, queue, mark);
	queue.pop();
}

bool CheckWay(std::vector<std::vector<FieldCell>>& labyrinth, const Position& pos, int mark)
{
	const int minColumnPosition = 0;
	const int minRowPosition = 0;
	if (pos.column >= minColumnPosition && pos.column <= columns - 1 &&
		pos.row >= minRowPosition && pos.row <= rows - 1 &&
		labyrinth[pos.column][pos.row].mark == --mark)
	{
		return true;
	}
	return false;
}

void RestoreWay(std::vector<std::vector<FieldCell>>& labyrinth, Position& pos, int& mark)
{
	Position nextPos;
	const Position topPos = { pos.column - 1, pos.row };
	if (CheckWay(labyrinth, topPos, mark))
	{
		nextPos = topPos;
	}
	const Position bottomPos = { pos.column + 1, pos.row };
	if (CheckWay(labyrinth, bottomPos, mark))
	{
		nextPos = bottomPos;
	}
	const Position leftPos = { pos.column, pos.row - 1 };
	if (CheckWay(labyrinth, leftPos, mark))
	{
		nextPos = leftPos;
	}
	const Position rightPos = { pos.column, pos.row + 1 };
	if (CheckWay(labyrinth, rightPos, mark))
	{
		nextPos = rightPos;
	}
	pos = nextPos;
	mark = labyrinth[pos.column][pos.row].mark;
}

void FindAndAddWay(std::vector<std::vector<FieldCell>>& labyrinth,
	const Position& startPosition)
{
	const char finishSymbol = 'B';
	const int startMark = 0;
	int mark = startMark;
	labyrinth[startPosition.column][startPosition.row].mark = mark;
	
	//больще разделений на смысловые части
	std::queue<Position> queue;
	queue.push(startPosition);

	FieldCell cell;
	Position pos;

	while (!queue.empty())
	{
		pos = queue.front();
		mark = labyrinth[pos.column][pos.row].mark;
		if (labyrinth[pos.column][pos.row].symbol == finishSymbol)
		{
			break;
		}
		MoveQueue(labyrinth, pos, queue, mark);
	}

	if (labyrinth[pos.column][pos.row].symbol != finishSymbol) 
	{
		return;
	}
	//разделеть на поиск и метку пути
	while (mark != startMark)
	{
		RestoreWay(labyrinth, pos, mark);
		if (mark == startMark)
		{
			break;
		}
		const char waySymbol = '.';
		labyrinth[pos.column][pos.row].symbol = waySymbol;
	}
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
	std::vector<std::vector<FieldCell>> labyrinth(rows, std::vector<FieldCell>(columns));
	if (!GetLabyrinth(inputFile, labyrinth, startPosition))
	{
		return 3;
	}
	FindAndAddWay(labyrinth, startPosition); //пометить вместо добавить потому что при чтении add подразумевает куда
	const std::string outputFileName = argv[2];
	std::ofstream outputFile(outputFileName);
	PrintLabyrinth(outputFile, labyrinth);
	CloseFiles(inputFile, outputFile);
	return 0;
}