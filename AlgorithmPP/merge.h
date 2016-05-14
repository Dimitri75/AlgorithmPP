#pragma once
class Merge
{
public:
	Merge();
	~Merge();
	static int max(int x, int y);
	static void mergeHelper(int *input, int left, int right, int *scratch);
	static int sort(int *input, int size);
};

