// AlgorithmPP.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"

using namespace std;

Matrix* operator*(Matrix const &a, Matrix const &b){
	return Matrix::strassen(a, b);
}

void strassen(){
	int order = 20;

	Matrix *A = new Matrix(true, order);
	Matrix *B = new Matrix(true, order);
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

void karatsuba() {
	int a[BigInt::MAX], b[BigInt::MAX];
	int r[6 * BigInt::MAX
	];
	int d_a, d_b;
	int d = 1;

	BigInt::getNum(a, &d_a);
	BigInt::getNum(b, &d_b);

	if (d_a < 0 || d_b < 0) {
		cout << 0 << endl;
		exit(0);
		return;
	}

	int i = (d_a > d_b) ? d_a : d_b;

	while (d < i)
		d *= 2;

	for (i = d_a; i < d; i++)
		a[i] = 0;

	for (i = d_b; i < d; i++)
		b[i] = 0;

	BigInt::karatsuba(a, b, r, d);
	BigInt::doCarry(r, 2 * d);
	BigInt::printNum(r, 2 * d);
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
	return 0;
}