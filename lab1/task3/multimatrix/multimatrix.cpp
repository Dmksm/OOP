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

//лучше копировать в результирующую матрицу а не возвращать с копированием так быстрее
std::vector<std::vector<double>> MultiplyMatrices(
	const std::vector<std::vector<double>>& matrix1, 
	const std::vector<std::vector<double>>& matrix2)
{
	std::vector<std::vector<double>> resultMatrix(matrixSize, std::vector<double>(matrixSize)); //если уверен то можно не предполагать какая размер матрицы
	for (size_t currRow = 0; currRow < resultMatrix.size(); currRow++)
	{
		for (size_t currColumn = 0; currColumn < resultMatrix[currRow].size(); currColumn++)
		{
			resultMatrix[currRow][currColumn] = 
				getMatrixCellValue(matrix1, matrix2, currRow, currColumn); 
		}
	}
	return resultMatrix;
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
		output << "\n"; // использовать std::endl так как больше поддерживается чем \n
	}
}

int main(int argc, char* argv[])
{
	if (!CheckInputParametersNumber(argc))
	{
		return 1;
	}
	std::ifstream inputFile1(argv[1]);
	if (!CheckOpenFile(inputFile1, argv[1])) // возвращаем либо 0 либо 1, сейчас не очень актуально разделять
	{
		return 2;
	}
	std::ifstream inputFile2(argv[2]);
	if (!CheckOpenFile(inputFile2, argv[2]))
	{
		return 3;
	}
	std::vector<std::vector<double>> matrix1(matrixSize, std::vector<double>(matrixSize));
	ReadMatrix(matrix1, inputFile1);
	std::vector<std::vector<double>> matrix2(matrixSize, std::vector<double>(matrixSize));
	ReadMatrix(matrix2, inputFile2);
	PrintMatrix(MultiplyMatrices(matrix1, matrix2), std::cout);
	return 0;
}