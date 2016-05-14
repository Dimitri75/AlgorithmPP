// AlgorithmPP.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"

using namespace std;

const int ORDER = 20;
chrono::time_point<chrono::system_clock> start;
chrono::time_point<chrono::system_clock> stop;

Matrix* operator*(Matrix const &a, Matrix const &b){
	return Matrix::strassen(a, b);
}

void strassen(){
	Matrix *A = new Matrix(true, ORDER);
	Matrix *B = new Matrix(true, ORDER);
	A->print("A");
	B->print("B");

	Matrix *C = (*A) * (*B);
	C->print("C = A * B (using strassen algorithm)");
}

void mergeSort(){
	int input[] = { 5, 9, 1, 3, 8 };
	cout << input << endl;

	Merge::sort(input, 5);
	cout << input << endl;
}

int karatsuba() {
	int a[BigInt::MAX], b[BigInt::MAX];
	int r[6 * BigInt::MAX];
	int d_a, d_b;
	int d = 1;
	clock_t start;
	clock_t stop;

	BigInt::getNum(a, &d_a);
	BigInt::getNum(b, &d_b);

	if (d_a < 0 || d_b < 0) {
		cout << 0 << endl;
		exit(0);
		return 0;
	}

	int i = (d_a > d_b) ? d_a : d_b;

	while (d < i)
		d *= 2;

	for (i = d_a; i < d; i++)
		a[i] = 0;

	for (i = d_b; i < d; i++)
		b[i] = 0;
	
	// Karatsuba
	start = clock();
	stop = start + CLOCKS_PER_SEC;
	for (i = 0; clock() < stop; i++) {
		BigInt::karatsuba(a, b, r, d);
		BigInt::doCarry(r, 2 * d);
	}
	start = clock() - start;
	BigInt::printNum(r, 2 * d);
	cout << "Karatsuba\t" << 1000 * (double)start / CLOCKS_PER_SEC / i << "\t(" << i << " trials)" << endl << endl;

	// Standard
	start = clock();
	stop = start + CLOCKS_PER_SEC;
	for (i = 0; clock() < stop; i++) {
		BigInt::multiplication(a, b, r, d);
		BigInt::doCarry(r, 2 * d);
	}
	start = clock() - start;
	BigInt::printNum(r, 2 * d);
	cout << "Standard\t" << 1000 * (double)start / CLOCKS_PER_SEC / i << "\t(" << i << " trials)" << endl << endl;
}

int _tmain(int argc, _TCHAR* argv[]){
	std::cout << "TP1 - Dimitri BUHON" << std::endl;
	int input = -1;

	while (input != 0){
		cout << endl << "Choisir une option (1, 2, 3 ou 0 pour quitter) : ";
		cin >> input;

		switch (input)
		{
		case 0:
			break;
		case 1:
			cout << endl << endl << "Exercice 1 : Strassen" << endl;
			strassen();
			break;
		case 2:
			cout << endl << endl << "Exercice 2 : Tri" << endl;
			//mergeSort();
			break;
		case 3:
			cout << endl << endl << "Exercice 3 : Karatsuba" << endl;
			karatsuba();
			break;
		default:
			break;
		}
	}

	system("pause");
	return 0;
}