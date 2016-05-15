#include "stdafx.h"
#include "matrix.h"

#define CUT 4
const int MAX = 99;

int& Matrix::operator()(unsigned row, unsigned col) {
	return grid[row][col];
}

Matrix Matrix::operator+(Matrix &mat){
	return *(addition(*this, mat));
}

Matrix Matrix::operator-(Matrix &mat){
	return *(substraction(*this, mat));
}

Matrix Matrix::operator*(Matrix &mat){
	return *(strassen(*this, mat));
}

Matrix::Matrix(Matrix const &mat){
	n = mat.n;
	order = mat.order;
	grid = mat.grid;
}

Matrix::Matrix(bool fil, int _n) : n(_n)
{
	initGrid(fil);
}

Matrix::Matrix(Matrix topLeftCorner, Matrix topRightCorner, Matrix botLeftCorner, Matrix botRightCorner, int _order)
{
	int cornerOrder = topLeftCorner.getOrder();
	n = cornerOrder * 2;
	initGrid(false);
	order = _order;

	for (int row = 0; row < cornerOrder; row++)
		for (int column = 0; column < cornerOrder; column++)
				grid[row][column] = topLeftCorner(row, column);

	for (int row = 0; row < cornerOrder; row++)
		for (int column = cornerOrder; column < n; column++)
			grid[row][column] = topRightCorner(row, column % cornerOrder);

	for (int row = cornerOrder; row < n; row++)
		for (int column = 0; column < cornerOrder; column++)
			grid[row][column] = botLeftCorner(row % cornerOrder, column);

	for (int row = cornerOrder; row < n; row++)
		for (int column = cornerOrder; column < n; column++)
			grid[row][column] = botRightCorner(row % cornerOrder, column % cornerOrder);
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
	order = n;

	n = 1;
	while (n < order)
		n *= 2;

	grid = new int*[n];
	int row, column;
	for (row = 0; row < order; row++){
		grid[row] = new int[n];

		for (column = 0; column < order; column++){
			grid[row][column] = fil ? random(MAX) : 0;
		}
	}

	if (order != n){
		for (int i = row; i < n; i++)
			grid[i] = new int[n];

		for (; row < n; row++){
			for (int c = 0; c < n; c++){
				grid[row][c] = 0;
				grid[c][row] = 0;
			}
		}
	}
}

void Matrix::print(std::string name){
	cout << "Print Matrix " << name << endl;
	for (int row = 0; row < order; row++){
		for (int column = 0; column < order; column++){
			cout << "" << grid[row][column] << "\t";
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

Matrix* Matrix::multiplies(Matrix &mat){
	return multiplication(*this, mat);
}

Matrix* Matrix::operation(Operation operation, Matrix a, Matrix b){
	if (a.getOrder() != b.getOrder())
		return nullptr;

	Matrix *c = new Matrix(false, a.getOrder());
	for (int row = 0; row < a.getOrder(); row++){
		for (int column = 0; column < a.getOrder(); column++){
			switch (operation)
			{
				case Matrix::ADDITION:
					(*c)(row, column) = a(row, column) + b(row, column);
					break;
				case Matrix::SUBSTRACTION:
					(*c)(row, column) = a(row, column) - b(row, column);
					break;
				case Matrix::MULTIPLICATION:
					for (int o = 0; o < a.getOrder(); o++)
						(*c)(row, column) += a(row, o) * b(o, column);
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
	for (int row = 0; row < a.getOrder(); row++){
		for (int column = 0; column < a.getOrder(); column++){
			c->getGrid()[row][column] += a.getGrid()[row][column] * b.getGrid()[row][column];
		}
	}

	return c;
}


Matrix* Matrix::strassen(Matrix a, Matrix b){
	if (a.getOrder() <= CUT)
		return multiplication(a, b);

	Matrix a11 (*a.getCorner(Matrix::TOP_LEFT));
	Matrix a12 (*a.getCorner(Matrix::TOP_RIGHT));
	Matrix a21 (*a.getCorner(Matrix::BOT_LEFT));
	Matrix a22 (*a.getCorner(Matrix::BOT_RIGHT));

	Matrix b11 (*b.getCorner(Matrix::TOP_LEFT));
	Matrix b12 (*b.getCorner(Matrix::TOP_RIGHT));
	Matrix b21 (*b.getCorner(Matrix::BOT_LEFT));
	Matrix b22 (*b.getCorner(Matrix::BOT_RIGHT));

	Matrix m1 = (a11 + a22) * (b11 + b22);
	Matrix m2 = (a21 + a22) * b11;
	Matrix m3 = a11 * (b12 - b22);
	Matrix m4 = a22 * (b21 - b11);
	Matrix m5 = (a11 + a12) * b22;
	Matrix m6 = (a21 - a11) * (b11 + b12);
	Matrix m7 = (a12 - a22) * (b21 + b22);

	Matrix c11 = m1 + m4 - m5 + m7;
	Matrix c12 = m3 + m5;
	Matrix c21 = m2 + m4;
	Matrix c22 = m1 - m2 + m3 + m6;

	return new Matrix(c11, c12, c21, c22, a.order);
}

Matrix* Matrix::getCorner(Position position) {
	int order = n / 2;
	Matrix* corner = new Matrix(false, order);

	switch (position)
	{
	case TOP_LEFT: {
		for (int row = 0; row < order; row++)
			for (int column = 0; column < order; column++)
				(*corner)(row, column) = grid[row][column];

		break;
	}
	case TOP_RIGHT: {
		for (int row = 0; row < order; row++)
			for (int column = order; column < n; column++)
				(*corner)(row, column % order) = grid[row][column];

		break;
	}
	case BOT_LEFT: {
		for (int row = order; row < n; row++)
			for (int column = 0; column < order; column++)
				(*corner)(row % order, column) = grid[row][column];

		break;
	}
	case BOT_RIGHT: {
		for (int row = order; row < n; row++)
			for (int column = order; column < n; column++)
				(*corner)(row % order, column % order) = grid[row][column];

		break;
	}
	default:
		break;
	}

	return corner;
}
