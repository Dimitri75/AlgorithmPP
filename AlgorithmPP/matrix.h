#pragma once
class Matrix
{
	public:
		Matrix(Matrix const&);
		Matrix(bool fil = false, int _n = 4);
		~Matrix(void);

		const int getOrder();
		int** getGrid();
		void print(std::string name = "");
		static Matrix* addition(Matrix, Matrix);
		static Matrix* substraction(Matrix, Matrix);
		static Matrix* multiplication(Matrix, Matrix);
		static Matrix* hadamard(Matrix, Matrix);
		static Matrix* strassen(Matrix, Matrix);

		Matrix operator+(Matrix &);
		Matrix operator-(Matrix &);
		Matrix operator*(Matrix &);
		int& operator()(unsigned row, unsigned col);
		int operator()(unsigned row, unsigned col) const;

	private:
		enum Position { TOP_LEFT, TOP_RIGHT, BOT_LEFT, BOT_RIGHT };
		enum Operation { ADDITION, SUBSTRACTION, MULTIPLICATION }; Matrix(Matrix topLeftCorner, Matrix topRightCorner, Matrix botLeftCorner, Matrix botRightCorner, int _order);
		int n, order;
		int **grid;
		void initGrid(bool fil);
		Matrix* multiplies(Matrix &mat);
		Matrix* getCorner(Position);
		static Matrix* operation(Operation, Matrix, Matrix);

};

