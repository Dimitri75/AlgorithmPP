#include "stdafx.h"
#include "BigInt.h"

#define CUT 4

int* BigInt::operator()(unsigned const& i){
	return &value[i];
}

void BigInt::operator*(BigInt &nb){
	karatsuba(*this, nb);
}

BigInt::BigInt()
{
	value = new int[MAX];
	getNum(value, &d_value);
}

BigInt::BigInt(int* _value){
	value = _value;
}


BigInt::~BigInt()
{
	delete[] value;
}

void BigInt::karatsuba(BigInt &nb){
	karatsuba(*this, nb);
}

void BigInt::karatsuba(BigInt &a, BigInt &b){
	int d = 1;
	int r[6 * BigInt::MAX];

	if (a.d_value < 0 || b.d_value < 0) {
		cout << 0 << endl;
		exit(0);
		return;
	}

	int i = (a.d_value > b.d_value) ? a.d_value : b.d_value;

	while (d < i)
		d *= 2;

	for (i = a.d_value; i < d; i++)
		a.value[i] = 0;

	for (i = b.d_value; i < d; i++)
		b.value[i] = 0;

	// Karatsuba
	BigInt::karatsubaHelper(a, b, r, d);
	BigInt::doCarry(r, 2 * d);
	BigInt::printNum(r, 2 * d);
}

void BigInt::karatsubaHelper(BigInt &a, BigInt &b, int *ret, int d) {
	if (d <= CUT) {
		multiplication(a.value, b.value, ret, d);
		return;
	}

	BigInt *ar = new BigInt(a(0));
	BigInt *al = new BigInt(a(d / 2));
	BigInt *br = new BigInt(b(0));
	BigInt *bl = new BigInt(b(d / 2));

	BigInt *asum = new BigInt(&ret[d * 5]);
	BigInt *bsum = new BigInt(&ret[d * 5 + d / 2]);

	int *x1 = &ret[d * 0];
	int *x2 = &ret[d * 1];
	int *x3 = &ret[d * 2];

	for (int i = 0; i < d / 2; i++) {
		asum->value[i] = al->value[i] + ar->value[i];
		bsum->value[i] = bl->value[i] + br->value[i];
	}

	karatsubaHelper(*ar, *br, x1, d / 2);
	karatsubaHelper(*al, *bl, x2, d / 2);
	karatsubaHelper(*asum, *bsum, x3, d / 2);

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
			cout << "Seuls les " << MAX << " premiers chiffres seront gardés." << endl << endl;
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