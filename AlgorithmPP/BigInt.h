// Dimitri BUHON - Karatsuba

#pragma once
class BigInt
{
public:
	static const int MAX = 1024;
	BigInt();
	BigInt(int size);
	BigInt(int* _value);
	~BigInt();

	int* value;
	int d_value;

	void print();
	static BigInt* karatsuba(BigInt &a, BigInt &b);

	BigInt* operator*(BigInt&);
	int* operator()(unsigned const& i);

private:
	void getInput();
	void carry();
	static void multiplication(int *a, int *b, int *res, int d);
	BigInt* karatsuba(BigInt &nb);
	static void karatsubaHelper(BigInt &a, BigInt &b, int *res, int d);
};

