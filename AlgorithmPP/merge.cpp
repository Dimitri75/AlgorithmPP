#include "stdafx.h"
#include "merge.h"


Merge::Merge()
{
}


Merge::~Merge()
{
}

int Merge::max(int x, int y){
	return x > y ? x : y;
}

void Merge::mergeHelper(int *input, int left, int right, int *scratch){
	if (right == left + 1)
		return;

	int i = 0;
	int length = right - left;
	int midpointDistance = length / 2;
	int l = left, r = left + midpointDistance;

	mergeHelper(input, left, left + midpointDistance, scratch);
	mergeHelper(input, left + midpointDistance, right, scratch);

	for (i = 0; i < length; i++){
		if (l < left + midpointDistance && (r == right || max(input[l], input[r]) == input[l])){
			scratch[i] = input[l];
			l++;
		}
		else{
			scratch[i] = input[r];
			r++;
		}
	}

	for (i = left; i < right; i++)
		input[i] = scratch[i - left];
}

// Elements are sorted from the greatest to the least
int Merge::sort(int *input, int size){
	int *scratch = new int;
	if (scratch != NULL){
		mergeHelper(input, 0, size, scratch);
		free(scratch);
		return 1;
	}
	return 0;
}