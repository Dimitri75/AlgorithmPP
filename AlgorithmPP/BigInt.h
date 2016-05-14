#pragma once
class BigInt
{
public:
	BigInt();
	~BigInt();
	static const int MAX = 1024;
	static void karatsuba(int *a, int *b, int *ret, int d);
	static void multiplication(int *a, int *b, int *ret, int d);
	static void doCarry(int *a, int d);
	static void getNum(int *a, int *d_a);
	static void printNum(int *a, int d);
	void operator*(int const&);
};

