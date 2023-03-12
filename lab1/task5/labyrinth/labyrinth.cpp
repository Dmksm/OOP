#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

const int ROWS = 100;
const int COLUMNS = 100;
const char WALL = '#';
const char FINISH_SYMBOL = 'B';
const int START_MARK = 0;

struct Position
{
	int column = 0;
	int row = 0;
};

struct FieldCell
{
	char symbol = ' ';
	int mark = -1;
};

bool CheckInputParametersNumber(int paramNumber)
{
	const int PARAMETERS_NUMBER = 3;
	if (paramNumber != PARAMETERS_NUMBER)
	{
		std::cout << "The number of parameters must be " << PARAMETERS_NUMBER << " !\n";
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
	const char START_POINT = 'A';
	const char FINISH_POINT = 'B';
	const char WAY = ' ';
	if ((symbol != START_POINT) && (symbol != FINISH_POINT) && (symbol != WAY) &&
		(symbol != WALL))
	{
		std::cout << "The labyrinth must consist of available symbols: '" << START_POINT <<
			"' or '" << FINISH_POINT << "' or '" << WAY << "' or '" << WALL << "'\n";
		return false;
	}
	isStartPoint = false;
	if (symbol == START_POINT)
	{
		isStartPoint = true;
		startPositionCount++;
	}
	if (symbol == FINISH_POINT)
	{
		finishPositionCount++;
	}
	return true;
}

bool CharacterAddition(std::vector<std::vector<FieldCell>>& labyrinth, const std::string& line,
	int lineIndex, int& startPointsNumber, int& finishPointsNumber, Position& startPosition)
{
	int availableLength = line.length();
	if (availableLength > ROWS)
	{
		availableLength = ROWS;
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
			startPosition.column = lineIndex;
			startPosition.row = currElem;
		}
		labyrinth[lineIndex][currElem].symbol = symbol;
	}

	return true;
}

bool CheckStartAndEndPointNumbers(int startPointsNumber, int finishPointsNumber)
{
	const int EXPECTED_START_POINTS_NUMBER = 1;
	const int EXPECTED_FINISH_POINTS_NUMBER = 1;
	if ((startPointsNumber != EXPECTED_START_POINTS_NUMBER) ||
		(finishPointsNumber != EXPECTED_FINISH_POINTS_NUMBER))
	{
		std::cout << "The number of start " << startPointsNumber << " and end points " <<
			finishPointsNumber << " must be equal to " << EXPECTED_START_POINTS_NUMBER <<
			" and " << EXPECTED_FINISH_POINTS_NUMBER << " respectively\n";
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
	while (getline(input, line) && (++currLine < COLUMNS))
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

void AddQueue(std::vector<std::vector<FieldCell>>& labyrinth, Position pos,
	std::queue<Position>& queue, int mark)
{
	const int MIN_COLUMN_POSITION = 0;
	const int MIN_ROW_POSITION = 0;
	const int STANDARD_MARK = -1;
	if (pos.column >= MIN_COLUMN_POSITION && pos.column <= COLUMNS - 1 &&
		pos.row >= MIN_ROW_POSITION && pos.row <= ROWS - 1 &&
		labyrinth[pos.column][pos.row].symbol != WALL &&
		labyrinth[pos.column][pos.row].mark == STANDARD_MARK)
	{
		labyrinth[pos.column][pos.row].mark = ++mark;
		queue.push(pos);
	}
}

void MoveQueue(std::vector<std::vector<FieldCell>>& labyrinth, Position pos,
	std::queue<Position>& queue, int mark)
{
	const Position TOP_POS = { pos.column - 1, pos.row };
	AddQueue(labyrinth, TOP_POS, queue, mark);
	const Position BOTTOM_POS = { pos.column + 1, pos.row };
	AddQueue(labyrinth, BOTTOM_POS, queue, mark);
	const Position LEFT_POS = { pos.column, pos.row - 1 };
	AddQueue(labyrinth, LEFT_POS, queue, mark);
	const Position RIGHT_POS = { pos.column, pos.row + 1 };
	AddQueue(labyrinth, RIGHT_POS, queue, mark);
	queue.pop();
}

bool CheckWay(std::vector<std::vector<FieldCell>>& labyrinth, const Position& pos, int mark)
{
	const int MIN_COLUMN_POSITION = 0;
	const int MIN_ROW_POSITION = 0;
	if (pos.column >= MIN_COLUMN_POSITION && pos.column <= COLUMNS - 1 &&
		pos.row >= MIN_ROW_POSITION && pos.row <= ROWS - 1 &&
		labyrinth[pos.column][pos.row].mark == --mark)
	{
		return true;
	}
	return false;
}

void RestoreWay(std::vector<std::vector<FieldCell>>& labyrinth, Position& pos, int& mark)
{
	Position nextPos;
	const Position TOP_POS = { pos.column - 1, pos.row };
	if (CheckWay(labyrinth, TOP_POS, mark))
	{
		nextPos = TOP_POS;
	}
	const Position BOTTOM_POS = { pos.column + 1, pos.row };
	if (CheckWay(labyrinth, BOTTOM_POS, mark))
	{
		nextPos = BOTTOM_POS;
	}
	const Position LEFT_POS = { pos.column, pos.row - 1 };
	if (CheckWay(labyrinth, LEFT_POS, mark))
	{
		nextPos = LEFT_POS;
	}
	const Position RIGHT_POS = { pos.column, pos.row + 1 };
	if (CheckWay(labyrinth, RIGHT_POS, mark))
	{
		nextPos = RIGHT_POS;
	}
	pos = nextPos;
	mark = labyrinth[pos.column][pos.row].mark;
}

void FindWay(std::vector<std::vector<FieldCell>>& labyrinth,
	Position startPosition, Position& pos, int& mark)
{
	std::queue<Position> queue;
	queue.push(startPosition);

	while (!queue.empty())
	{
		pos = queue.front();
		mark = labyrinth[pos.column][pos.row].mark;
		if (labyrinth[pos.column][pos.row].symbol == FINISH_SYMBOL)
		{
			break;
		}
		MoveQueue(labyrinth, pos, queue, mark);
	}
}

void MarkWay(std::vector<std::vector<FieldCell>>& labyrinth,
	Position pos, int mark)
{
	while (mark != START_MARK)
	{
		RestoreWay(labyrinth, pos, mark);
		if (mark == START_MARK)
		{
			break;
		}
		const char WAY_SYMBOL = '.';
		labyrinth[pos.column][pos.row].symbol = WAY_SYMBOL;
	}
}

void FindAndMarkWay(std::vector<std::vector<FieldCell>>& labyrinth,
	Position startPosition)
{
	int mark = START_MARK;
	labyrinth[startPosition.column][startPosition.row].mark = mark;
	FieldCell cell;
	Position pos;

	FindWay(labyrinth, startPosition, pos, mark);

	if (labyrinth[pos.column][pos.row].symbol != FINISH_SYMBOL) 
	{
		return;
	}
	
	MarkWay(labyrinth, pos, mark);
}

int main(int argc, char* argv[])
{
	if (!CheckInputParametersNumber(argc))
	{
		return 1;
	}

	std::ifstream inputFile(argv[1]);
	if (!CheckOpenFile(inputFile, argv[1]))
	{
		return 2;
	}

	Position startPosition;
	std::vector<std::vector<FieldCell>> labyrinth(ROWS, std::vector<FieldCell>(COLUMNS));
	if (!GetLabyrinth(inputFile, labyrinth, startPosition))
	{
		return 3;
	}

	FindAndMarkWay(labyrinth, startPosition);

	std::ofstream outputFile(argv[2]);
	PrintLabyrinth(outputFile, labyrinth);

	return 0;
}