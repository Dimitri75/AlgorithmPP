#include "stdafx.h"
#include "Sort.h"

//BUBBLE SORT
void Sort::bubbleSort(int a[], int size)
{

	int outer, inner;
	for (outer = size; outer > 0; --outer)	{
		for (inner = 0; inner < outer - 1; ++inner){
			if (a[inner] > a[inner + 1]){
				int temp = a[inner];
				a[inner] = a[inner + 1];
				a[inner + 1] = temp;
			}
		}
	}
}

//SELECTION SORT
void Sort::selectionSort(int a[], int size){
	int outer, inner, min;
	for (outer = 0; outer < size - 1; ++outer)	{
		min = outer;
		for (inner = outer + 1; inner < size; ++inner){
			if (a[inner] < a[min]){
				min = inner;
			}
		}

		int temp = a[outer];
		a[outer] = a[min];
		a[min] = temp;
	}
}

//INSERTION SORT
void Sort::insertionSort(int a[], int size){
	int i, j, tmp;
	for (i = 1; i < size; ++i){
		j = i;

		while (j > 0 && a[j - 1] > a[j]){
			tmp = a[j];
			a[j] = a[j - 1];
			a[j - 1] = tmp;
			--j;
		}
	}
}

//SHELL SORT
void Sort::shellSort(int a[], int size){
	int i, j, increment, temp;
	for (increment = size / 2; increment > 0; increment /= 2){
		for (i = increment; i<size; ++i){
			temp = a[i];
			for (j = i; j >= increment; j -= increment){
				if (temp < a[j - increment])
					a[j] = a[j - increment];
				else
					break;
			}
			a[j] = temp;
		}
	}
}


//QUICK SORT
void Sort::quickSort(int a[], int right){
	return Sort::quickSort(a, 0, right);
}

void Sort::quickSort(int a[], int left, int right)
{
	if (left < right)
	{
		int pivotIndex = partition(a, left, right);

		quickSort(a, left, pivotIndex - 1);
		quickSort(a, pivotIndex + 1, right);
	}
}


int Sort::partition(int a[], int left, int right)
{
	int p = left, pivot = a[left], location;

	for (location = left + 1; location <= right; location++){
		if (pivot > a[location]){
			a[p] = a[location];
			a[location] = a[p + 1];
			a[p + 1] = pivot;

			p++;
		}
	}
	return p;
}


// RAND QUICK SORT
void swap(int& a, int& b) {
	int t = b;
	b = a;
	a = t;
}

void Sort::randQuick(int a[], int l, int h) {
	if (h > l) {
		// partition
		int p = rand() % (h - l) + l;
		int d = a[p];
		// divide
		swap(a[l], a[p]);
		int i = l;
		int j = i + 1;
		while (j < h) {
			while (a[j] > d && j < h) j++;
			if (j < h) {
				i++;
				swap(a[i], a[j]);
				j++;
			}
		}
		swap(a[i], a[l]);
		randQuick(a, l, i);
		randQuick(a, i + 1, h);
	}
}

void Sort::randQuickSort(int a[], int size) {
	randQuick(a, 0, size);
}



// MERGE SORT
void Sort::merge(int a[], int l, int h) {
	if (h - l == 1) {
		if (a[l] > a[h]) {
			int t = a[l];
			a[l] = a[h];
			a[h] = t;
		}
	}
	else if (h == l) {

	}
	else if (h > l) {
		int size = h - l + 1;
		int m = l + (h - l) / 2;
		merge(a, l, m);
		merge(a, m + 1, h);
		int* b = new int[size];
		int k = 0;
		int i = l;
		int j = m + 1;
		while (i <= m && j <= h)
			if (a[i] <= a[j])
				b[k++] = a[i++];
			else
				b[k++] = a[j++];

		while (i <= m)
			b[k++] = a[i++];

		while (j <= h)
			b[k++] = a[j++];

		for (k = 0; k < size; k++)
			a[l + k] = b[k];
	
		delete[] b;
	}
}

void Sort::mergeSort(int a[], int size) {
	merge(a, 0, size - 1);
}