// AlgorithmPP.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"

using namespace std;

const int ORDER = 20;
chrono::time_point<chrono::system_clock> start;
chrono::time_point<chrono::system_clock> stop;

matrix* operator*(matrix const &a, matrix const &b){
	return matrix::strassen(a, b);
}

void strassen(){
	matrix *A = new matrix(true, ORDER);
	matrix *B = new matrix(true, ORDER);
	//A->print("A");
	//B->print("B");

	//int strassen, standard;
	//start = chrono::system_clock::now();
	matrix *C = (*A) * (*B);
	//stop = std::chrono::system_clock::now();
	//strassen = chrono::duration_cast<chrono::microseconds> (stop - start).count();
	C->print("C strassen");

	//start = chrono::system_clock::now();
	//matrix *D = matrix::multiplication(*A, *B);
	//stop = std::chrono::system_clock::now();
	//standard = chrono::duration_cast<chrono::microseconds> (stop - start).count();
	//D->print("D standard");

	//cout << "Standard (microseconds) : " << standard << endl;
	//cout << "Strassen (microseconds) : " << strassen << endl;

}

void mergeSort(){
	int input[] = { 5, 9, 1, 3, 8 };
	cout << input << endl;

	merge::sort(input, 5);
	cout << input << endl;
}

int _tmain(int argc, _TCHAR* argv[]){
	std::cout << "TP1 - Dimitri BUHON" << std::endl;



	strassen();
	//mergeSort();

	system("pause");
}