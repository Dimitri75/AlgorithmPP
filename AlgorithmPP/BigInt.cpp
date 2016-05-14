#include "stdafx.h"
#include "BigInt.h"

#define CUT 4

void BigInt::operator*(const int &b){

}

BigInt::BigInt()
{
}


BigInt::~BigInt()
{
}

void BigInt::karatsuba(int *a, int *b, int *ret, int d) {
	int *ar = &a[0];
	int *al = &a[d / 2];
	int *br = &b[0];
	int *bl = &b[d / 2];
	int *asum = &ret[d * 5];
	int *bsum = &ret[d * 5 + d / 2];
	int *x1 = &ret[d * 0];
	int *x2 = &ret[d * 1];
	int *x3 = &ret[d * 2];

	if (d <= CUT) {
		multiplication(a, b, ret, d);
		return;
	}

	for (int i = 0; i < d / 2; i++) {
		asum[i] = al[i] + ar[i];
		bsum[i] = bl[i] + br[i];
	}

	karatsuba(ar, br, x1, d / 2);
	karatsuba(al, bl, x2, d / 2);
	karatsuba(asum, bsum, x3, d / 2);

	for (int i = 0; i < d; i++) 
		x3[i] = x3[i] - x1[i] - x2[i];

	for (int i = 0; i < d; i++)
		ret[i + d / 2] += x3[i];
}

void BigInt::multiplication(int *a, int *b, int *ret, int d) {
	for (int i = 0; i < 2 * d; i++) 
		ret[i] = 0;

	for (int i = 0; i < d; i++) {
		for (int j = 0; j < d; j++) 
			ret[i + j] += a[i] * b[j];
	}
}

void BigInt::doCarry(int *a, int d) {
	int c = 0;

	for (int i = 0; i < d; i++) {
		a[i] += c;

		if (a[i] < 0)
			c = -(-(a[i] + 1) / 10 + 1);
		else
			c = a[i] / 10;

		a[i] -= c * 10;
	}

	if (c != 0)
		cout << stderr << " Overflow " << c << endl;
}

void BigInt::getNum(int *a, int *d_a) {
	string input;
	int c = 0;
	*d_a = 0;
	cout << "Entrez un nombre : ";
	while (!(cin >> input))
	{
		cerr << "Erreur de saisie" << endl;
		cout << "Nombre : ";
	}

	for (int ch : input){
		if (c >= MAX){
			cout << "Keeping only the first 1024 digits" << endl << endl;
			break;
		}

		a[*d_a] = ch - '0';
		++(*d_a);
		c++;
	}

	for (int i = 0; i * 2 < *d_a - 1; i++) {
		c = a[i];
		a[i] = a[*d_a - i - 1];
		a[*d_a - i - 1] = c;
	}
}

void BigInt::printNum(int *a, int d) {
	int i;
	for (i = d - 1; i > 0; i--) 
		if (a[i] != 0) 
			break;

	for (; i >= 0; i--)
		cout << a[i];
	cout << endl;
}