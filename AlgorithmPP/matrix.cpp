#include "stdafx.h"
#include "matrix.h"

const int CUT = 8;
const int MAX = 99;

int& matrix::operator()(unsigned col, unsigned row) {
	return grid[col][row];
}

matrix* matrix::operator+(matrix const &mat){
	return addition(*this, mat);
}

matrix* matrix::operator-(matrix const &mat){
	return substraction(*this, mat);
}

matrix* matrix::operator*(matrix const &mat){
	return multiplication(*this, mat);
}

matrix::matrix(matrix const &mat){
	n = mat.n;
	grid = mat.grid;
}

matrix::matrix(bool fil, int _n) : n(_n)
{
	initGrid(fil);
}

matrix::matrix(matrix topLeftCorner, matrix topRightCorner, matrix botLeftCorner, matrix botRightCorner)
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

matrix::~matrix(void)
{
	/*if (grid != nullptr){
		for (int i = 0; i < n; i++)
			delete[] grid[i];
		delete[] grid;
	}*/
}

const int matrix::getOrder(){
	return n;
}

int** matrix::getGrid() {
	return grid;
}

int random(int max, int min = 0){
	random_device seeder;
	mt19937 engine(seeder());
	uniform_int_distribution<int> dist(min, max);
	return dist(engine);
}

void matrix::initGrid(bool fil){
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

void matrix::print(std::string name){
	cout << "Print Matrix " << name << endl;
	for (int column = 0; column < n; column++){
		for (int line = 0; line < n; line++){
			cout << "" << grid[column][line] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

matrix* matrix::addition(matrix a, matrix b){
	return operation(ADDITION, a, b);
}

matrix* matrix::substraction(matrix a, matrix b){
	return operation(SUBSTRACTION, a, b);
}

matrix* matrix::multiplication(matrix a, matrix b){
	return operation(MULTIPLICATION, a, b);
}

matrix* matrix::operation(Operation operation, matrix a, matrix b){
	if (a.getOrder() != b.getOrder())
		return nullptr;

	matrix *c = new matrix(false, a.getOrder());
	for (int column = 0; column < a.getOrder(); column++){
		for (int line = 0; line < a.getOrder(); line++){
			switch (operation)
			{
				case matrix::ADDITION:
					(*c)(column, line) = a(column, line) + b(column, line);
					break;
				case matrix::SUBSTRACTION:
					(*c)(column, line) = a(column, line) - b(column, line);
					break;
				case matrix::MULTIPLICATION:
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

matrix* matrix::hadamard(matrix a, matrix b){
	if (a.getOrder() != b.getOrder())
		return nullptr;

	matrix *c = new matrix(false, a.getOrder());
	for (int column = 0; column < a.getOrder(); column++){
		for (int line = 0; line < a.getOrder(); line++){
			c->getGrid()[column][line] += a.getGrid()[column][line] * b.getGrid()[column][line];
		}
	}

	return c;
}

matrix* matrix::strassen(matrix a, matrix b){
	if (a.getOrder() <= CUT)
		return a * b;

	matrix topLeftA (a.getCorner(matrix::TOP_LEFT));
	matrix topRightA (a.getCorner(matrix::TOP_RIGHT));
	matrix botLeftA (a.getCorner(matrix::BOT_LEFT));
	matrix botRightA (a.getCorner(matrix::BOT_RIGHT));

	matrix topLeftB (b.getCorner(matrix::TOP_LEFT));
	matrix topRightB (b.getCorner(matrix::TOP_RIGHT));
	matrix botLeftB (b.getCorner(matrix::BOT_LEFT));
	matrix botRightB (b.getCorner(matrix::BOT_RIGHT));

	matrix m1 (strassen(topLeftA + botRightA, topLeftB + botRightB));
	matrix m2 (strassen(botLeftA + botRightA, topLeftB));
	matrix m3 (strassen(topLeftA, topRightB - botRightB));
	matrix m4 (strassen(botRightA, botLeftB - topLeftB));
	matrix m5 (strassen(topLeftA + topRightA, botRightB));
	matrix m6 (strassen(botLeftA - topLeftA, topLeftB + topRightB));
	matrix m7 (strassen(topRightA - botRightA, botLeftB + botRightB));

	matrix tl ((m1 + m4) - (m5 + m7));
	matrix tr (m3 + m5);
	matrix bl (m2 + m4);
	matrix br (*(m1 - m2) + (m3 + m6));

	matrix* c = new matrix(tl, tr, bl, br);

	return c;
}

matrix* matrix::getCorner(Position position) {
	matrix* corner = new matrix(false, n / 2);

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
