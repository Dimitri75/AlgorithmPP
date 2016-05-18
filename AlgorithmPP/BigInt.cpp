#include "stdafx.h"
#include "BigInt.h"

#define CUT 4

int* BigInt::operator()(unsigned const& i){
	return &value[i];
}

BigInt* BigInt::operator*(BigInt &nb){
	return karatsuba(*this, nb);
}

BigInt::BigInt()
{
	value = new int[MAX];
	getInput();
}

BigInt::BigInt(int size)
{
	value = new int[size];
}

BigInt::BigInt(int* _value){
	value = _value;
}


BigInt::~BigInt()
{
	delete[] value;
}

BigInt* BigInt::karatsuba(BigInt &nb){
	return karatsuba(*this, nb);
}

BigInt* BigInt::karatsuba(BigInt &a, BigInt &b){
	BigInt *r = new BigInt(6 * MAX);
	r->d_value = 1;

	if (a.d_value < 0 || b.d_value < 0) {
		std::cout << 0 << std::endl;
		exit(0);
		return nullptr;
	}

	int i = (a.d_value > b.d_value) ? a.d_value : b.d_value;

	while (r->d_value < i)
		r->d_value *= 2;

	for (i = a.d_value; i < r->d_value; i++)
		a.value[i] = 0;

	for (i = b.d_value; i < r->d_value; i++)
		b.value[i] = 0;

	BigInt::karatsubaHelper(a, b, r->value, r->d_value);

	r->d_value *= 2;
	r->carry();
	
	return r;
}

void BigInt::karatsubaHelper(BigInt &a, BigInt &b, int *res, int d) {
	if (d <= CUT) {
		multiplication(a.value, b.value, res, d);
		return;
	}

	BigInt *ar = new BigInt(a(0));
	BigInt *al = new BigInt(a(d / 2));
	BigInt *br = new BigInt(b(0));
	BigInt *bl = new BigInt(b(d / 2));

	BigInt *asum = new BigInt(&res[d * 5]);
	BigInt *bsum = new BigInt(&res[d * 5 + d / 2]);

	int *x1 = &res[d * 0];
	int *x2 = &res[d * 1];
	int *x3 = &res[d * 2];

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
		res[i + d / 2] += x3[i];
}

void BigInt::multiplication(int *a, int *b, int *res, int d) {
	for (int i = 0; i < 2 * d; i++) 
		res[i] = 0;

	for (int i = 0; i < d; i++) {
		for (int j = 0; j < d; j++) 
			res[i + j] += a[i] * b[j];
	}
}

void BigInt::carry() {
	int c = 0;

	for (int i = 0; i < d_value; i++) {
		value[i] += c;

		if (value[i] < 0)
			c = -(-(value[i] + 1) / 10 + 1);
		else
			c = value[i] / 10;

		value[i] -= c * 10;
	}

	if (c != 0)
		std::cout << stderr << " Overflow " << c << std::endl;
}

inline bool is_number(const std::string& s){
	return count_if(s.begin(), s.end(), isdigit) == s.size();
}

void BigInt::getInput() {
	std::string input;
	int c = 0;

	d_value = 0;
	std::cout << "Entrez un nombre : ";
	while (!(std::cin >> input) || !is_number(input)){
		std::cerr << "Erreur de saisie" << std::endl;
		std::cout << "Nombre : ";
	}

	for (int ch : input){
		if (c >= MAX){
			std::cout << "Seuls les " << MAX << " premiers chiffres seront gardés." << std::endl << std::endl;
			break;
		}

		value[d_value] = ch - '0';
		++(d_value);
		c++;
	}

	for (int i = 0; i * 2 < d_value - 1; i++) {
		c = value[i];
		value[i] = value[d_value - i - 1];
		value[d_value - i - 1] = c;
	}
}

void BigInt::print() {
	int i;
	for (i = d_value - 1; i > 0; i--)
		if (value[i] != 0)
			break;

	for (; i >= 0; i--)
		std::cout << value[i];
	std::cout << std::endl;
}
