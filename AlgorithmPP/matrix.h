#include "stdafx.h";

#pragma once
class matrix
{
	public:
		enum Position { TOP_LEFT, TOP_RIGHT, BOT_LEFT, BOT_RIGHT };
		enum Operation { ADDITION, SUBSTRACTION, MULTIPLICATION };

		matrix(matrix const&);
		matrix(bool fil = false, int _n = 4);
		matrix(matrix topLeftCorner, matrix topRightCorner, matrix botLeftCorner, matrix botRightCorner);
		~matrix(void);

		const int getOrder();
		int** getGrid();
		matrix* getCorner(Position);
		void print(std::string name = "");
		static matrix* operation(Operation, matrix, matrix);
		static matrix* addition(matrix, matrix);
		static matrix* substraction(matrix, matrix);
		static matrix* multiplication(matrix, matrix);
		static matrix* hadamard(matrix, matrix);
		static matrix* strassen(matrix, matrix);

		matrix* operator+(matrix const&);
		matrix* operator-(matrix const&);
		matrix* operator*(matrix const&);
		int& operator()(unsigned row, unsigned col);
		int operator()(unsigned row, unsigned col) const;

	private:
		int n;
		int **grid;
		matrix* gridTopLeft;
		matrix* gridTopRight;
		matrix* gridBottomLeft;
		matrix* gridBottomRight;
		void initGrid(bool fil);
		void initGrids(bool fil);
};

