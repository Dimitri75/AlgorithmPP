// AlgorithmPP.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"

using namespace std;

const int ORDER = 30;

void strassen(){
	Matrix *a = new Matrix(true, ORDER);
	Matrix *b = new Matrix(true, ORDER);
	a->print("A");
	b->print("B");

	Matrix c = (*a) * (*b);
	c.print("C = A * B (using strassen algorithm)");

	//Matrix::multiplication(*a, *b)->print("STANDARD");
}

void mergeSort(){
	int input[] = { 5, 9, 1, 3, 8 };
	cout << input << endl;

	Merge::sort(input, 5);
	cout << input << endl;
}

void karatsuba() {
	BigInt *a = new BigInt;
	BigInt *b = new BigInt;

	(*a) * (*b);
}

int _tmain(int argc, _TCHAR* argv[]){
	std::cout << "TP1 - Dimitri BUHON" << std::endl;
	string input;
	while (input != "0"){
		cout << endl << "Choisir une option (1, 2, 3 ou 0 pour quitter) : ";
		cin >> input;

		if (input == "1"){
			cout << endl << endl << "Exercice 1 : Strassen" << endl;
			strassen();
		}
		else if (input == "2"){
			cout << endl << endl << "Exercice 2 : Tri" << endl;
			//mergeSort();
		}
		else if (input == "3"){
			cout << endl << endl << "Exercice 3 : Karatsuba" << endl;
			karatsuba();
		}
	}

	return 0;
}