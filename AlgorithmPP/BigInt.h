#pragma once
class BigInt
{
public:
	BigInt();
	BigInt(int* _value);
	~BigInt();
	static const int MAX = 1024;
	int value[MAX];
	int d_value;

	void karatsuba(BigInt &nb);
	static void karatsuba(BigInt &a, BigInt &b);
	static void karatsubaHelper(BigInt &a, BigInt &b, int *ret, int d);
	static void multiplication(int *a, int *b, int *ret, int d);
	static void doCarry(int *a, int d);
	static void getNum(int *a, int *d_a);
	static void printNum(int *a, int d);
	void operator*(BigInt&);
	int* operator()(unsigned const& i);


};

