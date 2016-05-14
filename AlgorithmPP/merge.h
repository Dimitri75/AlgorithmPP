#pragma once
class merge
{
public:
	merge();
	~merge();
	static int max(int x, int y);
	static void merge_helper(int *input, int left, int right, int *scratch);
	static int sort(int *input, int size);
};

