#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>

const int matrixSize = 3; //именование в MATRIX_SIZE, constexpr - для вычисления значений во время компиляции -> быстрее

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

void ReadMatrix(std::vector<std::vector<double>>& matrix, std::istream& input)
{
	double number;
	int row = 0, column = 0;
	while (input >> number)
	{
		matrix[row % matrixSize][column % matrixSize] = number;
		if ((++column % matrixSize) == 0) //проверка на 3 на 3 размерность
		{
			row++;
		}
	}
}

double getMatrixCellValue(const std::vector<std::vector<double>>& matrix1, 
	const std::vector<std::vector<double>>& matrix2, int row, int column)
{
	double result = 0;
	int count = -1;
	const int digitCount = 3;
	while (++count < matrixSize)
	{
		double val = matrix1[row][count] * matrix2[count][column];
		result += round(val * pow(10, digitCount)) / pow(10, digitCount); //округление при выводе а хранить точное использовать set precision
	}
	return result;
}

void MultiplyMatrices(
	const std::vector<std::vector<double>>& matrix1, 
	const std::vector<std::vector<double>>& matrix2,
	std::vector<std::vector<double>>& resultMatrix
)
{
	for (size_t currRow = 0; currRow < matrixSize; currRow++)
	{
		for (size_t currColumn = 0; currColumn < matrixSize; currColumn++)
		{
			resultMatrix[currRow][currColumn] = 
				getMatrixCellValue(matrix1, matrix2, currRow, currColumn); 
		}
	}
}

void PrintMatrix(const std::vector<std::vector<double>>& matrix, std::ostream& output)
{
	const int digitNumber = 3;
	for (std::vector<double> row : matrix)
	{
		for (double column : row)
		{
			output << column << "      "; // set fixed и precision разобраться для выода опред кол знаков
		}
		output << std::endl;
	}
}

int main(int argc, char* argv[])
{
	if (!CheckInputParametersNumber(argc))
	{
		return 1;
	}

	std::ifstream inputFile1(argv[1]);
	if (!CheckOpenFile(inputFile1, argv[1]))
	{
		return 1;
	}

	std::ifstream inputFile2(argv[2]);
	if (!CheckOpenFile(inputFile2, argv[2]))
	{
		return 1;
	}

	std::vector<std::vector<double>> matrix1(matrixSize, std::vector<double>(matrixSize));
	ReadMatrix(matrix1, inputFile1);

	std::vector<std::vector<double>> matrix2(matrixSize, std::vector<double>(matrixSize));
	ReadMatrix(matrix2, inputFile2);

	std::vector<std::vector<double>> resultMatrix(matrixSize, std::vector<double>(matrixSize));
	MultiplyMatrices(matrix1, matrix2, resultMatrix);

	PrintMatrix(resultMatrix, std::cout);
	return 0;
}