#include "stdafx.h";

#pragma once
class Matrix
{
	public:
		enum Position { TOP_LEFT, TOP_RIGHT, BOT_LEFT, BOT_RIGHT };
		enum Operation { ADDITION, SUBSTRACTION, MULTIPLICATION };

		Matrix(Matrix const&);
		Matrix(bool fil = false, int _n = 4);
		Matrix(Matrix topLeftCorner, Matrix topRightCorner, Matrix botLeftCorner, Matrix botRightCorner);
		~Matrix(void);

		const int getOrder();
		int** getGrid();
		Matrix* getCorner(Position);
		void print(std::string name = "");
		static Matrix* operation(Operation, Matrix, Matrix);
		static Matrix* addition(Matrix, Matrix);
		static Matrix* substraction(Matrix, Matrix);
		static Matrix* multiplication(Matrix, Matrix);
		static Matrix* hadamard(Matrix, Matrix);
		static Matrix* strassen(Matrix, Matrix);

		Matrix* operator+(Matrix const&);
		Matrix* operator-(Matrix const&);
		Matrix* operator*(Matrix const&);
		int& operator()(unsigned row, unsigned col);
		int operator()(unsigned row, unsigned col) const;

	private:
		int n;
		int **grid;
		Matrix* gridTopLeft;
		Matrix* gridTopRight;
		Matrix* gridBottomLeft;
		Matrix* gridBottomRight;
		void initGrid(bool fil);
		void initGrids(bool fil);
};

