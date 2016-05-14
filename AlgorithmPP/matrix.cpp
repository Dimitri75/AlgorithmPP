#include "stdafx.h"
#include "matrix.h"

#define CUT 8
const int MAX = 99;

int& Matrix::operator()(unsigned col, unsigned row) {
	return grid[col][row];
}

Matrix* Matrix::operator+(Matrix const &mat){
	return addition(*this, mat);
}

Matrix* Matrix::operator-(Matrix const &mat){
	return substraction(*this, mat);
}

Matrix* Matrix::operator*(Matrix const &mat){
	return multiplication(*this, mat);
}

Matrix::Matrix(Matrix const &mat){
	n = mat.n;
	grid = mat.grid;
}

Matrix::Matrix(bool fil, int _n) : n(_n)
{
	initGrid(fil);
}

Matrix::Matrix(Matrix topLeftCorner, Matrix topRightCorner, Matrix botLeftCorner, Matrix botRightCorner)
{
	n = topLeftCorner.getOrder() * 2;
	initGrid(false);

	for (int column = 0; column < n; column++)
		for (int row = 0; row < n; row++)
			if (column < n / 2 && row < n / 2)
				grid[column][row] = topLeftCorner(column, row);

			else if (column < n / 2 && row >= n / 2)
				grid[column][row] = topRightCorner(column, n / 2 + row);

			else if (column >= n / 2 && row < n / 2)
				grid[column][row] = botLeftCorner(n / 2 + column, row);

			else if (column >= n / 2 && row >= n / 2)
				grid[column][row] = botRightCorner(n / 2 + column, n / 2 + row);
}

Matrix::~Matrix(void)
{
	/*if (grid != nullptr){
		for (int i = 0; i < n; i++)
			delete[] grid[i];
		delete[] grid;
	}*/
}

const int Matrix::getOrder(){
	return n;
}

int** Matrix::getGrid() {
	return grid;
}

int random(int max, int min = 0){
	random_device seeder;
	mt19937 engine(seeder());
	uniform_int_distribution<int> dist(min, max);
	return dist(engine);
}

void Matrix::initGrid(bool fil){
	int order = n % 2 == 0 ? n : n + 1;

	grid = new int*[order];

	int column, line;
	for (column = 0; column < n; column++){
		grid[column] = new int[order];

		for (line = 0; line < n; line++){
			grid[column][line] = fil ? random(MAX) : 0;
		}
	}

	if (order != n){
		grid[column] = new int[order];
		for (int i = 0; i < order; i++){
			grid[column][i] = 0;
			grid[i][line] = 0;
		}
		n = order;
	}
}

void Matrix::print(std::string name){
	cout << "Print Matrix " << name << endl;
	for (int column = 0; column < n; column++){
		for (int line = 0; line < n; line++){
			cout << "" << grid[column][line] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

Matrix* Matrix::addition(Matrix a, Matrix b){
	return operation(ADDITION, a, b);
}

Matrix* Matrix::substraction(Matrix a, Matrix b){
	return operation(SUBSTRACTION, a, b);
}

Matrix* Matrix::multiplication(Matrix a, Matrix b){
	return operation(MULTIPLICATION, a, b);
}

Matrix* Matrix::operation(Operation operation, Matrix a, Matrix b){
	if (a.getOrder() != b.getOrder())
		return nullptr;

	Matrix *c = new Matrix(false, a.getOrder());
	for (int column = 0; column < a.getOrder(); column++){
		for (int line = 0; line < a.getOrder(); line++){
			switch (operation)
			{
				case Matrix::ADDITION:
					(*c)(column, line) = a(column, line) + b(column, line);
					break;
				case Matrix::SUBSTRACTION:
					(*c)(column, line) = a(column, line) - b(column, line);
					break;
				case Matrix::MULTIPLICATION:
					for (int o = 0; o < a.getOrder(); o++)
						(*c)(column, line) += a.getGrid()[column][o] * b.getGrid()[o][line];
					break;
				default:
					break;
			}
		}
	}

	return c;
}

Matrix* Matrix::hadamard(Matrix a, Matrix b){
	if (a.getOrder() != b.getOrder())
		return nullptr;

	Matrix *c = new Matrix(false, a.getOrder());
	for (int column = 0; column < a.getOrder(); column++){
		for (int line = 0; line < a.getOrder(); line++){
			c->getGrid()[column][line] += a.getGrid()[column][line] * b.getGrid()[column][line];
		}
	}

	return c;
}

Matrix* Matrix::strassen(Matrix a, Matrix b){
	if (a.getOrder() <= CUT)
		return a * b;

	Matrix topLeftA (a.getCorner(Matrix::TOP_LEFT));
	Matrix topRightA (a.getCorner(Matrix::TOP_RIGHT));
	Matrix botLeftA (a.getCorner(Matrix::BOT_LEFT));
	Matrix botRightA (a.getCorner(Matrix::BOT_RIGHT));

	Matrix topLeftB (b.getCorner(Matrix::TOP_LEFT));
	Matrix topRightB (b.getCorner(Matrix::TOP_RIGHT));
	Matrix botLeftB (b.getCorner(Matrix::BOT_LEFT));
	Matrix botRightB (b.getCorner(Matrix::BOT_RIGHT));

	Matrix m1 (strassen(topLeftA + botRightA, topLeftB + botRightB));
	Matrix m2 (strassen(botLeftA + botRightA, topLeftB));
	Matrix m3 (strassen(topLeftA, topRightB - botRightB));
	Matrix m4 (strassen(botRightA, botLeftB - topLeftB));
	Matrix m5 (strassen(topLeftA + topRightA, botRightB));
	Matrix m6 (strassen(botLeftA - topLeftA, topLeftB + topRightB));
	Matrix m7 (strassen(topRightA - botRightA, botLeftB + botRightB));

	Matrix tl ((m1 + m4) - (m5 + m7));
	Matrix tr (m3 + m5);
	Matrix bl (m2 + m4);
	Matrix br (*(m1 - m2) + (m3 + m6));

	Matrix* c = new Matrix(tl, tr, bl, br);

	return c;
}

Matrix* Matrix::getCorner(Position position) {
	Matrix* corner = new Matrix(false, n / 2);

	switch (position)
	{
	case TOP_LEFT: {
		for (int column = 0; column < corner->getOrder(); column++)
			for (int line = 0; line < corner->getOrder(); line++)
				(*corner)(column, line) = grid[column][line];

		break;
	}
	case TOP_RIGHT: {
		for (int column = 0; column < corner->getOrder(); column++)
			for (int line = corner->getOrder(); line < n; line++)
				(*corner)(column, line % corner->getOrder()) = grid[column][line];

		break;
	}
	case BOT_LEFT: {
		for (int column = corner->getOrder(); column < n; column++)
			for (int line = 0; line < corner->getOrder(); line++)
				(*corner)(column % corner->getOrder(), line) = grid[column][line];

		break;
	}
	case BOT_RIGHT: {
		for (int column = corner->getOrder(); column < n; column++)
			for (int line = corner->getOrder(); line < n; line++)
				(*corner)(column % corner->getOrder(), line % corner->getOrder()) = grid[column][line];

		break;
	}
	default:
		break;
	}

	return corner;
}
